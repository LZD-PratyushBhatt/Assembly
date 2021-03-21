#include<lpc17xx.h>
#include<stdio.h>
#include<stdlib.h>
#define RS_CTRL 0x08000000
#define EN_CTRL 0x10000000
#define DT_CTRL 0x07800000


unsigned int flag1,flag2,i,temp,temp1,temp2,temp_key,flag_key=0,row,col,temp3,key1,key2,key3,key4;
unsigned char msg[4];
unsigned int lcd_on[9] = {0x30,0x30,0x30,0x20,0x28,0x0c,0x01,0x06,0x80};
unsigned char keyboard[4][4] = {'0','1','2','3','4','5','6','7','8','9','+','-','*','/','='};
unsigned char str[5];
void lcd_write(void);
void port_write(void);
void delay(unsigned int);
void put_msg(unsigned char[]);
void lcd_init(void);
void keyboard_init(void);
void scan(void);
int keyScan(void);


int main(){
	SystemInit();
	SystemCoreClockUpdate();
	
	lcd_init();
	keyboard_init();
	key1 = keyScan();
	key1 = key1-'0';
  delay(10000);
	key2 = keyScan();
	delay(10000);
	key3 = keyScan();
	delay(10000);
	key3 = key3-'0';
	key4 = keyScan();
	delay(100000);
	
	switch(key2){
		case '+':
			sprintf(str,"%3.2f",(float)key1+(float)key2);
			break;
		case '-':
			sprintf(str,"%3.2f",(float)key1-(float)key2);
			break;
		case '*':
			sprintf(str,"%3.2f",(float)key1*(float)key2);
			break;
		case '/':
			sprintf(str,"%3.2f",(float)key1/(float)key2);
			break;
		
	}
	
	put_msg(str);
	
}

void keyboard_init(){
	LPC_GPIO2->FIODIR = 0x00003C00;
}

int keyScan(void){
	
		while(1){
		for(row = 0;row<4;row++){
			if(row==0)
				temp = 1<<10;
			else if(row==1)
				temp = 1<<11;
			else if(row==2)
				temp = 1<<12;
			else if(row==3)
				temp = 1<<13;
			
			LPC_GPIO2->FIOPIN = temp;
			flag_key = 0; //Fresh Scan
			scan();
			if(flag_key){
				temp_key = keyboard[row][col]; //Converting into ASCII
				flag1 = 1;
				lcd_write();
				break;
			}			
		}		
		if(flag_key==1){
			break;
		}
	}
	return temp_key;
	
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

void put_msg(unsigned char str[]){
	i = 0;
	flag1 = 1;
	while(str[i]!='\0')
	{
		temp1 = str[i];
		lcd_write();
		i++;
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