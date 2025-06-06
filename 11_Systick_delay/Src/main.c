#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"



#define GPIOAEN						(1U<<0)
#define PIN5						(1U<<5)
#define LED_PIN						PIN5


int main(void){
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U<<10); // standard led code
	GPIOA->MODER &= ~(1U<<11);
	uart2_tx_init();

	while(1)
	{

		GPIOA->ODR ^= LED_PIN;
		printf("DELAY");
		systickDelayMs(2000);	}

}




