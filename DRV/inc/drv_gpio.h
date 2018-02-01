/**
  *******************************************************************************************************
  * File Name: drv_gpio.h
  * Author: Vector
  * Version: V1.0.0
  * Date: 2018-2-1
  * Brief: 该文件对与GPIO相关的外设进行了声明,同时声明了操作GPIO的函数、结构体、枚举变量等
  *******************************************************************************************************
  * History
  *		1.Date: 2018-2-1
  *			Author: Vector
  *			Mod: 建立文件
  *
  *******************************************************************************************************
  */
# ifndef __DRV_GPIO_H
# define __DRV_GPIO_H

# include "derivative.h"

/*  定义相关PORT,GPIOA寄存器管PORTA-PORTD,32个IO
		GPIOB管PORTE-PORTH,32个IO，
		GPIOC管PORTI,8个IO
*/
#define PORTA  GPIOA
#define PORTB  GPIOA
#define PORTC  GPIOA
#define PORTD  GPIOA

#define PORTE	 GPIOB
#define PORTF	 GPIOB
#define PORTG  GPIOB
#define PORTH	 GPIOB
 
#define PORTI	 GPIOC


/*  引脚初始化结构体  */
typedef struct 
{
	uint8_t GPIO_Pin;		/*  引脚  */
	uint8_t GPIO_Mode;	/*  模式  */
	uint8_t GPIO_PuPd;	/*  输出类型  */
	uint8_t GPIO_HDrv;	/*  大电流驱动能力选项,该选项只对某几个引脚有用  */
}GPIO_InitTypeDef;


/*  引脚模式枚举变量  */
typedef enum
{
	GPIO_Mode_IN = 0x00,
	GPIO_Mode_OUT = 0x01,
}GPIOMode_TypeDef;


/*  引脚上/下拉模式枚举变量  */
typedef enum
{ 
  GPIO_PuPd_NOPULL = 0x00,		/*  无上/下拉  */
  GPIO_PuPd_UP     = 0x01,		/*  内部上拉  */
  GPIO_PuPd_DOWN   = 0x02,		/*  内部下拉,KEA不支持  */
}GPIOPuPd_TypeDef;


/*  GPIOA寄存器管的引脚枚举变量  */
typedef enum
{
	GPIO_Pin_A0 = 0x0,
	GPIO_Pin_A1,
	GPIO_Pin_A2,
	GPIO_Pin_A3,
	GPIO_Pin_A4,
	GPIO_Pin_A5,
	GPIO_Pin_A6,
	GPIO_Pin_A7,
	
	GPIO_Pin_B0,
	GPIO_Pin_B1,
	GPIO_Pin_B2,
	GPIO_Pin_B3,
	GPIO_Pin_B4,
	GPIO_Pin_B5,
	GPIO_Pin_B6,
	GPIO_Pin_B7,
	
	GPIO_Pin_C0,
	GPIO_Pin_C1,
	GPIO_Pin_C2,
	GPIO_Pin_C3,
	GPIO_Pin_C4,
	GPIO_Pin_C5,
	GPIO_Pin_C6,
	GPIO_Pin_C7,
	
	GPIO_Pin_D0,
	GPIO_Pin_D1,
	GPIO_Pin_D2,
	GPIO_Pin_D3,
	GPIO_Pin_D4,
	GPIO_Pin_D5,
	GPIO_Pin_D6,
	GPIO_Pin_D7,
}GPIOAPin_TypeDef;

/*  GPIOB寄存器管的引脚枚举变量  */
typedef enum
{
	GPIO_Pin_E0 = 0x0,
	GPIO_Pin_E1,
	GPIO_Pin_E2,
	GPIO_Pin_E3,
	GPIO_Pin_E4,
	GPIO_Pin_E5,
	GPIO_Pin_E6,
	GPIO_Pin_E7,
	
	GPIO_Pin_F0,
	GPIO_Pin_F1,
	GPIO_Pin_F2,
	GPIO_Pin_F3,
	GPIO_Pin_F4,
	GPIO_Pin_F5,
	GPIO_Pin_F6,
	GPIO_Pin_F7,
	
	GPIO_Pin_G0,
	GPIO_Pin_G1,
	GPIO_Pin_G2,
	GPIO_Pin_G3,
	GPIO_Pin_G4,
	GPIO_Pin_G5,
	GPIO_Pin_G6,
	GPIO_Pin_G7,
	
	GPIO_Pin_H0,
	GPIO_Pin_H1,
	GPIO_Pin_H2,
	GPIO_Pin_H3,
	GPIO_Pin_H4,
	GPIO_Pin_H5,
	GPIO_Pin_H6,
	GPIO_Pin_H7,
}GPIOBPin_TypeDef;

/*  GPIOC寄存器管的引脚枚举变量  */
typedef enum
{
	GPIO_Pin_I0 = 0x0,
	GPIO_Pin_I1,
	GPIO_Pin_I2,
	GPIO_Pin_I3,
	GPIO_Pin_I4,
	GPIO_Pin_I5,
	GPIO_Pin_I6,
	GPIO_Pin_I7,
}GPIOCPin_TypeDef;


/*  供外部使用的GPIO引脚操作函数  */
void drv_gpio_Init(GPIO_Type *PORTx, GPIO_InitTypeDef *GPIO_InitStruct);
uint8_t drv_gpio_ReadPin(GPIO_Type *PORTx, uint8_t GPIO_Pin);
void drv_gpio_WritePin(GPIO_Type *PORTx, uint8_t GPIO_Pin, FunctionalState NewState);
void drv_gpio_TogglePin(GPIO_Type *PORTx, uint8_t GPIO_Pin);

# endif

/********************************************  END OF FILE  *******************************************/
