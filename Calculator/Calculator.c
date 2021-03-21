#include<lpc17xx.h>
#include<stdio.h>
#include<stdlib.h>
#define RS_CTRL 0x08000000
#define EN_CTRL 0x10000000
#define DT_CTRL 0x07800000

unsigned int lcd_on[9] = {0x30,0x30,0x30,0x20,0x28,0x0c,0x06,0x01,0x80};
unsigned char keyboard[4][4] = {'0','1','2','3','4','5','6','7','8','9','+','-','*','/','=','='};
unsigned int temp1,temp2,temp3,temp4,flag1,flag2,flag_key,i,key1,key2,key3,key4,row,col;
char final_answer[30];

void scan(void);
void delay(unsigned int);
void lcd_write(void);
void port_write(void);
int keyscan(void);
void lcd_init(void);
void keyboard_init(void);
void put_msg(unsigned char[]);
	
	
int main(){
SystemInit();
SystemCoreClockUpdate();
LPC_GPIO0->FIODIR = RS_CTRL| EN_CTRL| DT_CTRL;
lcd_init();
keyboard_init();
	
key1 = keyscan()-'0';
	delay(50000);
key2 = keyscan();
	delay(50000);
key3 = keyscan()-'0';
	delay(50000);	
key4 = keyscan();
	delay(50000);
	
	switch(key2){
		case '+':
			sprintf(final_answer,"%3.2f",(float)key1+(float)key2);
			break;
		case '-':
			sprintf(final_answer,"%3.2f",(float)key1-(float)key2);
			break;
		case '*':
			sprintf(final_answer,"%3.2f",(float)key1*(float)key2);
			break;
		case '/':
			sprintf(final_answer,"%3.2f",(float)key1/(float)key2);
			break;
	}
	put_msg(final_answer);
	
	while(1);
}

void put_msg(unsigned char str[]){
	i = 0;
	flag1 = 1;
	while(str[i]!='\0'){
		temp1 = str[i];
		lcd_write();
		i++;
	}
}


void lcd_init(){
	
	flag1=0;
	for(i=0;i<9;i++){
		temp1 = lcd_on[i];
		lcd_write();
	}
}

void keyboard_init(){
	LPC_GPIO2->FIODIR = 0x00003C00;
}

void lcd_write(){
	flag2 = ((temp1==0x30 || temp1==0x20)&& flag1==0)?1:0;
	temp2 = temp1&0xf0;
	temp2<<=19;
	port_write();
	
	if(!flag2){
		temp2 = temp1&0x0f;
		temp2<<=23;
		port_write();
	}
}

void port_write(){
	LPC_GPIO0->FIOPIN = temp2;
	if(flag1!=0)
		LPC_GPIO0->FIOSET = RS_CTRL;
	else LPC_GPIO0->FIOCLR = RS_CTRL;
	
	LPC_GPIO0->FIOSET = EN_CTRL;
	delay(25);
	LPC_GPIO0->FIOCLR = EN_CTRL;
	delay(5000);
}

int keyscan(){
	while(1){
		for(row=0;row<4;row++)
		{
			if(row==0)
				temp3 = 1<<10;
			else if(row==1)
				temp3 = 1<<11;
			else if(row==2)
				temp3 = 1<<12;
			else if(row==3)
				temp3 = 1<<13;
			
			LPC_GPIO2->FIOPIN = temp3;
			flag_key = 0;
			scan();
			if(flag_key){
				temp1 = keyboard[row][col];
				flag1 = 1;
				lcd_write();
				break;
			}
		}
		if(flag_key)
			break;
		
	}
	return temp1;
	
}


void scan(){
	temp4 = LPC_GPIO1->FIOPIN;
	temp4&=0x07800000;
	if(temp4!=0){
		flag_key = 1;
		if(temp4 == 1<<23)
			col = 0;
		else if(temp4 == 1<<24)
			col = 1;
		else if(temp4 == 1<<25)
			col = 2;
		else if(temp4 ==1<<26)
			col = 3;
	}
}

void delay(unsigned int r){
	unsigned int r1;
	for(r1 = 0;r1<r;r++);
}

