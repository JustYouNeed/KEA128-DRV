/**
  *******************************************************************************************************
  * File Name: bsp_led.c
  * Author: Vector
  * Version: V1.0.0
  * Date: 2018-2-25
  * Brief: 本文件声明了有关板级LED灯的变量声明
  *******************************************************************************************************
  * History
  *		1.Author: Vector
	*			Date:	2018-2-25
	*			Mod:	建立文件 
  *
  *******************************************************************************************************
  */	
# ifndef __BSP_LED_H
# define __BSP_LED_H

/*
  *******************************************************************************************************
  *                              INCLUDE FILES
  *******************************************************************************************************
*/
# include "derivative.h"


# define LED_ALL			0
# define LED1					1
# define LED2					2
# define LED3					3

# define LED_ON				GPIO_PIN_RESET
# define LED_OFF			GPIO_PIN_SET

# define LED1_PORT		PORTB
# define LED2_PORT		PORTE
# define LED3_PORT		PORTD
# define LED4_PORT		PORTE

# define LED1_PIN			GPIO_Pin_B1
# define LED2_PIN			GPIO_Pin_E5
# define LED3_PIN			GPIO_Pin_D2
# define LED4_PIN			GPIO_Pin_E0

void bsp_led_Config(void);
void bsp_led_ON(uint8_t LEDx);
void bsp_led_OFF(uint8_t LEDx);
void bsp_led_Toggle(uint8_t LEDx);

# endif

/********************************************  END OF FILE  *******************************************/

