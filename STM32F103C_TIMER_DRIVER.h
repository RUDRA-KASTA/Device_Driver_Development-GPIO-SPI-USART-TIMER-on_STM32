
#include "stm32f10x.h"				/*** device header file ***/
#include "STM32F103C8T6_GPIO_DRIVER.h"
#include <stdio.h>
#include <stdint.h>

/**************************************************  some standard macros ****************************************************/

#define  SET						  1
#define  ENABLE					  1
#define  RESET 						0
#define  DISABLE 					0
#define  FLAG_RESET  		  0
#define  FLAG_SET  				1
#define  LOW              0
#define  HIGH             1

/***********************************************  CAPTURE/COMPARE POLARITY MACROS  *******************************************/

#define NONINVERTED       0
#define INVERTED          1

/***********************************************  CAPTURE/COMPARE MAPPING MACROS  ********************************************/

#define TIMER_CC1_OP                  0
#define TIMER_CC1_IP_IC1onTI1         1
#define TIMER_CC1_IP_IC1onTI2         2

#define TIMER_CC2_OP                  0
#define TIMER_CC2_IP_IC2onTI2         1
#define TIMER_CC2_IP_IC2onTI1         2

/***********************************************  Counter mode on TI1 and TI2 ************************************************/

#define TIMER_SMS_DISABLE             0
#define TIMER_SMS_COUNTonTI2          1
#define TIMER_SMS_COUNTonTI1          2
#define TIMER_SMS_COUNTonBOTH         3

#define CC_OP                         0
#define CC_IP_SAME_MAPPING						1
#define CC_IP_OPP_MAPPING			  			2

#define PWM_MODE_1										6
#define PWM_MODE_2										7

#define ARR_NOTBUFF										0
#define ARR_BUFF											1

#define POL_OC1_ACTIVE_LOW						1
#define POL_OC1_ACTIVE_HIGH						0

#define CMS_EA_MODE										0
#define CMS_CA_MODE1									1
#define CMS_CA_MODE2									2
#define CMS_EA_MODE3									3


/**************************************************** CLOCK ENABLE MACROS ***************************************************/

#define TIMER1_PCLK_EN()      	(RCC->APB2ENR |=(1<<11))
#define TIMER2_PCLK_EN()      	(RCC->APB1ENR |=(1<<0))
#define TIMER3_PCLK_EN()      	(RCC->APB1ENR |=(1<<1))
#define TIMER4_PCLK_EN()      	(RCC->APB1ENR |=(1<<2))

/**************************************************** CLOCK DISABLE MACROS ***************************************************/

#define TIMER1_PCLK_DI()      	(RCC->APB2ENR &=~(1<<11))
#define TIMER2_PCLK_DI()      	(RCC->APB1ENR &=~(1<<0))
#define TIMER3_PCLK_DI()      	(RCC->APB1ENR &=~(1<<1))
#define TIMER4_PCLK_DI()      	(RCC->APB1ENR &=~(1<<2))

/*************************************************** COUNTER MODE OF THE TIMER *************************************************/

#define TIM_COUNTERMODE_UP      		0X00000000U
#define TIM_COUNTERMODE_DOWN    		TIM_CR1_DIR
#define TIM_COUNTERMODE_CALN1       TIM_CR1_CMS_0
#define TIM_COUNTERMODE_CALN2       TIM_CR1_CMS_1
#define TIM_COUNTERMODE_CALN3       TIM_CR1_CMS

/****************************************************** TIMER STAUTUS Flag MACROS ************************************************/

#define UIF  0
#define TIMER_UIF_FLAG  (1<<UIF)

/********************************************* MEMBER STRUCTURE OF CONFIGURATION STRUCTURE ****************************************/

typedef struct
{
	uint16_t  CCregister1;
	uint16_t  CCregister2;
	uint16_t  CCregister3;
	uint16_t  CCregister4;
	
}TIMx_CCRxREGISTER;

typedef struct
{
  uint16_t CH1_IPOPorMAPPING;
	uint16_t CH1_IP_PRESCALAR;
	uint16_t CH1_IP_FILTER;
	uint16_t CH1_OP_FE;
	uint16_t CH1_OP_PRELOADEN;
	uint16_t CH1_OP_MODE;
	
	
}CH1_MODE_REG;

