#include "stm32f4xx.h"

/*Using timer 2 */
/*TIMER 2 is connected to APB1 bus */

#define TIM2EN			(1U<<0)
#define CR1_CEN			(1U<<0)

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
