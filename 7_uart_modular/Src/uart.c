#include "uart.h"



#define GPIOAEN			(1U<<0)
#define UART2EN			(1U<<17)

#define CR1_TE			(1U<<3)
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)

#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ

#define UART_BAUDRATE	115200

static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk,uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uar2_tx_init(void);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return(ch);
}


void uar2_tx_init(void)
{
	RCC->AHB1ENR |= GPIOAEN;	//Enable Clock access to the GPIO

	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	GPIOA->AFR[0] |= (1U<<8);   // Setting the Alternate function to AF07
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	RCC->APB1ENR |= UART2EN; 		//Enabling clock access to UART2 Module
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE); // configuring the baudrate
	USART2->CR1 = CR1_TE; 			//Setting the control register to enable transmitter
	USART2->CR1 |=CR1_UE;
}

void uart2_write(int ch)
{
	//Make sure transmit data register is empty
	while(!(USART2->SR & SR_TXE)){}
	//Write to the Transmit data register
	USART2->DR= (ch & 0xFF); // To write only the lower 8 bits to the data register
}



static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk,uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	  return ((PeriphClk+(BaudRate/2U))/BaudRate);
}


