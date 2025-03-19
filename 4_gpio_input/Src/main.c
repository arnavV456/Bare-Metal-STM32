#include "stm32f4xx.h"

#define GPIOAEN			(1U<<0)
#define GPIOCEN			(1U<<2)

#define PIN5			(1U<<5)
#define PIN13			(1U<<13)
#define LED_PIN			(PIN5)
#define BTN_PIN			(PIN13)

// Push button - Port C and Pin 13

int main(){
	RCC->AHB1ENR |= GPIOAEN;	//enabling clock for gpio a
	RCC->AHB1ENR |= GPIOCEN;	//enabling clock for gpio c
	GPIOA->MODER |= 1U<<10;		// setting pin 5 as output
	GPIOA->MODER &= ~(1U<<11);
	GPIOC->MODER &= ~(1U<<26);	//setting pin 13 as input
	GPIOC->MODER &= ~(1U<<27);

	while(1){
	if(GPIOC->IDR != 0)
	GPIOA->BSRR = LED_PIN;			// set pin 5
	else
	GPIOA->BSRR = (1U<<(5+16));    // Reset pin 5
	}
}

