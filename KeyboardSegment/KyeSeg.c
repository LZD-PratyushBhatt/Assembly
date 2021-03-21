#include<lpc17xx.h>
#include<stdio.h>
#include<stdlib.h>
#define FIRST_SEGMENT 0xFFF87FFF;
unsigned int i,temp1,temp2,temp3,row,col,flag1,flag2,flag_key;
unsigned int seven_segment[4][4] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x58,0x5e,0x79,0x71};
void keyboard_init(void);
void scan(void);
void delay(unsigned int);
	
int main(){
	SystemInit();
	SystemCoreClockUpdate();

	LPC_GPIO0->FIODIR = 0xffffffff; //p0.4 - p0.11 and p0.15 -p0.18  seven Segment
	keyboard_init();
	
	while(1){
		
		for(row =0;row<4;row++){
			if(row ==0)
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
				temp3 = seven_segment[row][col];
				LPC_GPIO0->FIOMASK = 0xFFF87FFF;
				LPC_GPIO0->FIOPIN = FIRST_SEGMENT;
				LPC_GPIO0->FIOMASK = 0xFFFFF00F;
				LPC_GPIO0->FIOPIN = temp3;
				break;
			}
		}
		delay(50000);
		
	}
}
void keyboard_init(){
	LPC_GPIO2->FIODIR = 0x00003C00;
}

void scan(){
	temp2 = LPC_GPIO1->FIOPIN;
	temp2&=0x07800000;
	if(temp2!=0x00000000){
		flag_key = 1;
		if(temp2 == 1<<23)
			col = 0;
		else if(temp2 == 1<<24)
			col = 1;
		else if(temp2 ==1<<25)
			col=2;
		else if(temp2 ==1<<26)
			col = 3;
	}
	
}

void delay(unsigned int r){
	unsigned int r1;
	for(r1=0;r1<r;r1++);
}