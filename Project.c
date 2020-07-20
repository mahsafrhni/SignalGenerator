#include "stm32f4xx.h"
#include <stdio.h>
#include <stdbool.h>
#define RS 0x20     /* PB5 mask for reg select */
#define RW 0x40     /* PB6 mask for read/write */
#define EN 0x80     /* PB7 mask for enable */

void PORTS_init(void);
void usart_init(void);
void usart_write(uint8_t data);
void adc_init();
uint16_t adc_conv();
void delayMs(int n);
void LCD_command(unsigned char command);
void LCD_data(char data);
void LCD_init(void);
void clearScreen(void);
void askTime();
void askFerequency();

int main(void) {
	LCD_init();
	PORTS_init();
	adc_init();
	usart_init(); 
	clearScreen();
	char stId[] = "96243048\r\n";
	char menu[] = "1.Sin 2.Square";
	char menu1[] = "3.Triangle 4.Sawtooth";
	char time[]="Time?";
	char f[]="frq?";
	//char menu3[]="5.step";
	int pressed,key;
  uint16_t adc;
	uint16_t tw [4];
  uint16_t fw[3];
	for (int i = 0; i < 10; i++) {
		LCD_data(stId[i]);
	}
	delayMs(1500);
	clearScreen();
	delayMs(70);
	for (int i = 0; i < 15; i++) {
		LCD_data(menu[i]);
	}
	LCD_command(192);
	for (int i = 0; i < 21; i++) {
		LCD_data(menu1[i]);
	}
	delayMs(400);
	while(1){
		delayMs(40);
		GPIOB->ODR=0xEFFF;
	  pressed = GPIOB->IDR;
		switch(pressed){
			case 0xEEFF:  //1
				usart_write(1);
				clearScreen();
				delayMs(40);
	      for (int i = 0; i < 5; i++) {
					LCD_data(time[i]);
				}
				delayMs(150);
				while(pressed!=0x7BFF){ // mokhalefe morabba
				adc = adc_conv(); //masalan 5354
				clearScreen();
				delayMs(6);	
				tw[0]=adc/1000;  //=5
				adc%=1000;      //=354
				tw[1]=adc/100;  //=3
				adc%=100;   //=54
				tw[2]=adc/10;  //=5
				adc%=10;  //=4
				tw[3]=adc; //=4
				for (int i = 0; i < 4; i++) {
					LCD_data((char)(tw[i]+'0'));
				}	
				delayMs(300);
				GPIOB->ODR = 0X7FFF;  //vared kardane #
				pressed = GPIOB->IDR;
				delayMs(5);
				}
				LCD_command(1);
				delayMs(1);
	      for (int i = 0; i < 4; i++) {
					LCD_data(f[i]);
				}
				delayMs(500);
			  pressed = 0xFFFF;
				while(pressed!=0x7BFF){
			  adc = adc_conv(); //masalan 535
				delayMs(300);	
				clearScreen();
				delayMs(6);	
				fw[0]=adc/100;  //=5
				adc%=100;      //=35
				fw[1]=adc/10;  //=3
				adc%=10;   //=5
				fw[2]=adc;  //=5
				for (int i = 0; i < 3; i++) {
					LCD_data((char)(fw[i]+'0'));
				}	
			GPIOB->ODR = 0X7FFF;
			pressed = GPIOB->IDR;
			delayMs(5);
	}
			break;
			case 0xEDFF:  //2
			usart_write(2);
				clearScreen();
				delayMs(40);
				//char time[]="Time?";
	      for (int i = 0; i < 5; i++) {
					LCD_data(time[i]);
				}
				delayMs(150);
				while(pressed!=0x7BFF){
				adc = adc_conv(); //masalan 5354
				clearScreen();
				delayMs(6);	
				tw[0]=adc/1000;  //=5
				adc%=1000;      //=354
				tw[1]=adc/100;  //=3
				adc%=100;   //=54
				tw[2]=adc/10;  //=5
				adc%=10;  //=4
				tw[3]=adc; //=4
				for (int i = 0; i < 4; i++) {
					LCD_data((char)(tw[i]+'0'));
				}	
				delayMs(300);
				GPIOB->ODR = 0X7FFF;
				pressed = GPIOB->IDR;
				delayMs(5);
				}
				LCD_command(1);
				delayMs(1);
				//char f[]="frq?";
	      for (int i = 0; i < 4; i++) {
					LCD_data(f[i]);
				}
				delayMs(500);
			pressed = 0xFFFF;
				while(pressed!=0x7BFF){
			adc = adc_conv(); //masalan 535
				delayMs(300);	
				clearScreen();
				delayMs(6);	
				fw[0]=adc/100;  //=5
				adc%=100;      //=35
				fw[1]=adc/10;  //=3
				adc%=10;   //=5
				fw[2]=adc;  //=5
				for (int i = 0; i < 3; i++) {
					LCD_data((char)(fw[i]+'0'));
				}	
			GPIOB->ODR = 0X7FFF;
			pressed = GPIOB->IDR;
			delayMs(5);
	}
			break;
			case 0xEBFF: //3
			usart_write(3);
				clearScreen();
				delayMs(40);
				//char time[]="Time?";
	      for (int i = 0; i < 5; i++) {
					LCD_data(time[i]);
				}
				delayMs(150);
				while(pressed!=0x7BFF){
				adc = adc_conv(); //masalan 5354
				clearScreen();
				delayMs(6);	
				tw[0]=adc/1000;  //=5
				adc%=1000;      //=354
				tw[1]=adc/100;  //=3
				adc%=100;   //=54
				tw[2]=adc/10;  //=5
				adc%=10;  //=4
				tw[3]=adc; //=4
				for (int i = 0; i < 4; i++) {
					LCD_data((char)(tw[i]+'0'));
				}	
				delayMs(300);
				GPIOB->ODR = 0X7FFF;
				pressed = GPIOB->IDR;
				delayMs(5);
				}
				LCD_command(1);
				delayMs(1);
			//	char f[]="frq?";
	      for (int i = 0; i < 4; i++) {
					LCD_data(f[i]);
				}
				delayMs(500);
			pressed = 0xFFFF;
				while(pressed!=0x7BFF){
			adc = adc_conv(); //masalan 535
				delayMs(300);	
				clearScreen();
				delayMs(6);	
				fw[0]=adc/100;  //=5
				adc%=100;      //=35
				fw[1]=adc/10;  //=3
				adc%=10;   //=5
				fw[2]=adc;  //=5
	
				for (int i = 0; i < 3; i++) {
					LCD_data((char)(fw[i]+'0'));
				}	
			GPIOB->ODR = 0X7FFF;
			pressed = GPIOB->IDR;
			delayMs(5);
	}		
			break;
		}
		GPIOB->ODR = 0XDFFF;
		pressed = GPIOB->IDR;
		switch(pressed){
			case 0xDEFF: //4
			usart_write(4);
				clearScreen();
				delayMs(40);
				char time[]="Time?";
	      for (int i = 0; i < 5; i++) {
					LCD_data(time[i]);
				}
				delayMs(150);
				while(pressed!=0x7BFF){
				adc = adc_conv(); //masalan 5354
				clearScreen();
				delayMs(6);	
				tw[0]=adc/1000;  //=5
				adc%=1000;      //=354
				tw[1]=adc/100;  //=3
				adc%=100;   //=54
				tw[2]=adc/10;  //=5
				adc%=10;  //=4
				tw[3]=adc; //=4
				for (int i = 0; i < 4; i++) {
					LCD_data((char)(tw[i]+'0'));
				}	
				delayMs(300);

				GPIOB->ODR = 0X7FFF;
				pressed = GPIOB->IDR;
				delayMs(5);
				}
				LCD_command(1);
				delayMs(1);
				char f[]="frq?";
	      for (int i = 0; i < 4; i++) {
					LCD_data(f[i]);
				}
				delayMs(500);
			pressed = 0xFFFF;
				while(pressed!=0x7BFF){
			adc = adc_conv(); //masalan 535
				delayMs(300);	
				clearScreen();
				delayMs(6);	
				fw[0]=adc/100;  //=5
				adc%=100;      //=35
				fw[1]=adc/10;  //=3
				adc%=10;   //=5
				fw[2]=adc;  //=5
				
				for (int i = 0; i < 3; i++) {
					LCD_data((char)(fw[i]+'0'));
				}	
			GPIOB->ODR = 0X7FFF;
			pressed = GPIOB->IDR;
			delayMs(5);
	}				
			break;
		}
	 }
 }
