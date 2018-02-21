/**
  *******************************************************************************************************
  * File Name: drv_pit.c
  * Author: Vector
  * Version: V1.0.0
  * Date: 2018-2-1
  * Brief: KEA128оƬGPIO�ײ���������
  *******************************************************************************************************
  * History
  *		1.Data: 2018-2-1
  *     Author: Vector
  *     Mod: �����ļ�,��ӻ�������
	*		
	*		2.Data: 2018-2-9
	*			Author:	Vector
	*			Mod: ����º���drv_gpio_PinAFConfig,�����������ŵĸ��ù���
  *
  *******************************************************************************************************
  */
	
# include "drv_gpio.h"

/*
*********************************************************************************************************
*                                       drv_gpio_Init   
*
* Description: ��ʼ��һ��GPIO����
*             
* Arguments  : 1> PORTx: GPIO�˿�ָ��, PORTA~PORTI
*              2> GPIO_InitStruct: GPIO�������ýṹ��ָ��
*
* Reutrn     : None.
*
* Note(s)    : һ��ֻ������һ������
*********************************************************************************************************
*/
void drv_gpio_Init(GPIO_Type *PORTx, GPIO_InitTypeDef *GPIO_InitStruct)
{
	PORTx->PIDR |= ((uint32_t)1 << GPIO_InitStruct->GPIO_Pin);	/*  �Ƚ�ֹ����  */
	
	/*  ���ö˿����ݷ���Ĵ���,����Ϊ��Ӧ������/���ģʽ  */
	PORTx->PDDR |= (GPIO_InitStruct->GPIO_Mode << GPIO_InitStruct->GPIO_Pin);
		
	if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN)		/*  �������Ϊ�����������빦��  */
		PORTx->PIDR &= ~((uint32_t)1 << GPIO_InitStruct->GPIO_Pin);
	
	/*  �������������  */
	if(GPIO_InitStruct->GPIO_PuPd == GPIO_PuPd_UP)
	{
		/*  GPIOA,GPIOB,���������õļĴ�����ͬ  */
		if(GPIOA == PORTx) PORT->PUE0 |= 1 << GPIO_InitStruct->GPIO_Pin;
		else if(GPIOB == PORTx) PORT->PUE1 |= 1 << GPIO_InitStruct->GPIO_Pin;
		else	PORT->PUE2 |= 1 << GPIO_InitStruct->GPIO_Pin;
	}
	
	/*  �������������ֻ�й̶��ļ���������  */
	if(GPIO_InitStruct->GPIO_HDrv == ENABLE)
	{
		if(PORTx == PORTH)
		{
			switch(GPIO_InitStruct->GPIO_Pin)
			{
				case GPIO_Pin_H1:PORT->HDRVE |= 1 << 7;break;
				case GPIO_Pin_H0:PORT->HDRVE |= 1 << 6;break;
				default: break;
			}
		}
		if(PORTx == PORTE)
		{
			switch(GPIO_InitStruct->GPIO_Pin)
			{
				case GPIO_Pin_E1:PORT->HDRVE |= 1 << 5;break;
				case GPIO_Pin_E0:PORT->HDRVE |= 1 << 4;break;
				default: break;
			}
		}
		if(PORTx == PORTD)
		{
			switch(GPIO_InitStruct->GPIO_Pin)
			{
				case GPIO_Pin_D1:PORT->HDRVE |= 1 << 3;break;
				case GPIO_Pin_D0:PORT->HDRVE |= 1 << 2;break;
				default: break;
			}
		}
		if(PORTx == PORTB)
		{
			switch(GPIO_InitStruct->GPIO_Pin)
			{
				case GPIO_Pin_B5:PORT->HDRVE |= 1 << 1;break;
				case GPIO_Pin_B4:PORT->HDRVE |= 1 << 0;break;
				default: break;
			}
		}
	}
}

/*
*********************************************************************************************************
*                                  drv_gpio_ReadPin        
*
* Description: ��ȡһ�����ŵĵ�ƽֵ
*             
* Arguments  : 1> PORTx: GPIO�˿�ָ��, PORTA~PORTI
*              2> GPIO_Pin: ���ű��
*
* Reutrn     : ���ŵ�ƽ
*
* Note(s)    : None.
*********************************************************************************************************
*/
uint8_t drv_gpio_ReadPin(GPIO_Type *PORTx, uint8_t GPIO_Pin)
{
	uint8_t pin;
	
	/*  ��ȡ���ŵ�ƽ  */
	pin = PORTx->PDIR & GPIO_PDIR_PDI(1 << GPIO_Pin);
	
	return pin;
}

