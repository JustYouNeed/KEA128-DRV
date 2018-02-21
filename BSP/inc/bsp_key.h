/**
  *******************************************************************************************************
  * File Name: 
  * Author: 
  * Version: 
  * Date: 
  * Brief: 
  *******************************************************************************************************
  * History
  *
  *
  *******************************************************************************************************
  */	

# ifndef __BSP_KEY_H
# define __BSP_KEY_H


/*
  *******************************************************************************************************
  *                              INCLUDE FILES
  *******************************************************************************************************
*/
# include "derivative.h"

# define KEY_UP_PORT	PORTA
# define KEY_UP_PIN		GPIO_Pin_A0

# define KEY_DOWN_PORT	PORTA
# define KEY_DOWN_PIN	GPIO_Pin_A1

# define KEY_OK_PORT	PORTA
# define KEY_OK_PIN		GPIO_Pin_A2

# define BSP_KEY_COUNT		3
# define KEY_LONG_TIME		220
# define KEY_FILTER_TIME	1
# define KEY_FIFO_SIZE	10
# define KEY_PRESS			1
# define KEY_UNPRESS		0

typedef enum{
	KEY_ID_UP = 0x00,
	KEY_ID_OK,
	KEY_ID_DOWN,
}KEY_ID_ENUM;

typedef enum
{
	KEY_NONE = 0x00,
	
	KEY_UP_PRESS,
	KEY_UP_UP,
	KEY_UP_LONG,
	
	KEY_OK_PRESS,
	KEY_OK_UP,
	KEY_OK_LONG,
	
	KEY_DOWN_PRESS,
	KEY_DOWN_UP,
	KEY_DOWN_LONG
}KEY_STAT_ENUM;

typedef struct 
{
	uint8_t Fifo[KEY_FIFO_SIZE];
	uint8_t Read;
	uint8_t Write;
	
	uint8_t IsConfig;
}Key_Fifo_Str;

/*
	每个按键对应1个全局的结构体变量。
*/
typedef struct
{
	uint8_t (*IsKeyPressFunc)(void);
	
	uint8_t Count;
	uint8_t  State;
	uint8_t RepeatSpeed;
	uint8_t RepeatCount;
	uint16_t LongCount;
	uint16_t LongTime;
}Key_Str;

void bsp_key_Init(void);
void bsp_key_Scan(void);
void bsp_key_PutKeyToFIFO(uint8_t KeyValue);
void bsp_key_ClearFIFO(void);
uint8_t bsp_key_GetKey(void);
uint8_t bsp_key_GetKeyState(KEY_ID_ENUM KeyId);

# endif

