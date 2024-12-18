
#include <stdio.h>
#include <stdint.h>
#include "stm32f10x.h"

/**************************************************  some standart macros ***************************************************************/

#define  SET  1
#define  ENABLE  1
#define  RESET 0
#define  DISABLE 0
#define  FLAG_RESET  0
#define  FLAG_SET  1


/***************************************************  status flag macros   *****************************************************************/

#define SPI_TXE    1
#define SPI_RXNE   0
#define SPI_BUSY   7
#define SPI_CRCERR 4
#define SPI_MODF	 5
#define SPI_OVR		 6

/****************************************************   clock enable macros   *************************************************************/
																											 
#define  SPI1_PCLK_EN()  (RCC->APB2ENR |=(1<<12))
#define  SPI2_PCLK_EN()  (RCC->APB1ENR |=(1<<14))
#define  SPI3_PCLK_EN()  (RCC->APB1ENR |=(1<<15))

/*****************************************************   clock disable macros   **********************************************************/
																											 
#define  SPI1_PCLK_DI()  (RCC->APB2ENR &=~(1<<12))		
#define  SPI2_PCLK_DI()  (RCC->APB1ENR &=~(1<<14))
#define  SPI3_PCLK_DI()  (RCC->APB1ENR &=~(1<<15))

/*****************************************************   SPI_device modes    ************************************************************/

#define  SPI_DEVICE_MODE_MASTER   1
#define  SPI_DEVICE_MODE_SLAVE    0

/***************************************************   SPI_configurations    *************************************************************/ 

#define  SPI_CONFIGURATION_FD        0
#define  SPI_CONFIGURATION_HD				 1
#define  SPI_CONFIGURATION_RXONLY    2

/*********************************************** *****  SPI_clock speed    **************************************************************/

#define  SPI_CLK_SPEED_DIV2        0
#define  SPI_CLK_SPEED_DIV4        1
#define  SPI_CLK_SPEED_DIV8        2
#define  SPI_CLK_SPEED_DIV16       3
#define  SPI_CLK_SPEED_DIV32       4 
#define  SPI_CLK_SPEED_DIV64       5
#define  SPI_CLK_SPEED_DIV128      6
#define  SPI_CLK_SPEED_DIV256      7

/*****************************************************    SPI_DFF     ********************************************************************/

#define  SPI_DFF_8BITS    0
#define  SPI_DFF_16BITS   1

/****************************************************   SPI_CLOCK POLARITY   *************************************************************/

#define  SPI_CPHA_LOW  0
#define  SPI_CPHA_HIGH  1

/***************************************************    SPI_CLOCK PHASE    ***************************************************************/

#define  SPI_CPOL_LOW  0
#define  SPI_CPOL_HIGH  1

/****************************************************   SPI_SSM_BITS    ******************************************************************/

#define  SPI_SSM_EN   1
#define  SPI_SSM_DI   0

/***************************************************   FRAME FORMATE   ****************************************************************/

#define  SPI_MSB_TF  0
#define  SPI_LSB_TF  1 

/***************************************************  status flag macros   *************************************************************/

#define SPI_TXE_FLAG   (1<<(SPI_TXE))
#define SPI_RXE_FLAG   (1<<(SPI_RXNE))
#define SPI_BUSY_FLAG  (1<<(SPI_BUSY))


/*************************************************   CONFIGURATION STRUCTURE FOR SPI ********************************************/
																									
 typedef  struct
 {
			uint16_t  SPI_CPHA;
			uint16_t  SPI_CPOL;
			uint16_t  SPI_CLKSPEED;
			uint16_t  SPI_MODE;
			uint16_t  SPI_CONFIGURATION;
			uint16_t  SPI_FRAMEFORMATE;
			uint16_t  SPI_SSM;
			uint16_t  SPI_DFF;
		
 }SPI_config_t;
 
 typedef struct
 {
			SPI_TypeDef  *pSPIx;
			SPI_config_t  SPIConfig;
	 
 }  SPI_handle_t;
 
 
/****************************************************   periperial clock setup  ********************************************************/

void SPI_periclockcontrol(SPI_TypeDef *pSPIx, uint8_t enordi);

 
/*******************************************************   init and de-init    **********************************************************/

void SPI_init(SPI_handle_t *pSPIhandle);
void SPI_deint(SPI_TypeDef *pSPIx);
 
 
 /**********************************************************   status flag   ******************************************************/
 
uint8_t   SPI_getflagstatus(SPI_TypeDef *pSPIx, uint8_t flagname);
 
 
/*******************************************************  RECEVING AND SENDING DATA  ******************************************************/ 

void SPI_transmitdata(SPI_TypeDef *pSPIx, uint8_t *pTXbuffer, uint8_t len);
void SPI_transmitdata2(SPI_TypeDef *pSPIx, uint16_t *pTXbuffer, uint8_t len);
void SPI_receivedata(SPI_TypeDef *pSPIx, uint8_t *pRXbuffer, uint8_t len);
  
	
/*****************************************************   SPI configuration functions   *************************************************/
 
void SPI_peripherialcontrol(SPI_TypeDef *pSPIx, uint8_t enordi);
void SPI_SSIconfig(SPI_TypeDef *pSPIx, uint8_t enordi);
void SPI1_GPIOinits(void);
void SPI1_inits(void);
void SPI1_clock(void);





void function(void);


