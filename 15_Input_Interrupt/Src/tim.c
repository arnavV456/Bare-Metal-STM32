#include "stm32f4xx.h"

/*Using timer 2 */
/*TIMER 2 is connected to APB1 bus */

#define TIM2EN			(1U<<0)
#define TIM3EN			(1U<<1)
#define CR1_CEN			(1U<<0)
#define GPIOA_EN		(1U<<0)
#define CCER_CC1S		(1U<<0)
#define CCER_CC1E		(1U<<0)


void timer2_1hz_init(void)
{
	/*Enable clock access*/
	RCC->APB1ENR |= TIM2EN;
	/*Set prescaler*/
	TIM2->PSC = 1600-1;		// 16000000/1600 = 10000
	/*set auto reload value*/
	TIM2->ARR = 10000-1;	// 10000/10000 = 1Hz
	/*clear counter*/
	TIM2->CNT = 0;
	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;

}

void timer2_pa5_output_compare(void)
{
	/*Configuring PA5 in alternate function mode AF01*/
	RCC->AHB1ENR = GPIOA_EN;
	GPIOA->MODER &=~(1U<<10);
	GPIOA->MODER |=(1U<<11);
	GPIOA->AFR[0] |= (1U<<20);

	 /*Enable clock access*/
	RCC->APB1ENR |= TIM2EN;
	/*Set prescaler*/
	TIM2->PSC = 1600-1;		// 16000000/1600 = 10000
	/*set auto reload value*/
	TIM2->ARR = 10000-1;	// 10000/10000 = 1Hz

	/*Set output compare toggle mode*/
	TIM2->CCMR1 |= (1U<<4);
	TIM2->CCMR1 |= (1U<<5);
	/*Enable timer 2 channel 1 since PA5 is connected to TIM2_CH1*/
	TIM2->CCER |= (1U<<0);


	/*clear counter*/
	TIM2->CNT = 0;
	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;

}
void timer3_pa6_input_capture(void)
{
	/*Timer 3 channel 1 is connected to PA6 alternate function AF2*/

	/*Enable clock access*/
	RCC->AHB1ENR = GPIOA_EN;

	/*Alternate function*/
	GPIOA->MODER &=~(1U<<12);
	GPIOA->MODER |= (1U<<13);

	/*Set the alternate function to AF02*/
	GPIOA->AFR[0] &=~(1U<<27);
	GPIOA->AFR[0] &=~(1U<<26);
	GPIOA->AFR[0] &=~(1U<<24);
	GPIOA->AFR[0] |= (1U<<25);

	/*Enable clock access to timer 3*/
	RCC->APB1ENR = TIM3EN;

	/*Set prescaler*/
	TIM3->PSC = 16000-1;

	/*Set ch1 to input capture */
	TIM3->CCER = CCER_CC1S;

	/*Set ch1 to capture at rising edge*/
	TIM3->CCER = CCER_CC1E;

	/*Enable timer 3*/
	TIM3->CR1= CR1_CEN;



}
