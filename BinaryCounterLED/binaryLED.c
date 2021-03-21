#include<lpc17xx.h>
#include<stdio.h>
#include<stdlib.h>

unsigned int i,j,counter;
unsigned int array_binary[9] = {0,0,0,0,0,0,0,0,0};
void delay(unsigned int);
void change_array(void);
int main(){
	//p0.4 - p0.11 LEDs are connected,
	LPC_GPIO0->FIODIR = 0x00000ff0;  //All set as output
	
	counter = 0;
	while(1){
		
	for(counter = 0;counter<256;counter++){
   change_array();
   LPC_GPIO0->FIOPIN = (array_binary[1]<<4)|(array_binary[2]<<5)|(array_binary[3]<<6)|(array_binary[4]<<7)|(array_binary[5]<<8)|(array_binary[6]<<9)|
		(array_binary[7]<<10)|(array_binary[8]<<11);
		delay(5);
	}		
	}	
}

void delay(unsigned int r){
	unsigned int r1;
	for(r1= 0;r1<r;r1++);
}

void change_array(){
	array_binary[1]++;
	if(array_binary[1]==2){
		array_binary[1] = 0;
		array_binary[2]++;
		  if(array_binary[2]==2){
				array_binary[2] = 0;
		array_binary[3]++;
		  if(array_binary[3]==2){
				array_binary[3] = 0;
		array_binary[4]++;
		  if(array_binary[4]==2){
				array_binary[4] = 0;
		array_binary[5]++;
		  if(array_binary[5]==2){
				array_binary[5] = 0;
		array_binary[6]++;
		  if(array_binary[6]==2){
				array_binary[6] = 0;
		array_binary[7]++;
		  if(array_binary[7]==2){
				array_binary[7] = 0;
		array_binary[8]++;
		  if(array_binary[8]==2){
				array_binary[8] = 0;
					}}}	}	}	}	}	}
}