typedef struct
{
  uint16_t CH2_IPOPorMAPPING;
	uint16_t CH2_IP_PRESCALAR;
	uint16_t CH2_IP_FILTER;
	uint16_t CH2_OP_FE;
	uint16_t CH2_OP_PRELOADEN;
	uint16_t CH2_OP_MODE;
	
}CH2_MODE_REG;

typedef struct
{
  uint16_t CH3_IPOPorMAPPING;
	uint16_t CH3_IP_PRESCALAR;
	uint16_t CH3_IP_FILTER;
	uint16_t CH3_OP_FE;
	uint16_t CH3_OP_PRELOADEN;
	uint16_t CH3_OP_MODE;
	
}CH3_MODE_REG;

typedef struct
{
  uint16_t CH4_IPOPorMAPPING;
	uint16_t CH4_IP_PRESCALAR;
	uint16_t CH4_IP_FILTER;
	uint16_t CH4_OP_FE;
	uint16_t CH4_OP_PRELOADEN;
	uint16_t CH4_OP_MODE;
	
}CH4_MODE_REG;

typedef struct
{
	uint16_t  CC1EN;
	uint16_t  CC1POLARITY;
	uint16_t  CC2EN;
	uint16_t  CC2POLARITY;
	uint16_t  CC3EN;
	uint16_t  CC3POLARITY;
	uint16_t  CC4EN;
	uint16_t  CC4POLARITY;
	
}TIMx_CCER_REG;

typedef struct
{
	uint16_t UPDATE_DISABLE;
	uint16_t UPDATE_REQ_SRC;
	uint16_t ONE_pulse_mode;
	uint16_t CAMODE_SEL;
	uint16_t ARPE;
	uint16_t CLKDIV;
	
}TIMx_CR1_REG;

/*************************************************** TIMER CONFIG STRUCTURE ****************************************************/

typedef struct
{
	uint16_t       BDTR_MO;
	uint16_t       CMS;
	uint16_t       EGR;	
	uint16_t  		 AVEMODESELECT;
	uint16_t 			 PRESCALAR;
	uint16_t 			 ARR_VALUE;
	uint16_t  		 UPDATE_GENERATIOIN;
	uint16_t       SLAVEMODESELECT;
	TIMx_CCER_REG  CCER_REGISTER;
	CH1_MODE_REG   CH1_MODE;
	CH2_MODE_REG   CH2_MODE;
	CH3_MODE_REG   CH3_MODE;
	CH4_MODE_REG   CH4_MODE;
	TIMx_CCRxREGISTER  CCRx_REG;
	TIMx_CR1_REG       CR1_REG;
	
}TIMER_config_t; 

/****************************************************** TIMER HANDLE STRUCTURE **************************************************/

typedef struct
{
		TIM_TypeDef  *pTIMx;
		TIMER_config_t   TIMERconfig;
	
}TIMER_handle_t;

/****************************************************** TIMER CLOCK CONTROL *************************************************/

void TIMER_periclockcontrol(TIM_TypeDef *pTIMxx , uint8_t enordi);

/************************************************** TIMER PREPHERIAL CONTROL ************************************************/

void TIMER_countercontrol(TIM_TypeDef *pTIMx , uint8_t enordi);

/***************************************************** TIMER INIT FUNCTIONO **************************************************/

void TIMER_init(TIMER_handle_t *pTIMERhandle);
void TIMER_delay_init(TIMER_handle_t *pTIMERhandle);

/************************************************** TIMER FLAG STATUS FUNCTION ********************************************/

uint8_t TIMER_getflagstatus(TIM_TypeDef *pTIMx , uint16_t flagname);

/****************************************************** MAIN FILES FUNCTIONS ***************************************************/
		
void TIMER2_init(void);
void GPIOinit(void);
void CaptureorCompare_ENABLE(void);
void delay(TIM_TypeDef *pTIMa , uint32_t sec);
void PWM_CH1(TIM_TypeDef *pTIMa ,uint16_t fre , uint16_t DC );
void PWM_CH3(TIM_TypeDef *pTIMa ,uint16_t fre , uint16_t DC );
uint8_t ENCODER_DIR_read(void);





