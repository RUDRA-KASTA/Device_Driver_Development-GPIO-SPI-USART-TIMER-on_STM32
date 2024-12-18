#include "STM32F103C_TIMER_DRIVER.h"
#include <stdint.h>
#include <stdio.h>

int x;
#define time(x) TIM4->CCR1=x

void GPIOasTIMinit(void);
void AFIO_use(void);
void PWM_(TIM_TypeDef *pTIMa);


void GPIOasTIMinit(void)
{
		GPIO_handle_t  ABC  ;																								//TIM4
		ABC.pGPIOx = GPIOB;
		ABC.GPIO_pinconfig.GPIO_pin_mode = OUT_MODE_SPEED_2MHZ;
		ABC.GPIO_pinconfig.GPIO_op_type = OT_AF_PP;
		ABC.GPIO_pinconfig.GPIO_pin_number = GPIO_PIN_NO6;
		GPIO_init(&ABC); 
}


void PWM_(TIM_TypeDef *pTIMa)
{
		GPIOasTIMinit();
		TIMER_handle_t  PWM;
		PWM.pTIMx = pTIMa;
	
		PWM.TIMERconfig.CCER_REGISTER.CC1EN = ENABLE;
		PWM.TIMERconfig.CH1_MODE.CH1_IPOPorMAPPING = CC_OP ;
		PWM.TIMERconfig.CH1_MODE.CH1_OP_MODE = PWM_MODE_1;
		PWM.TIMERconfig.PRESCALAR = (72-1);     
		PWM.TIMERconfig.ARR_VALUE = (uint16_t)(20000);
		//PWM.TIMERconfig.CCRx_REG.CCregister1 = (uint16_t)(time(x)); //(((2*PWM.TIMERconfig.ARR_VALUE*DC)/100) + 100);
		PWM.TIMERconfig.BDTR_MO = ENABLE;
		
		TIMER_init(&PWM);
		TIMER_countercontrol(pTIMa,ENABLE);
}
	

int main()
{	
	  TIMER_periclockcontrol(TIM4 , ENABLE);
		TIMER_periclockcontrol(TIM2 , ENABLE);
	
		delay(TIM3,2000);
	
		PWM_(TIM4);
	
					time(1500);
		delay(TIM3,3000);
					time(1000);
  	delay(TIM3,3000);
					time(2000);
		delay(TIM3,3000);
					time(1500);
		//		PWM_CH1(TIM1 , 50 , 10);
		//		delay(TIM2,2000);
		/*		PWM_CH1(TIM1 , 50 , 5);
				delay(TIM2,2000);
//				delay(TIM2,2000);
//				PWM_CH1(TIM1 , 50 , 5);*/
// 		}
	
}



