#include<lpc17xx.h>
#include<stdio.h>
#include<stdlib.h>
#define RS_CTRL 0x08000000
#define EN_CTRL 0x10000000
#define DT_CTRL 0x07800000


unsigned int flag1,flag2,i,temp1,temp2,flag_key=0,row,col,temp3;
unsigned char msg[4];
unsigned int lcd_on[9] = {0x30,0x30,0x30,0x20,0x28,0x0c,0x01,0x06,0x80};
void lcd_write(void);
void port_write(void);
void delay(unsigned int);
void put_msg(unsigned char[]);
void lcd_init(void);
void keyboard_init(void);
void scan(void);

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	
	lcd_init();
	keyboard_init();
	
	while(1){
		for(row = 0;row<4;row++){
			if(row==0)
				temp1 = 1<<10;
			else if(row==1)
				temp1 = 1<<11;
			else if(row==2)
				temp1 = 1<<12;
			else if(row==3)
				temp1 = 1<<13;
			
			LPC_GPIO2->FIOPIN = temp1;
			flag_key = 0;
			scan();
			if(flag_key){
				temp2 = row*4+ col + 48; //Converting into ASCII
				flag1 = 1;
				lcd_write();
				break;
			}			
		}		
	}
}

void keyboard_init(){
	LPC_GPIO2->FIODIR = 0x00003C00;
}

void scan(){
	temp3 = LPC_GPIO1->FIOPIN;
	temp3&= 0x07800000;
	if(temp3!=0x00000000)
	{
		flag_key = 1;
		if(temp3 == 1<<23)
			col = 0;
		else if(temp3 == 1<<24)
			col = 1;
		else if(temp3 == 1<<25)
			col = 2;
		else if(temp3 == 1<<26)
			col = 3;
	}
}

void lcd_init(){
	LPC_GPIO0->FIODIR = RS_CTRL|DT_CTRL|EN_CTRL;
  i = 0;
	flag1 = 0;
	for(i = 0;i<9;i++)
	{
		temp1 = lcd_on[i];
		lcd_write();
	}
}

void lcd_write(){
	flag2 = ((temp1==0x30||temp1==0x20)&& flag1==0)?1:0;
	temp2 = temp1&0xf0;
	temp2<<=19;
	port_write();
	if(!flag2){
		temp2 = temp1&0x0f;
		temp2<<=23;
		port_write();
	}
}

void port_write(){
	LPC_GPIO0->FIOPIN = temp2;
	if(flag1==0)
		LPC_GPIO0->FIOCLR = RS_CTRL;
	else LPC_GPIO0->FIOSET = RS_CTRL;
	
	LPC_GPIO0->FIOSET = EN_CTRL;
	delay(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;
	delay(5000);
}

void delay(unsigned int r1){
	unsigned int r;
	for(r = 0;r<r1;r++);
}