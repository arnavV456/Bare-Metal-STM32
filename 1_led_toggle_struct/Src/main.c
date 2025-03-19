#include <stdint.h>

#define PERIPH_BASE 				(0x40000000UL)
#define AHB1_PERIPH_OFFSET			(0x00020000UL)
#define AHB1_PERIPH_BASE			(PERIPH_BASE + AHB1_PERIPH_OFFSET)
#define GPIOA_OFFSET 				(0x0000UL)
#define GPIOA_BASE					(AHB1_PERIPH_BASE + GPIOA_OFFSET)
#define RCC_OFFSET					(0x00003800UL)
#define RCC_BASE					(AHB1_PERIPH_BASE + RCC_OFFSET)
#define GPIOAEN						(1U<<0)
#define PIN5						(1U<<5)
#define LED_PIN						PIN5
#define _IO							volatile

typedef struct{
	_IO uint32_t MODER;
	_IO uint32_t DUMMY[4];
	_IO uint32_t ODR;
}GPIO_TypeDef;

typedef struct{
	_IO uint32_t DUMMY[12];
	_IO uint32_t AHB1ENR;
}RCC_TypeDef;

#define GPIOA		((GPIO_TypeDef*) GPIOA_BASE)
#define RCC			((RCC_TypeDef*)  RCC_BASE)
int main()
{
	//1. Enable clock access for GPIOA
		RCC->AHB1ENR |= GPIOAEN;
	//2.Set PA5 as output pin
		GPIOA->MODER |= (1U<<10); // setting bit 10 as 1
		GPIOA->MODER &= ~(1U<<11); // setting bit 11 as 0
	while(1){
		GPIOA->ODR ^= LED_PIN;
		for(int i = 0;i<=1000000;i++){}
	}
}
