#include "stm32F4xx.h"
#include <math.h>
#define wave_LEN 256

void ports_init(void);
void usart_init(void);
uint8_t usart_read(void);
void sine(void); 	
void sawt();
int sinus[wave_LEN];
void delayMs(int);
void sqaure(int freq);
void delayforSq(int n);

int main (void) {
	ports_init();
	usart_init();
	delayMs(7);
	int select = usart_read();
	delayMs(50);	
	switch(select){
		case 1:
			GPIOC->ODR = 0x1;
			sine();
			while (1){
				for(int i =0;i< wave_LEN;i++)
					GPIOB ->ODR = sinus[i];		
				}	
		break;
		case 2:
			GPIOC->ODR = 0x2;	
      sqaure(900);
		break;
		case 3:
			GPIOC->ODR = 0x3;
		break;
		case 4:
			GPIOC->ODR = 0x4;
			while(1){
				sawt();
			}
		break;	
		}
	delayMs(100);
}

void ports_init(void){
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  GPIOA->MODER = 0x00280300;
	
  GPIOA->AFR[1] &= 0x00000000;
  GPIOA->AFR[1] |= 0x00000770;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER = 0x55555555;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER |=  0X00005555;
	
	
}
void usart_init(){
  RCC->APB2ENR |= 0x00000010 ; /* USART1 clock */
  USART1->BRR = 0x0683; /* 9600 baud */
  USART1->CR1 |= 0x0004; /* enable Rx, 8-bit data */
  USART1->CR1 |= 0x0008; /* enable Tx, 8-bit data */
  USART1->CR2 = 0x0000; /*  stop bit 1 doone */
  USART1->CR3 = 0x0000; /* flow control nadarim */
  USART1->CR1 |= 0x2000; /* enable USART1 */
}
uint8_t usart_read(){
  while(!(USART1->SR & 0x0020)){}
  return USART1->DR;
}

void sine (void) {
    double Radians = (2 * 3.1415926535897)/ wave_LEN;
    for (int i = 0; i < wave_LEN; i++) {
        sinus[i] = 127.5 * (sin((Radians * i)) + 1) ;
			}
		return;
}
void sawt(){
		while (1) {
				for (int i = 0; i < 0x2000; i += 0x0002) {
							GPIOB->ODR = i & 0xFF; 
				}
		}
}

void sqaure(int freq){
  int temp;
  while(1){
      for (int i=0;i<2*freq;i++){
        temp = i % freq;
        if(temp < freq/2){
          GPIOB ->ODR =  0;
        }
        else{
            GPIOB ->ODR = 100;
        }
				//new delay
				delayforSq(280);
  }

}}
void delayforSq(int n) {
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 30; i++) ;
									
}
void delayMs(int n) {
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 20000; i++) ;
} 
//void draw_step(){
  //int i ;
 // for (i =0 ; i < tim ; i++){
   // if ( tim%t >= 0 && tim%t <= t/2){
     // GPIOC->ODR = 00000000;
   // }else if(tim%t <= t-1 && tim%t >= t/2){
     // GPIOC->ODR = 00000001;
    //}
 // }
//}