/*
*********************************************************************************************************
*                                drv_gpio_WritePin          
*
* Description: д���ŵ�ƽ
*             
* Arguments  : 1> PORTx: GPIO�˿�ָ��, PORTA~PORTI
*              2> GPIO_Pin: ���ű��
*              3> NewState: ö�ٱ���,SET ���� RESET
*
* Reutrn     : Nono.
*
* Note(s)    : None.
*********************************************************************************************************
*/
void drv_gpio_WritePin(GPIO_Type *PORTx, uint8_t GPIO_Pin, GPIO_PinState PinState)
{
	if(PinState == GPIO_PIN_RESET)  /*  ������õ͵�ƽ  */
	{
		PORTx->PCOR |= 1 << GPIO_Pin;
	}
	else
	{
		PORTx->PSOR |= 1 << GPIO_Pin;
	}
}

/*
*********************************************************************************************************
*                                  drv_gpio_TogglePin        
*
* Description: ��ת���ŵ�ƽ
*             
* Arguments  : 1> PORTx: GPIO�˿�ָ��, PORTA~PORTI
*              2> GPIO_Pin: ���ű��
*
* Reutrn     : None.
*
* Note(s)    : None.
*********************************************************************************************************
*/
void drv_gpio_TogglePin(GPIO_Type *PORTx, uint8_t GPIO_Pin)
{
	PORTx->PTOR |= 1 << GPIO_Pin;		/*  PORTx->PTOR�Ĵ���,����Ĵ���  */
}


/*
*********************************************************************************************************
*                                    drv_gpio_PinAFConfig      
*
* Description: �������ŵĸ��ù���
*             
* Arguments  : 1> GPIO_PinSource: GPIO������Դ,��drv_gpio.h��������������Դ�Ķ���
*              2> GPIO_AF       : Ҫ���õĹ���,��drv_gpio.h�������и��ù��ܵĶ���
*
* Reutrn     : None.
*
* Note(s)    : None.
*********************************************************************************************************
*/
void drv_gpio_PinAFConfig(uint8_t GPIO_PinSource, uint16_t GPIO_AF)
{
	uint8_t reg = 0;
	uint8_t bit = 0;
	uint8_t clrbit = 0;
	reg = (uint8_t)(GPIO_AF >> 8);		/*  ��ȡ�Ĵ�����  */
	bit = (uint8_t)(GPIO_AF);					/*  ��ȡ��Ҫ���õļĴ���λ��  */
	
	switch(GPIO_AF)				/*  ��Ϊ��ͬ�ĸ��ù���ռ�õ�λ����һ��  */
	{
		case GPIO_AF_FTM0_CH0:
		case GPIO_AF_FTM0_CH1:
		case GPIO_AF_FTM1_CH0:
		case GPIO_AF_FTM1_CH1:
		case GPIO_AF_PWT_IN0:
		case GPIO_AF_PWT_IN1:
		case GPIO_AF_FTM2_CH4:
		case GPIO_AF_FTM2_CH5:
		case GPIO_AF_RTCO:clrbit = 1;break;		/*  ֻռ��һλ  */
		case GPIO_AF_FTM2_CH0:
		case GPIO_AF_FTM2_CH1:
		case GPIO_AF_FTM2_CH2:
		case GPIO_AF_FTM2_CH3: clrbit = 3;break;	/*  ռ����λ  */
		case GPIO_AF_IRQ: clrbit = 7; break;			/*  ռ����λ  */
	}
	if(reg == 0)			/*  ��PINSEL0�Ĵ�������  */
	{
		SIM->PINSEL &= ~(clrbit << bit);		/*  ���������  */
		SIM->PINSEL |= GPIO_PinSource << bit;
	}
	else							/*  ��PINSEL1�Ĵ�������  */
	{
		SIM->PINSEL1 &= ~(clrbit << bit);		/*  ���������  */
		SIM->PINSEL1 |= GPIO_PinSource << bit;
	}
}

/********************************************  END OF FILE  *******************************************/

