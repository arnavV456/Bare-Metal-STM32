/*
 * systick.c
 *
 *  Created on: Mar 22, 2025
 *      Author: verma
 */
#include "stm32f4xx.h"

#define SYSTICK_LOAD_VALUE 		16000
#define CTRL_ENABLE 			(1U<<0)
#define CTRL_CLKSRC				(1U<<2)
#define CTRL_COUNTFLAG			(1U<<16)



void systickDelayMs(int delay)
{
	/*Configure systick*/
	/*Reload with number of clocks per */
	SysTick->LOAD = SYSTICK_LOAD_VALUE;

	/*Clear systick current value register*/
	SysTick->VAL= 0;
	/*Enable systick and select internal clock source*/
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i =0; i<delay; i++)
	{
		while((SysTick->CTRL & CTRL_COUNTFLAG)==0){}
	}
	SysTick->CTRL = 0;

}

