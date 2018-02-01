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
void drv_gpio_WritePin(GPIO_Type *PORTx, uint8_t GPIO_Pin, FunctionalState NewState)
{
	if(NewState == RESET)  /*  ������õ͵�ƽ  */
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

/********************************************  END OF FILE  *******************************************/