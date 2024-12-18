
/******************************************************  NECESSEY HEADER FILES  *****************************************************/

#include "stm32f10x.h"
#include <stdio.h>
#include <stdint.h>

/******************************************************  some standard macros *******************************************************/

#define  SET						  1
#define  ENABLE					  1
#define  RESET 						0
#define  DISABLE 					0
#define  FLAG_RESET  		  0
#define  FLAG_SET  				1

/******************************************************  INTERRUPT MACROS  *********************************************************/

#define NVIC_ISER0                       ((uint32_t*)0xE000E100)
#define NVIC_ISER1                       ((uint32_t*)0xE000E104)
#define NVIC_ISER2                       ((uint32_t*)0xE000E108)
#define NVIC_ISER3                       ((uint32_t*)0xE000E10C)

#define NVIC_ICER0                       ((uint32_t*)0XE000E180)
#define NVIC_ICER1                       ((uint32_t*)0XE000E184)
#define NVIC_ICER2                       ((uint32_t*)0XE000E188)
#define NVIC_ICER3                       ((uint32_t*)0XE000E18C)

#define NVIC_PR_BASE_ADDR                 ((uint32_t*)0xE000E400)

#define IRQ_N0_USART1                      37
#define IRQ_N0_USART2                      38
#define IRQ_N0_USART3                      39


/******************************************************  STATUS FLAG MACROS  ********************************************************/

#define PE      0
#define ORE     3
#define RXNE    5
#define TC      6
#define TXE     7

#define USART_PE_FLAG        (1<<PE)
#define USART_ORE_FLAG       (1<<ORE)
#define USART_RXNE_FLAG      (1<<RXNE)
#define USART_TC_FLAG        (1<<TC)
#define USART_TXE_FLAG       (1<<TXE)

/*******************************************************  USART MODE MACROS  ********************************************************/

#define USART_MODE_RX    0
#define USART_MODE_TX    1
#define USART_MODE_RXTX  2

/****************************************************  USART PARITY BIT MACROS  *****************************************************/

#define USART_EVEN_PARITY_EN  0
#define USART_ODD_PARITY_EN   1
#define USART_PARITY_DISABLE  2

/********************************************************  USART WORD LENGTH  *******************************************************/

#define USART_8_BIT_DATA  0
#define USART_9_BIT_DATA  1

/*******************************************************  USART NO. OF STOP BITS  ***************************************************/

#define USART_1_STOP_BIT    0
#define USART_005_STOP_BIT  1     							 /* 0.5 STOP BIT */
#define USART_2_STOP_BIT    2
#define USART_105_STOP_BIT  3     							 /* 1.5 STOP BIT */

/*******************************************************  USART HW FLOW CONTROL  ****************************************************/

#define USART_HW_FLOW_CONTROL_NONE  		 	0
#define USART_HW_FLOW_CONTROL_CTS    			1
#define USART_HW_FLOW_CONTROL_RTS    			2
#define USART_HW_FLOW_CONTROL_CTS_RTS    	3

/*****************************************************  SOME STANDARD BAUD RATES  ***************************************************/

#define USART_STD_BAUD_1200							1200
#define USART_STD_BAUD_2400							2400
#define USART_STD_BAUD_9600							9600
#define USART_STD_BAUD_19200 						19200
#define USART_STD_BAUD_38400 						38400
#define USART_STD_BAUD_57600 						57600
#define USART_STD_BAUD_115200 					115200
#define USART_STD_BAUD_230400 					230400
#define USART_STD_BAUD_460800 					460800
#define USART_STD_BAUD_921600 					921600
#define USART_STD_BAUD_2M 							2000000
#define SUART_STD_BAUD_3M 							3000000

/******************************************************  CLOCK ENABLE MACROS  ******************************************************/

#define	USART1_PCLK_EN()   		(RCC->APB2ENR |=(1<<14))
#define USART2_PCLK_EN()   		(RCC->APB1ENR |=(1<<17))
#define USART3_PCLK_EN()   		(RCC->APB1ENR |=(1<<18))
	
/******************************************************  CLOCK DISABLE MACROS  *****************************************************/

#define	USART1_PCLK_DI()   (RCC->APB2ENR &=~(1<<14))
#define USART2_PCLK_DI()   (RCC->APB1ENR &=~(1<<17))
#define USART3_PCLK_DI()   (RCC->APB1ENR &=~(1<<18))	
	
/**************************************************  USART CONFIGURATION STRUCTURE  ************************************************/

typedef struct
{
	uint16_t USART_MODE;
	uint32_t USART_BAUDRATE;
	uint16_t USART_PARITY_BIT;
	uint16_t USART_WORD_LENGTH;
	uint16_t USART_NUM_OF_STOP_BIT;
	uint16_t USART_HW_FLOW_CONTROL;
	
}USART_config_t;

/****************************************************  USART HANDLE STRUCTURE  *********************************************************/

typedef struct
{
	USART_TypeDef  *pUSARTx;
	USART_config_t  USARTconfig;
	
} USART_handle_t;

/*****************************************************  USART CLOCK CONTROL  **********************************************************/

void USART_periclockcontrol(USART_TypeDef *pUSARTx , uint16_t enordi);

/******************************************************  USART INT AND DEINT FUNCTION  ***************************************************/

void USART_init(USART_handle_t *USARThandle);
void USART_deint(USART_TypeDef *pUSARTx);

/******************************************************  USART SEND DATA  ***********************************************************/

void USART_transmitdata( USART_handle_t *pUSARThandle , uint8_t *pTXbuffer , uint32_t len);
void USART_transmitdata9bitstring(USART_handle_t *pUSARThandle , uint8_t *pTXbuffer , uint32_t len);
void USART_send(USART_TypeDef *pUSARTx ,uint8_t integer);

/******************************************************** USART RECEIVE DATA *****************************************************/

void USART_receivedata(USART_handle_t *pUSARThandle , uint8_t *pRXbuffer , uint32_t len);
uint16_t USART_receive(USART_TypeDef *pUSARTx);

/************************************************  USART PERIPHERIAL CONTROL FUNCTION  *************************************************/

void USART_peripherialcontrol(USART_TypeDef *pUSARTx ,uint16_t enordi);

/************************************************* USART FLAG STATUS FUNTION *************************************************/

uint8_t USART_getflagstatus(USART_TypeDef *pUSARTx, uint8_t flagname);

/******************************************************  USART SET BAUDRATE  ********************************************/

void USART_set_baudrate(USART_TypeDef *pUSARTx , uint32_t baud_rate);                                   

/******************************************************  USART INTERRUPTS  **********************************************/ 
 
void USART_IRQInterruptConfig(uint8_t IRQnumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQnumber, uint32_t IRQPriority);
void USART_IRQhandling(USART_handle_t *phandle);

void USART2_interrupt_config(void);