void LCD_init(void) {
	PORTS_init();
	delayMs(30);            /* initialization sequence */
	LCD_command(0x30);
	delayMs(10);
	LCD_command(0x30);
	delayMs(1);
	LCD_command(0x30);
	LCD_command(0x38);     
	LCD_command(0x06);     
	LCD_command(0x01);      
  LCD_command(0x0F);      
}

void PORTS_init(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;    
  GPIOA->MODER = 0x0069000F;
	
    /* Configure PA9 for USART1_TX */
  GPIOA->AFR[1] &= 0x00000000; /* erase AFR */
  GPIOA->AFR[1] |= 0x00000770; /* enable pin 9 and pin 10 alt7 for USART1*/
	RCC->AHB1ENR |=  0x06;          /* enable GPIOB/C clock */
	
  GPIOB->MODER &= ~0xFF00FC00;    /* clear pin mode */
  GPIOB->MODER |=  0x55005400;    /* set pin output mode */
  GPIOB->BSRR = 0x00C00000;       /* turn off EN and R/W */
	
  GPIOC->MODER &= ~0x0000FFFF;    /* clear pin mode */
  GPIOC->MODER |=  0x00005555;    /* set pin output mode */
}

void LCD_command(unsigned char command) {
	GPIOB->BSRR = (RS | RW) << 16;  
	GPIOC->ODR = command;          
	GPIOB->BSRR = EN;              
	delayMs(0);
	GPIOB->BSRR = EN << 16;        
	if (command < 4)
		delayMs(2);         
	else
		delayMs(1);        
}
void clearScreen(void){
	GPIOB->BSRR = (RS | RW) << 16; 
	GPIOC->ODR = 1;          
	GPIOB->BSRR = EN;             
	delayMs(0);
	GPIOB->BSRR = EN << 16;
	delayMs(2); 
}

