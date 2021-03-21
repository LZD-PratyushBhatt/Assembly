#include<lpc17xx.h>
#include<stdio.h>
#include<stdlib.h>
#define RS_CTRL 0x08000000
#define EN_CTRL 0x10000000
#define DT_CTRL 0x07800000

unsigned int i,temp1,temp2,flag1,flag2;
unsigned int lcd_on[9] = {0x30,0x30,0x30,0x20,0x28,0x0c,0x06,0x01,0x80};
unsigned char msg[30] = {"My name is Pratyush"};
void lcd_init(void);
void delay(unsigned int);
void lcd_write(void);
void port_write(void);
void put_msg(unsigned char[]);
int main(){
	
	SystemInit();
	SystemCoreClockUpdate();
	
	lcd_init();
	put_msg(msg);
	
	
}

void lcd_init(){
	LPC_GPIO0->FIOPIN = RS_CTRL|DT_CTRL|EN_CTRL;
	flag1 =1;
	for(i=0;i<9;i++)
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
		temp2 = temp1&=0x0f;
		temp2<<=23;
		port_write();
	}
}

void port_write(){
	LPC_GPIO0->FIOPIN = temp2;
	if(flag1==0)
		LPC_GPIO0->FIOSET = RS_CTRL;
	else LPC_GPIO0->FIOCLR = RS_CTRL;
	
	LPC_GPIO0->FIOSET = EN_CTRL;
	delay(50);
	LPC_GPIO0->FIOCLR = EN_CTRL;
	delay(5000);
	
}

void put_msg(unsigned char str[]){
	i = 0;
	flag1 =1;
	while(str[i]!='\0')
	{
	temp1 = str[i];	
		lcd_write();
		i++;
		if(i==16)
		{
			flag1 = 0;
			temp1 = 0xc0;
			lcd_write();
			flag1 = 1;
		}
	}
}

void delay(unsigned int r){
	unsigned int r1;
	for(r1=0;r1<r;r1++);
}
