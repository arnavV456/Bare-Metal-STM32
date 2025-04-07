#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"


#define GPIOAEN						(1U<<0)
#define PIN5						(1U<<5)
#define LED_PIN						PIN5


static void exti_callback(void);


int main(void){
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10); // standard led code
	GPIOA->MODER &= ~(1U<<11);

	uart2_tx_init();
	pc13_exti_init();
	while(1)
	{

	}

}
static void exti_callback(void){
	printf("BTN Pressed\n\r");
	GPIOA->ODR ^= LED_PIN;
}

void EXTI15_10_IRQHandler(void)
{
	if((EXTI->PR & LINE13)!=0)
	{
		/*Clear the PR to arm it */
		EXTI->PR |= LINE13;
		/*do something....*/
		exti_callback();
	}
}



