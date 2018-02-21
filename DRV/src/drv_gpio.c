/**
  *******************************************************************************************************
  * File Name: drv_pit.c
  * Author: Vector
  * Version: V1.0.0
  * Date: 2018-2-1
  * Brief: KEA128芯片GPIO底层驱动函数
  *******************************************************************************************************
  * History
  *		1.Data: 2018-2-1
  *     Author: Vector
  *     Mod: 建立文件,添加基本函数
	*		
	*		2.Data: 2018-2-9
	*			Author:	Vector
	*			Mod: 添加新函数drv_gpio_PinAFConfig,用于设置引脚的复用功能
  *
  *******************************************************************************************************
  */
	
# include "drv_gpio.h"

/*
*********************************************************************************************************
*                                       drv_gpio_Init   
*
* Description: 初始化一个GPIO引脚
*             
* Arguments  : 1> PORTx: GPIO端口指针, PORTA~PORTI
*              2> GPIO_InitStruct: GPIO引脚配置结构体指针
*
* Reutrn     : None.
*
* Note(s)    : 一次只能配置一个引脚
*********************************************************************************************************
*/
void drv_gpio_Init(GPIO_Type *PORTx, GPIO_InitTypeDef *GPIO_InitStruct)
{
	PORTx->PIDR |= ((uint32_t)1 << GPIO_InitStruct->GPIO_Pin);	/*  先禁止输入  */
	
	/*  配置端口数据方向寄存器,配置为相应的输入/输出模式  */
	PORTx->PDDR |= (GPIO_InitStruct->GPIO_Mode << GPIO_InitStruct->GPIO_Pin);
		
	if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN)		/*  如果设置为输入则开启输入功能  */
		PORTx->PIDR &= ~((uint32_t)1 << GPIO_InitStruct->GPIO_Pin);
	
	/*  如果开启了上拉  */
	if(GPIO_InitStruct->GPIO_PuPd == GPIO_PuPd_UP)
	{
		/*  GPIOA,GPIOB,及其他配置的寄存器不同  */
		if(GPIOA == PORTx) PORT->PUE0 |= 1 << GPIO_InitStruct->GPIO_Pin;
		else if(GPIOB == PORTx) PORT->PUE1 |= 1 << GPIO_InitStruct->GPIO_Pin;
		else	PORT->PUE2 |= 1 << GPIO_InitStruct->GPIO_Pin;
	}
	
	/*  大电流驱动能力只有固定的几个引脚有  */
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
* Description: 读取一个引脚的电平值
*             
* Arguments  : 1> PORTx: GPIO端口指针, PORTA~PORTI
*              2> GPIO_Pin: 引脚编号
*
* Reutrn     : 引脚电平
*
* Note(s)    : None.
*********************************************************************************************************
*/
uint8_t drv_gpio_ReadPin(GPIO_Type *PORTx, uint8_t GPIO_Pin)
{
	uint8_t pin;
	
	/*  读取引脚电平  */
	pin = PORTx->PDIR & GPIO_PDIR_PDI(1 << GPIO_Pin);
	
	return pin;
}

/*
*********************************************************************************************************
*                                drv_gpio_WritePin          
*
* Description: 写引脚电平
*             
* Arguments  : 1> PORTx: GPIO端口指针, PORTA~PORTI
*              2> GPIO_Pin: 引脚编号
*              3> NewState: 枚举变量,SET 或者 RESET
*
* Reutrn     : Nono.
*
* Note(s)    : None.
*********************************************************************************************************
*/
void drv_gpio_WritePin(GPIO_Type *PORTx, uint8_t GPIO_Pin, GPIO_PinState PinState)
{
	if(PinState == GPIO_PIN_RESET)  /*  如果设置低电平  */
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
* Description: 翻转引脚电平
*             
* Arguments  : 1> PORTx: GPIO端口指针, PORTA~PORTI
*              2> GPIO_Pin: 引脚编号
*
* Reutrn     : None.
*
* Note(s)    : None.
*********************************************************************************************************
*/
void drv_gpio_TogglePin(GPIO_Type *PORTx, uint8_t GPIO_Pin)
{
	PORTx->PTOR |= 1 << GPIO_Pin;		/*  PORTx->PTOR寄存器,跳变寄存器  */
}


/*
*********************************************************************************************************
*                                    drv_gpio_PinAFConfig      
*
* Description: 设置引脚的复用功能
*             
* Arguments  : 1> GPIO_PinSource: GPIO引脚资源,在drv_gpio.h中有所有引脚资源的定义
*              2> GPIO_AF       : 要复用的功能,在drv_gpio.h中有所有复用功能的定义
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
	reg = (uint8_t)(GPIO_AF >> 8);		/*  获取寄存器号  */
	bit = (uint8_t)(GPIO_AF);					/*  获取需要设置的寄存器位置  */
	
	switch(GPIO_AF)				/*  因为不同的复用功能占用的位数不一样  */
	{
		case GPIO_AF_FTM0_CH0:
		case GPIO_AF_FTM0_CH1:
		case GPIO_AF_FTM1_CH0:
		case GPIO_AF_FTM1_CH1:
		case GPIO_AF_PWT_IN0:
		case GPIO_AF_PWT_IN1:
		case GPIO_AF_FTM2_CH4:
		case GPIO_AF_FTM2_CH5:
		case GPIO_AF_RTCO:clrbit = 1;break;		/*  只占用一位  */
		case GPIO_AF_FTM2_CH0:
		case GPIO_AF_FTM2_CH1:
		case GPIO_AF_FTM2_CH2:
		case GPIO_AF_FTM2_CH3: clrbit = 3;break;	/*  占用两位  */
		case GPIO_AF_IRQ: clrbit = 7; break;			/*  占用三位  */
	}
	if(reg == 0)			/*  在PINSEL0寄存器里面  */
	{
		SIM->PINSEL &= ~(clrbit << bit);		/*  先清除设置  */
		SIM->PINSEL |= GPIO_PinSource << bit;
	}
	else							/*  在PINSEL1寄存器里面  */
	{
		SIM->PINSEL1 &= ~(clrbit << bit);		/*  先清除设置  */
		SIM->PINSEL1 |= GPIO_PinSource << bit;
	}
}

/********************************************  END OF FILE  *******************************************/

