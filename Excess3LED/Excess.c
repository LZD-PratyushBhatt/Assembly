#include<lpc17xx.h>
#include<stdio.h>
#include<stdlib.h>

unsigned int i,counter=0,j,carry = 0,flag=0;
int bcd_array[9] = {0,-1,0,0,0,0,0,0,0};
int excess_array[9] = {0,0,0,0,0,0,0,0,0};
void delay(unsigned int);
void  change_array(void);
int main(){
	LPC_PINCON->PINSEL0 = 0;
	LPC_GPIO0->FIODIR = 0x00000FF0;
	
	while(1){
		for(i = 0;i<99;i++){
			change_array();	
			LPC_GPIO0->FIOPIN = excess_array[1]<<4 | excess_array[2]<<5 | excess_array[3]<<6 | excess_array[4]<<7 | excess_array[5]<<8 | excess_array[6]<<9 | excess_array[7]<<10
			| excess_array[8]<<11;
			delay(5);
		}
	}
}

void change_array(){
	if(counter==10){
		flag=1;
		bcd_array[1] = 0;
		bcd_array[2] = 0;
		bcd_array[3] =0;
		bcd_array[4] =0;
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
	

//EXCESS 3
  //for index 1 and 2
  excess_array[1]++;
		if(excess_array[1]==2){
			excess_array[1] = 0;
			excess_array[2]++;
			
			if(excess_array[2]==2){
				excess_array[2]=1;
				excess_array[3]++;
			}
			if(excess_array[3]==2){
				excess_array[3]=0;
				excess_array[4]++;
			}
	}
		else{
			excess_array[2]++;
			if(excess_array[2]==2){
				excess_array[2]=1;
				excess_array[3]++;
			}
			if(excess_array[3]==2){
				excess_array[3]=0;
				excess_array[4]++;
			}
		}
		
		
	// for index 5 and 6
	if(flag){
	 excess_array[5]++;
		if(excess_array[5]==2){
			excess_array[5] = 0;
			excess_array[6]++;
			
			if(excess_array[6]==2){
				excess_array[6]=1;
				excess_array[7]++;
			}
			if(excess_array[7]==2){
				excess_array[7]=0;
				excess_array[8]++;
			}
	}
		else
		{
			excess_array[6]++;
			if(excess_array[6]==2){
				excess_array[6]=1;
				excess_array[7]++;
			}
			if(excess_array[7]==2){
				excess_array[7]=0;
				excess_array[8]++;
			}
		}
}	
	
}

void delay(unsigned int r){
	unsigned int r1;
	for(r1=0;r1<r;r1++);
}
