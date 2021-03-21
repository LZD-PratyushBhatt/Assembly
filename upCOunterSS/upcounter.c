#include<lpc17xx.h>
#include<stdio.h>
#include<stdlib.h>

unsigned int dig_count=0,temp,counter = 0,i,flag = 0;
int count_array[5] = {0,1,2,3,4};
unsigned int select_segment[5] = {0,1<<23,2<<23,3<<23,4<23};
unsigned int seven_segment[10] = {0x3F,0x06,0x5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
void increasing_count(void);
void delay(void);
void display(void);
void decreasing_count(void);
void delay_count(void);
int main(){
	SystemInit();
	SystemCoreClockUpdate();
	LPC_GPIO0->FIODIR = 0x00000ff0; //p0.4 - p0.11 connector A
	LPC_GPIO2->FIODIR = 0x07800000;  //p2.23 - p2.26   connector B
	
	while(1){
		//delay();
		dig_count++;
		if(dig_count==5)
		{
			dig_count = 1;
		}
		//if(!(LPC_GPIO0->FIOPIN & 1<<21))
		increasing_count();
	//	else decreasing_count();
		display();	
	}
}

void increasing_count(){
	if(flag){
			flag = 0;
			count_array[1]++;
			if(count_array[1]==10){
				count_array[1]=0;
				count_array[2]++;
				if(count_array[2]==10){
					count_array[2] = 0;
					count_array[3]++;
					if(count_array[3]==10){
						count_array[3] = 0;
						count_array[4]++;
						if(count_array[4]==10){
							count_array[4]=0;
				}
			}
		}
	}
}	
}

void decreasing_count(){
	if(flag){
			flag = 0;
			count_array[1]--;
			if(count_array[1]==-1){
				count_array[1]=9;
				count_array[2]--;
				if(count_array[2]==-1){
					count_array[2] = 9;
					count_array[3]--;
					if(count_array[3]==-1){
						count_array[3] = 9;
						count_array[4]--;
						if(count_array[4]==-1){
							count_array[4]=9;
				}
			}
		}
	}
}
	
}

void display(){
 LPC_GPIO2->FIOPIN = select_segment[dig_count];
	LPC_GPIO0->FIOPIN = seven_segment[count_array[dig_count]]<<4;
for(i=0;i<500;i++);
	LPC_GPIO0->FIOCLR = 0x00000ff0;
}

void delay_count(){
	LPC_TIM0->TCR = 0x02;
	LPC_TIM0->PR = 2;
	LPC_TIM0->MR0=2999;
	LPC_TIM0->MCR = 0x04;
	LPC_TIM0->EMR = 0x20;
	LPC_TIM0->TCR = 0x01;
	while(!(LPC_TIM0->EMR & 0x01));
}

void delay(){
	delay_count();
	if(counter==1000){
		counter = 0;
		flag = 1;
	}
	else counter++;
}
