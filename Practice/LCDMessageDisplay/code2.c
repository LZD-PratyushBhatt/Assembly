#include<lpc17xx.h>
#include<stdio.h>
#include<stdlib.h>
#define RS_CTRL 0x08000000
#define EN_CTRL 0x10000000
#define DT_CTRL 0x07800000

unsigned int flag1,flag2,temp1,temp2,i;
unsigned int lcd_on[9] = {0x30,0x30,0x30,0x20,0x28,0xC0,0x06,0x01,0x80};
unsigned char msg[30] = {"My name is Pratyush Bhatt"};

void lcd_init(void);
void put_msg(unsigned char []);
void lcd_write(void);
void port_write(void);
void delay(unsigned int);



int main(){
	SystemInit();
	SystemCoreClockUpdate();
	
	lcd_init();
  put_msg(msg);
	
}

void lcd_init(){
	LPC_GPIO0->FIODIR = RS_CTRL|DT_CTRL|EN_CTRL;
	flag1 = 0; //command
	i = 0;
	for(i = 0;i<9;i++)
	{
		temp1 = lcd_on[i];
		lcd_write();
	}
}

void put_msg(unsigned char msg[]){
	flag1 = 1;
	i = 0;
	while(msg[i]!='\0'){
		temp1 = msg[i];
		lcd_write();
		i++;
		if(i == 16){
			flag1 = 0;
			temp1 = 0xC0; //Carriage return and line feed to the second line
			lcd_write();
			flag1 = 1;
	}
}
}

void lcd_write(){
	flag2 = ((temp1==0x20||temp1==0x30) && flag1==0)?1:0; // either one of the four command or else
	temp2 = temp1&0xf0;
	temp2<<=19; // p0.23 - p0.26
	port_write();
	if(!flag2){
		temp2 = temp1&0x0f;
		temp2<<=23; //p0.23 - p0.26
		port_write();
	}
}

void port_write(){
	LPC_GPIO0->FIOPIN = temp2;
	if(!flag1)
		LPC_GPIO0->FIOCLR = RS_CTRL; //command
	else LPC_GPIO0->FIOSET = RS_CTRL; //data
	
	LPC_GPIO0->FIOSET = EN_CTRL;
	delay(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;
	delay(5000);
}

void delay(unsigned int r1){
	unsigned int r;
	for(r = 0;r<r1;r++);
}
