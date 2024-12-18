
/************************************************************* NECESSARY HEADER FILES  *****************************************************/

#include "stm32f10x.h"
#include "STM32F103C_TIMER_DRIVER.h"
#include <stdint.h>
#include <stdio.h>

/*************************************************************** SOME USEFUL MACROS **************************************************************/

#define  PSC  36000
#define  ARR  2000
			
/************************************************************** CONFIGURING GPIO LED  *******************************************************/

void GPIOinit(void)
{
		GPIO_handle_t  led ;

		led.pGPIOx = GPIOC ;
		led.GPIO_pinconfig.GPIO_pin_mode = OUT_MODE_SPEED_2MHZ ;
		led.GPIO_pinconfig.GPIO_op_type = OT_GP_PP ;
		led.GPIO_pinconfig.GPIO_pin_number = GPIO_PIN_NO13 ;
		GPIO_init(&led);
}


/***************************************************************************************************************************************/
/***************************************************** TIMER MAIN FUNCTION  ************************************************************/
/***************************************************************************************************************************************/
	



 int main()
 {
//			GPIOinit();
//			GPIO_writetooutputpin(GPIOC,GPIO_PIN_NO13,HIGH);
		while(1)
		{
				delay(TIM1 , 1000);
//				GPIO_toggleoutputpin(GPIOC , GPIO_PIN_NO13);
		}
	
 } 
	 
 

 
 
