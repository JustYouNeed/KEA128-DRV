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
void drv_gpio_WritePin(GPIO_Type *PORTx, uint8_t GPIO_Pin, FunctionalState NewState)
{
	if(NewState == RESET)  /*  如果设置低电平  */
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

/********************************************  END OF FILE  *******************************************/