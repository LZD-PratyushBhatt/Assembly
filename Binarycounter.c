#include<LPC17XX.H>

int main(){
	unsigned int i=0;
	unsigned int j = 0;
	unsigned int counter=0;
	LPC_PINCON->PINSEL0=0;
	LPC_GPIO0->FIODIR = 0X00000FF0;
	
	while(1){
		for(j=0;j<256;j++){
			LPC_GPIO0->FIOPIN = counter<<4;
			for(i=0;i<100;i++); //Delay
			counter++;
		}
		counter = 0;
	}
	
}