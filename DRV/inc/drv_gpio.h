/**
  *******************************************************************************************************
  * File Name: drv_gpio.h
  * Author: Vector
  * Version: V1.0.0
  * Date: 2018-2-1
  * Brief: ���ļ�����GPIO��ص��������������,ͬʱ�����˲���GPIO�ĺ������ṹ�塢ö�ٱ�����
  *******************************************************************************************************
  * History
  *		1.Date: 2018-2-1
  *			Author: Vector
  *			Mod: �����ļ�
  *
  *******************************************************************************************************
  */
# ifndef __DRV_GPIO_H
# define __DRV_GPIO_H

# include "derivative.h"

/*  �������PORT,GPIOA�Ĵ�����PORTA-PORTD,32��IO
		GPIOB��PORTE-PORTH,32��IO��
		GPIOC��PORTI,8��IO
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


/*  ���ų�ʼ���ṹ��  */
typedef struct 
{
	uint8_t GPIO_Pin;		/*  ����  */
	uint8_t GPIO_Mode;	/*  ģʽ  */
	uint8_t GPIO_PuPd;	/*  �������  */
	uint8_t GPIO_HDrv;	/*  �������������ѡ��,��ѡ��ֻ��ĳ������������  */
}GPIO_InitTypeDef;


/*  ����ģʽö�ٱ���  */
typedef enum
{
	GPIO_Mode_IN = 0x00,
	GPIO_Mode_OUT = 0x01,
}GPIOMode_TypeDef;


/*  ������/����ģʽö�ٱ���  */
typedef enum
{ 
  GPIO_PuPd_NOPULL = 0x00,		/*  ����/����  */
  GPIO_PuPd_UP     = 0x01,		/*  �ڲ�����  */
  GPIO_PuPd_DOWN   = 0x02,		/*  �ڲ�����,KEA��֧��  */
}GPIOPuPd_TypeDef;


/*  GPIOA�Ĵ����ܵ�����ö�ٱ���  */
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

/*  GPIOB�Ĵ����ܵ�����ö�ٱ���  */
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

/*  GPIOC�Ĵ����ܵ�����ö�ٱ���  */
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


/*  ���ⲿʹ�õ�GPIO���Ų�������  */
void drv_gpio_Init(GPIO_Type *PORTx, GPIO_InitTypeDef *GPIO_InitStruct);
uint8_t drv_gpio_ReadPin(GPIO_Type *PORTx, uint8_t GPIO_Pin);
void drv_gpio_WritePin(GPIO_Type *PORTx, uint8_t GPIO_Pin, FunctionalState NewState);
void drv_gpio_TogglePin(GPIO_Type *PORTx, uint8_t GPIO_Pin);

# endif

/********************************************  END OF FILE  *******************************************/