void LCD_data(char data) {
	GPIOB->BSRR = RS;              
	GPIOB->BSRR = RW << 16;        
	GPIOC->ODR = data;              
	GPIOB->BSRR = EN;               
	delayMs(0);
	GPIOB->BSRR = EN << 16;        
	delayMs(1);
}

void delayMs(int n) {
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 3000; i++) ;
}

void usart_write(uint8_t data){
   while(!(USART1->SR & 0x0080)){}
			USART1->DR=(data & (uint8_t)0xFF);
}

void usart_init(){
  RCC->APB2ENR |= 0x00000010 ; /* enable USART1 clock */
  USART1->BRR = 0x0683; /* 9600 baud @ 16 MHz */
  USART1->CR1 |= 0x0008; /* enable Tx, 8-bit data */
  USART1->CR1 |= 0x0004;  /* enable Rx, 8-bit data */
  USART1->CR2 = 0x0000; /* 1 stop bit */
  USART1->CR3 = 0x0000; /* no flow control */
  USART1->CR1 |= 0x2000; /* enable USART1 */

}
  
void adc_init(){
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 
  ADC1->CR2 = 0;
  ADC1->SQR1 |= 0; 
  ADC1->SQR3 |= 1; 
  ADC1->CR2 |= ADC_CR2_ADON;  
}

uint16_t adc_conv(){
  ADC1->CR2 |= ADC_CR2_SWSTART; 
  while(!(ADC1->SR & 2)){}
  return ADC1->DR;
}
void askTime(){
	 char time[]="Time?";
	for (int i = 0; i < 5; i++) {
					LCD_data(time[i]);
				}
}
void askFerequency(){
	char f[]="frq?";
	for (int i = 0; i < 4; i++) {
					LCD_data(f[i]);
				}
}
//void show_time(uint16_t time){
  //int i ;
  //char str[16];
	//char tArr[16];
  //sprintf(str, "%d", time*1900+500 );
  //LCD_command(1);  //clear display 
 // LCD_command(0x80); //begin from first line
 // for(i=0;i<sizeof(str);i++){
  //  tArr[i] = str[i];
   // LCD_data(str[i]);
  //}
//}
