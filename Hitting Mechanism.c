

/************************************************************* NECESSARY HEADER FILES  *****************************************************/

#include "STM32F103C_TIMER_DRIVER.h"
#include "STM32F103C_USART_DRIVER.h"
#include "STM32F103C_SPI_DRIVER.h"
#include <math.h>

uint16_t count1 = 0, count2 = 0 ;

void proxy_config(void);
void USART2config_send(void);

void proxy_config(void)
{
		GPIO_handle_t proxy;
		proxy.pGPIOx = GPIOA;
		proxy.GPIO_pinconfig.GPIO_pin_mode = GPIO_INPUT;
		proxy.GPIO_pinconfig.GPIO_ip_type = IT_WITH_PUPD;
		proxy.GPIO_pinconfig.GPIO_pin_number = 8;
		GPIO_init(&proxy);
	
		proxy.GPIO_pinconfig.GPIO_pin_number = 10;
		GPIO_init(&proxy);
}

void USART2config_send(void)
{
		GPIO_handle_t  GPIOhandle;
	
		GPIOhandle.pGPIOx = GPIOA;
		GPIOhandle.GPIO_pinconfig.GPIO_pin_mode = OUT_MODE_SPEED_10MHZ;
		GPIOhandle.GPIO_pinconfig.GPIO_op_type = OT_AF_PP;
		GPIOhandle.GPIO_pinconfig.GPIO_pin_number = GPIO_PIN_NO2 ;
		GPIO_init(&GPIOhandle);
	
		USART_handle_t  USART2_handle;
	
		USART2_handle.pUSARTx = USART2;
		USART2_handle.USARTconfig.USART_MODE = USART_MODE_TX;
		USART2_handle.USARTconfig.USART_NUM_OF_STOP_BIT = USART_1_STOP_BIT;
		USART2_handle.USARTconfig.USART_PARITY_BIT = USART_PARITY_DISABLE;
		USART2_handle.USARTconfig.USART_WORD_LENGTH = USART_8_BIT_DATA;
		USART2_handle.USARTconfig.USART_BAUDRATE = USART_STD_BAUD_19200	;
		USART2_handle.USARTconfig.USART_HW_FLOW_CONTROL = USART_HW_FLOW_CONTROL_NONE;
		USART_init(&USART2_handle);
	
			/****************** USART peripherial control **********************/
								USART_peripherialcontrol(USART2_handle.pUSARTx,ENABLE);
			/*******************************************************************/
}

uint16_t proxy1(void)
{
		return GPIO_Read(GPIOA,8);
}

uint16_t proxy2(void)
{
		return GPIO_Read(GPIOA,10);
}

int main()
{
		USART2config_send();
		USART_send(USART2,64);
		delay(TIM2,1000);
		
		proxy_config();
		USART_send(USART2,64 + 31);								//+35   	//+30				//+25				//+20
		
		while(proxy1() == 0);
		while(proxy2() == 1);
		while(proxy1() == 1);
		while(proxy2() == 1);
		while(proxy1() == 1);
	
	//	USART_send(USART2,64 - 10);							 //-15    	// -10      //-8				//-5
		//delay(TIM2,100);
		//while(proxy1() == 0);
	//	while(proxy1() == 1);
		USART_send(USART2,64 - 10);
		delay(TIM2,50);
		USART_send(USART2,64 - 2);
		while(proxy1() == 0);
		while(proxy1() == 1);
		USART_send(USART2,64);
	
}




 











//		USART2config_send();
//		USART_send(USART2,64);
//		
//		proxy_config();
//		USART_send(USART2,64 + 35);								//+35   	//+30				//+25				//+20
//		
//		while(proxy2() == 1);
//		while(proxy1() == 1);
//		while(proxy2() == 1);
//		while(proxy1() == 1);
//	
//		USART_send(USART2,64 - 15);							 //-15    	// -10      //-8				//-5
//		
//		while(proxy1() == 0);
//		while(proxy1() == 1);
//		USART_send(USART2,64 + 1);								    				//+1
//		while(proxy1() == 0);
//		while(proxy1() == 1);
//		USART_send(USART2,64);

