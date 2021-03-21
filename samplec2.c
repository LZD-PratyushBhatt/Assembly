#include<lpc17xx.h>

int main(){
unsigned long int i;
//toggle p0.8 to p0.15

LPC_PINCON->PINSEL0=0;
LPC_GPIO0->FIODIR = 0X0000fff0;

while(1){
LPC_GPIO0->FIOSET = 0X0000FFF0;

for(i=0;i<1000;i++);
LPC_GPIO0->FIOCLR = 0X0000FFF0;
for(i=0;i<1000;i++);
}
return 0;

}