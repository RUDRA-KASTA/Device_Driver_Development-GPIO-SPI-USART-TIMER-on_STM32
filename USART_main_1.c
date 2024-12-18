

#include "stm32f10x.h"
#include "STM32F103C_USART_DRIVER.h"
#include "STM32F103C8T6_GPIO_DRIVER.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>




/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*////////////////////////////////////////////  CONFIGURING THE GPIO PIN AS USART PIN  //////////////////////////////////////////////*/
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


static USART_handle_t  USART2_handle;

void USART2_init(void)
{
	  GPIO_handle_t  GPIOhandle;
		GPIOhandle.pGPIOx = GPIOA;
		GPIOhandle.GPIO_pinconfig.GPIO_pin_mode = OUT_MODE_SPEED_10MHZ;
		GPIOhandle.GPIO_pinconfig.GPIO_op_type = OT_AF_PP;
		GPIOhandle.GPIO_pinconfig.GPIO_pin_number = GPIO_PIN_NO2 ;
		GPIO_init(&GPIOhandle);
	  
		USART2_handle.pUSARTx = USART2;
		USART2_handle.USARTconfig.USART_MODE = USART_MODE_TX;
		USART2_handle.USARTconfig.USART_NUM_OF_STOP_BIT = USART_1_STOP_BIT;
		USART2_handle.USARTconfig.USART_PARITY_BIT = USART_PARITY_DISABLE;
		USART2_handle.USARTconfig.USART_WORD_LENGTH = USART_8_BIT_DATA;
		USART2_handle.USARTconfig.USART_BAUDRATE = USART_STD_BAUD_19200	;
		USART2_handle.USARTconfig.USART_HW_FLOW_CONTROL = USART_HW_FLOW_CONTROL_NONE;
		USART_init(&USART2_handle);
}

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*///////////////////////////////////////////////////////////  MAIN FUNCTION  ///////////////////////////////////////////////////////*/
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/




int main(void)
{
	
	  ////////////////// 8bit integer /////////////////////
	
							USART2_init();
							USART_peripherialcontrol(USART2 , ENABLE);

							USART_send(USART2,170);
		
	
	
	/*
		//////////////////// 8bit string ////////////////////   
	
//			char cha[] ="ROBOCON";
			char cha[40] ="0";
	
			USART2_init();
			USART_peripherialcontrol(USART2 , ENABLE);
			
		//	USART_transmitdata(&USART2_handle , &cha , strlen(cha));
		while(1)
		{
			sprintf(cha,"t 0 3\n");
			USART_transmitdata(&USART2_handle , &cha , strlen(cha));
		}
	
	
		/*
		////////////////// 9bit integer /////////////////////
	
			uint16_t value = 351;
	
			USART2_init();
			USART_peripherialcontrol(USART2 , ENABLE);
			
			USART_transmitdata(&USART2_handle , &value , 1);
			*/
			
			
			/*
			////////////////// 9bit string /////////////////////
			
			char cha[] ="ROBOCON";
	
			USART2_init();
			USART_peripherialcontrol(USART2,ENABLE);
			
		  USART_transmitdata9bitstring(&USART2_handle ,&cha , strlen(cha));
			
			*/
}





/*

void USART2_GPIOints(void)
{
	  GPIO_handle_t  GPIOhandle;
	
		GPIOhandle.pGPIOx = GPIOA;
		GPIOhandle.GPIO_pinconfig.GPIO_pin_mode = GPIO_INPUT;
		GPIOhandle.GPIO_pinconfig.GPIO_ip_type = IT_FLOATING;
		GPIOhandle.GPIO_pinconfig.GPIO_pin_number = GPIO_PIN_NO3 ;
		GPIO_init(&GPIOhandle);
		
}




void USART2_init(void)
{
	
		USART2_handle.pUSARTx = USART2;
		USART2_handle.USARTconfig.USART_MODE = USART_MODE_RX;
		USART2_handle.USARTconfig.USART_NUM_OF_STOP_BIT = USART_1_STOP_BIT;
		USART2_handle.USARTconfig.USART_PARITY_BIT = USART_PARITY_DISABLE;
		USART2_handle.USARTconfig.USART_WORD_LENGTH = USART_8_BIT_DATA;
		USART2_handle.USARTconfig.USART_BAUDRATE = USART_STD_BAUD_115200	;
		USART2_handle.USARTconfig.USART_HW_FLOW_CONTROL = USART_HW_FLOW_CONTROL_NONE;
		USART_init(&USART2_handle);

}
*/




/*
int main(void)
{
		uint8_t value;
	
			USART2_GPIOints();
			USART2_init();

			USART_peripherialcontrol(USART2 , ENABLE);
	
		while(1)
		{
			USART_receivedata(&USART2_handle , &value , 1);
		}

}*/




