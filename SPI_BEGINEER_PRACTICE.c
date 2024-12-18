
#include "stm32f10x.h"
#include "STM32F103C_SPI_DRIVER.h"
#include "STM32F103C_TIMER_DRIVER.h"
#include <string.h>

       // SPI2           			    //	SPI1												    //	SPI1  mapping
			                                                               
	//	NSS      B12            //	NSS                                 //	NSS      PA15
	//	MISO     B14            //	CLK      PA5                        //	CLK      PB3
	//	MOSI     B15            //	MISO     PA6                        //	MISO     PB4
	//	CLK      B13            //	MOSI                                 //	MOSI     PB5

	/******************************************configure GPIOA pins as SPI1 pins*********************************************************/



void 	SPI1_GPIOinits(void)
{
		GPIO_handle_t    SPIpin ;
	
		SPIpin.pGPIOx = GPIOA;
	  SPIpin.GPIO_pinconfig.GPIO_pin_mode = OUT_MODE_SPEED_50MHZ;
		SPIpin.GPIO_pinconfig.GPIO_op_type = OT_AF_PP ;
		SPIpin.GPIO_pinconfig.GPIO_pin_number = GPIO_PIN_NO7;
	  GPIO_init(&SPIpin);																														//MOSI
	
		SPIpin.GPIO_pinconfig.GPIO_pin_mode = GPIO_INPUT;
		SPIpin.GPIO_pinconfig.GPIO_ip_type = IT_FLOATING;
		SPIpin.GPIO_pinconfig.GPIO_pin_number = GPIO_PIN_NO6;
	  GPIO_init(&SPIpin);																														//MISO
					
		SPIpin.GPIO_pinconfig.GPIO_pin_mode = OUT_MODE_SPEED_50MHZ;
		SPIpin.GPIO_pinconfig.GPIO_op_type = OT_GP_PP;
		SPIpin.GPIO_pinconfig.GPIO_pin_number = GPIO_PIN_NO4;
	  GPIO_init(&SPIpin);																														//NSS
}

void SPI1_clock(void)
{
		GPIO_handle_t  SPIclk ;
	 
		SPIclk.pGPIOx = GPIOA	;
		SPIclk.GPIO_pinconfig.GPIO_pin_mode = OUT_MODE_SPEED_50MHZ;
		SPIclk.GPIO_pinconfig.GPIO_op_type = OT_AF_PP ;
		SPIclk.GPIO_pinconfig.GPIO_pin_number = GPIO_PIN_NO5 ;
		GPIO_init(&SPIclk);																														//clock
	
}
/****************************************************    configuration of SPI1    ********************************************************/

void SPI1_inits(void)
{
		SPI_handle_t  SPIhandle;
	
		SPIhandle.pSPIx = SPI1;
		SPIhandle.SPIConfig.SPI_CONFIGURATION = SPI_CONFIGURATION_FD;
		SPIhandle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
		SPIhandle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
		SPIhandle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;	
		SPIhandle.SPIConfig.SPI_MODE = SPI_DEVICE_MODE_MASTER;
		SPIhandle.SPIConfig.SPI_SSM = SPI_SSM_DI;	
		SPIhandle.SPIConfig.SPI_FRAMEFORMATE = SPI_MSB_TF;
		SPIhandle.SPIConfig.SPI_CLKSPEED =  SPI_CLK_SPEED_DIV64	;
	
		SPI_init(&SPIhandle); 
}	

int main(void)
{				
	
						uint8_t value;
						value = 66;

						SPI1_GPIOinits();
						SPI1_inits();
						SPI1->CR2 |= (1<<2);
						SPI1_clock();
						SPI_peripherialcontrol(SPI1,ENABLE); 
						GPIO_Write(GPIOA,4,LOW);
						
					//		SPI_send(SPI1,&value,1);
					//  	delay(TIM1,5000);
					//	SPI_communicate(SPI1,0); 
						GPIO_Write(GPIOA,4,HIGH);
	
						while(SPI_getflagstatus(SPI1,SPI_BUSY_FLAG));
		
}



/*

void function(void)
		{	uint8_t i=0;
			
					while(i<14)
					{		uint8_t count=0;
						while (count%2 ==0)
						{
						SPI_peripherialcontrol(SPI1,DISABLE);
							count++;
							i++;
						}
						while (count%2 ==1)
						{
						SPI_peripherialcontrol(SPI1,ENABLE);
							count++;
							i++;
						}
					}
		}

*/







/*



void twotimeonedata(uint32_t num)
{
	uint16_t  v=65535, num2;
   num2 = num-65535;
	
	SPI_transmitdata2(SPI1,&v,1);
	SPI_transmitdata2(SPI1,&num2,1);

}

*/