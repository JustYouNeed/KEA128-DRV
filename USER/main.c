# include "drv_gpio.h"

int main(void)
{
	uint32_t cnt = 0;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	ICS_C1|=ICS_C1_IRCLKEN_MASK; 		/* Enable the internal reference clock*/ 
	ICS_C3= 0x90;						/* Reference clock frequency = 31.25 KHz*/		
	while(!(ICS_S & ICS_S_LOCK_MASK));   /* Wait for PLL lock, now running at 40 MHz (1280 * 31.25Khz) */		
	ICS_C2|=ICS_C2_BDIV(1)  ; 			/*BDIV=2, Bus clock = 20 MHz*/
	ICS_S |= ICS_S_LOCK_MASK ; 			/* Clear Loss of lock sticky bit */	
	
	
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_B1;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	drv_gpio_Init(PORTB, &GPIO_InitStruct);
//	
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_E5;
//	drv_gpio_Init(PORTE, &GPIO_InitStruct);
//	
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_E0;
//	drv_gpio_Init(PORTE, &GPIO_InitStruct);
//	
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_D2;
//	drv_gpio_Init(PORTD, &GPIO_InitStruct);
	
	while(1)
	{
		cnt ++;
		if(cnt %40000 == 0)
		{
			cnt = 0;
//			drv_gpio_TogglePin(PORTB, GPIO_Pin_B1);
//			drv_gpio_TogglePin(PORTE, GPIO_Pin_E5);
//			drv_gpio_TogglePin(PORTE, GPIO_Pin_E0);
//			drv_gpio_TogglePin(PORTD, GPIO_Pin_D2);
		}
	}
}

