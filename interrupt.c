

/************************************************************* NECESSARY HEADER FILES  *****************************************************/

#include "STM32F103C8T6_GPIO_DRIVER.h"
#include "STM32F103C_USART_DRIVER.h"
#include <string.h>

int main(void)
{
		LED_config();
		GPIOB_5_interruptconfig();
			
			while(1)
			{	
				GPIO_Toggle(GPIOC,GPIO_PIN_NO13);
				delay(TIM1,3000);
			}
} 


void EXTI9_5_IRQHandler(void)
{
	   GPIO_IRQhandling(GPIO_PIN_NO5);
	   GPIO_Toggle(GPIOC,GPIO_PIN_NO13);
}




