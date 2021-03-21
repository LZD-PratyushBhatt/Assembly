#include<lpc17xx.h>
#include<stdio.h>
#include<stdlib.h>
#define FIRST_SEGMENT 0
unsigned int temp = 0,temp1,row,col,flag=0,temp2;
unsigned char array[4][4] = {0x3F,0x06,0x5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F,0x77,0x7C,0X58,0X5E,0X79,0X71};
void scan(void);
int main(){
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_GPIO0->FIODIR = 0xFFFFFFFF; //p0.15 to p0.18 and p0.4 - p0.11
	LPC_GPIO2->FIODIR = 0x00003C00; //P2.10 - P2.13
	
	while(1){
		
		for(row = 0;row<4;row++){
			if(row==0)
				temp1 = 1<<10;
			else if(row==1) 
			  temp1 = 1<<11;
			else if(row ==2)
				temp1 = 1<<12;
			else if(row==3)
				temp1 = 1<<13;
			
			LPC_GPIO2->FIOPIN = temp1;
			flag = 0;
			scan();
			
			if(flag){
				temp2 = array[row][col];
				LPC_GPIO0->FIOMASK = 0xFF87FFF;
				LPC_GPIO0->FIOPIN = FIRST_SEGMENT;
				LPC_GPIO0->FIOMASK = 0xFFFFF00F;
				LPC_GPIO0->FIOPIN = temp2;
				break;
			}
		}
	}
}


void scan(){
	temp = LPC_GPIO1->FIOPIN;
	temp &= 0x07800000;
	if(temp!=0){
		flag = 1;
	if(temp==1<23)
		col = 0;
	else if(temp==1<24)
		col = 1;
	else if(temp==1<<25)
		col = 2;
	else if(temp==1<<26)
		col = 3;
	
}
}
	
