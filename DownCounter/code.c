#include<lpc17xx.h>
unsigned int i;
unsigned int dig_count;
unsigned int dig_array[5] = {0,9,9,9,9};
unsigned int select_seg[5] = {0,0<<23,1<<23,2<<23,3<<23};
unsigned char seven_segment[10] = {0x3f,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned int flag = 0;
unsigned int counter = 0;

void display(void);
void delay(void);

int main(){
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_GPIO0->FIODIR = 0x00000ff0;
	LPC_GPIO1->FIODIR = 0x07800000;
	
	while(1){
		delay();
		dig_count++;
		if(dig_count ==0x05)
			dig_count = 1;
		if(flag == 0xff) // means 1 second has passed according to our assumption
		{
			flag = 0;
			dig_array[1]--;
			if(dig_array[1]==0){
				dig_array[1] = 9;
				dig_array[2]-=1;
				
				if(dig_array[2]==0){
					dig_array[2] = 9;
					dig_array[3]-=1;
					
					if(dig_array[3] == 0){
						dig_array[3] = 9;
						dig_array[4]-=1;
						
						if(dig_array[4]==0)
							dig_array[4] = 9;
					}
				}
			}
		}	
		display();
	}
}

void display(){
	LPC_GPIO1->FIOPIN = select_seg[dig_count];
	LPC_GPIO0->FIOPIN = seven_segment[dig_array[dig_count]]<<4;
	for(i=0;i<500;i++);
	LPC_GPIO0->FIOCLR = 0x00000ff0;
}

void delay(){
	
	for(i=0;i<500;i++); //Lets think that this loop gives 50ms delay
	if(counter == 20){
		counter = 0;
		flag = 0xff;
	}
	else counter++;
}