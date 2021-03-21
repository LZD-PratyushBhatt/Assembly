#include<lpc17xx.h>
#include<stdio.h>
#include<stdlib.h>

unsigned int i,counter=1,j;
unsigned int bcd_array[9] = {0,0,0,0,0,0,0,0,0};

void delay(unsigned int);
void  change_array(void);
int main(){
	LPC_PINCON->PINSEL0 = 0;
	LPC_GPIO0->FIODIR = 0x00000FF0;
	
	while(1){
		for(i = 0;i<99;i++){
			LPC_GPIO0->FIOPIN = bcd_array[1]<<4 | bcd_array[2]<<5 | bcd_array[3]<<6 | bcd_array[4]<<7 | bcd_array[5]<<8 | bcd_array[6]<<9 | bcd_array[7]<<10
			| bcd_array[8]<<11;
			change_array();	
			delay(5);
		}
	}
}

void change_array(){
	if(counter==10){
		bcd_array[1] = 0;
		bcd_array[2] = 0;
		bcd_array[3] =0;
		bcd_array[4]=0;
		bcd_array[5]++;
		if(bcd_array[5]==2){
			bcd_array[5] = 0;
			bcd_array[6]++;
			if(bcd_array[6]==2){
				bcd_array[6]=0;
				bcd_array[7]++;
			}
			if(bcd_array[7]==2){
				bcd_array[7]=0;
				bcd_array[8]++;
			}
	}
		counter = 1;
	}
	else{
		counter++;
		
		bcd_array[1]++;
		if(bcd_array[1]==2){
			bcd_array[1] = 0;
			bcd_array[2]++;
			if(bcd_array[2]==2){
				bcd_array[2]=0;
				bcd_array[3]++;
			}
			if(bcd_array[3]==2){
				bcd_array[3]=0;
				bcd_array[4]++;
			}
	}
}
	}

void delay(unsigned int r){
	unsigned int r1;
	for(r1=0;r1<r;r1++);
}
