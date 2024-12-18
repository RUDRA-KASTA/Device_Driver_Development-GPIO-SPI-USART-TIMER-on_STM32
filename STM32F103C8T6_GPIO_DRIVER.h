#include "stm32f10x.h"
#include <stdio.h>
#include <stdint.h>


/**************************************************  SOME STANDARD MACROS  ***********************************************/

#define  LOW 							0
#define  HIGH							1
#define  SET              1
#define  ENABLE 		 		  1
#define  RESET 						0
#define  DISABLE 					0
#define  CRL_R            0
#define  CRH_R            1
#define  NO_REMAPPING       0
#define  PARTIAL_REMAPPING  1
#define  FULL_REMAPPING     3

/*********************************************** MACROS TO RESET GPIO PERIPHERIALS *****************************************/

#define GPIOA_REG_RESET()     do{(RCC->APB2RSTR |=(1<<2));  (RCC->APB2RSTR &=~(1<<2));}while(0)
#define GPIOB_REG_RESET()     do{(RCC->APB2RSTR |=(1<<3));  (RCC->APB2RSTR &=~(1<<3));}while(0)
#define GPIOC_REG_RESET()     do{(RCC->APB2RSTR |=(1<<4));  (RCC->APB2RSTR &=~(1<<4));}while(0)
#define GPIOD_REG_RESET()     do{(RCC->APB2RSTR |=(1<<5));  (RCC->APB2RSTR &=~(1<<5));}while(0)
#define GPIOE_REG_RESET()     do{(RCC->APB2RSTR |=(1<<6));  (RCC->APB2RSTR &=~(1<<6));}while(0)

/************************************************* GPIO PERIPHERIAL CLOCK ENABLE *******************************************/

#define  GPIOA_PCLK_EN()  (RCC->APB2ENR |=(1<<2))
#define  GPIOB_PCLK_EN()  (RCC->APB2ENR |=(1<<3))
#define  GPIOC_PCLK_EN()  (RCC->APB2ENR |=(1<<4))
#define  GPIOD_PCLK_EN()  (RCC->APB2ENR |=(1<<5)) 
#define  GPIOE_PCLK_EN()  (RCC->APB2ENR |=(1<<6))
#define  GPIOF_PCLK_EN()  (RCC->APB2ENR |=(1<<7))
#define  GPIOG_PCLK_EN()  (RCC->APB2ENR |=(1<<8))
#define  AFIO_EN()        (RCC->APB2ENR |=(1<<0))

/************************************************* GPIO PERIPHERIAL CLOCK DISABLE *******************************************/

#define  GPIOA_PCLK_DI()  (RCC->APB2ENR &=~(1<<2))
#define  GPIOB_PCLK_DI()  (RCC->APB2ENR &=~(1<<3))
#define  GPIOC_PCLK_DI()  (RCC->APB2ENR &=~(1<<4))
#define  GPIOD_PCLK_DI()  (RCC->APB2ENR &=~(1<<5))
#define  GPIOE_PCLK_DI()  (RCC->APB2ENR &=~(1<<6))
#define  GPIOF_PCLK_DI()  (RCC->APB2ENR &=~(1<<7))
#define  GPIOG_PCLK_DI()  (RCC->APB2ENR &=~(1<<8))

/************************************************* GPIO PIN NUMBER MACROS *******************************************************/

#define GPIO_PIN_NO0   0
#define GPIO_PIN_NO1   1
#define GPIO_PIN_NO2   2
#define GPIO_PIN_NO3   3
#define GPIO_PIN_NO4   4 
#define GPIO_PIN_NO5   5 
#define GPIO_PIN_NO6   6
#define GPIO_PIN_NO7   7
#define GPIO_PIN_NO8   8
#define GPIO_PIN_NO9   9
#define GPIO_PIN_NO10  10
#define GPIO_PIN_NO11  11
#define GPIO_PIN_NO12  12
#define GPIO_PIN_NO13  13
#define GPIO_PIN_NO14  14
#define GPIO_PIN_NO15  15

/******************************************************** GPIO PORT NUMBER ******************************************************/

#define GPIO_PORT_A    0
#define GPIO_PORT_B    1
#define GPIO_PORT_C    2
#define GPIO_PORT_D    3
#define GPIO_PORT_E    4

/***************************************************** GPIO MODE MACROS *********************************************************/

#define GPIO_INPUT                  0
#define OUT_MODE_SPEED_10MHZ        1
#define OUT_MODE_SPEED_2MHZ         2
#define OUT_MODE_SPEED_50MHZ        3
#define GPIO_IT_MODE_FT             4
#define GPIO_IT_MODE_RT             5
#define GPIO_IT_MODE_FRT            6

/****************************************************  GPIO IP TYPE  *************************************************************/

#define IT_ANALOG									0
#define IT_FLOATING								1
#define IT_WITH_PUPD							2
#define IT_RESERVED								3

/******************************************************* GPIO OP TYPE *************************************************************/

#define OT_GP_PP     0
#define OT_GP_OD     1
#define OT_AF_PP	   2
#define OT_AF_OD     3

/****************************************************  GPIO CONFIGURATION STRUCTURE  *******************************************************/

typedef struct
{
	uint32_t GPIO_pin_number; 																
	uint32_t GPIO_pin_mode;           	                      
	uint32_t GPIO_ip_type;																		
	uint32_t GPIO_op_type;																		
	
}GPIO_pinconfig_t;

/**********************************************************  GPIO HANDLE STRUCTURE  *******************************************************/

typedef struct
{
   GPIO_TypeDef  *pGPIOx;                        
	 GPIO_pinconfig_t  GPIO_pinconfig;
	
}GPIO_handle_t;   

/****************************************************  AFIO CONFIGURATION STRUCTURE  *******************************************************/

//typedef struct
//{
//	uint16_t  SPI1_REMAP;
//	uint16_t  TIM1_REMAP;
//	uint16_t  TIM3_REMAP;

//}AFIO_pinconfig_t;

/**********************************************************  AFIO HANDLE STRUCTURE  *******************************************************/

//typedef struct
//{
//		AFIO_TypeDef *pAFIO;
//		AFIO_pinconfig_t  AFIO_pinconfig;

//}AFIO_handle_t;


/*******************************************************  GPIO CLOCK CONTROL  ********************************************************/

void GPIO_periclockcontrol(GPIO_TypeDef *pGPIOx, uint8_t enordi);

/************************************************  GPIO/AFIO INT AND DE INT FUNCTION  ************************************************/

void GPIO_init(GPIO_handle_t *pGPIOhandle);
void GPIO_deint(GPIO_TypeDef *pGPIOx);
//void AFIO_TIM3_init(AFIO_handle_t *pAFIOhandle);
//void AFIO_SPI1_init(AFIO_handle_t *pAFIOhandle);

/******************************************************  GPIO READ AND WRITE  ********************************************************/
	
uint8_t GPIO_readfrominputpin(GPIO_TypeDef *pGPIOx, uint8_t pinnumber);
void GPIO_writetooutputpin(GPIO_TypeDef *pGPIOx, uint8_t pinnumber, uint8_t value);
void GPIO_writetooutputport(GPIO_TypeDef *pGPIOx, uint16_t value);
void GPIO_toggleoutputpin(GPIO_TypeDef *pGPIOx , uint8_t pin_number);

void GPIO_IRQhandling(uint8_t pinnumber);
void GPIO_Toggle(GPIO_TypeDef *pGPIOx , uint8_t pin_number);
void GPIO_Write(GPIO_TypeDef *pGPIOx, uint8_t pinnumber, uint8_t value);

