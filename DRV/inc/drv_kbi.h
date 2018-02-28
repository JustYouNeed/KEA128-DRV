/**
  *******************************************************************************************************
  * File Name: drv_kbi.c
  * Author: Vector
  * Version: V1.0.0
  * Date: 2018-2-28
  * Brief: 本文件声明了有关操作KBI外设的底层驱动函数、变量以及宏定义
  *******************************************************************************************************
  * History
  *		1.Author: Vector
	*     Date: 2018-2-28
	*     Mod: 建立文件
  *
  *******************************************************************************************************
  */	
	
# ifndef __DRV_KBI_H
# define __DRV_KBI_H

/*
  *******************************************************************************************************
  *                              INCLUDE FILES
  *******************************************************************************************************
*/
# include "derivative.h"


/*  KBI通道枚举变量类型  */
typedef enum
{
	KBI_Channel_A0 = 0,
	KBI_Channel_A1,
	KBI_Channel_A2,
	KBI_Channel_A3,
	KBI_Channel_A4,
	KBI_Channel_A5,
	KBI_Channel_A6,
	KBI_Channel_A7,
	
	KBI_Channel_B0,
	KBI_Channel_B1,
	KBI_Channel_B2,
	KBI_Channel_B3,
	KBI_Channel_B4,
	KBI_Channel_B5,
	KBI_Channel_B6,
	KBI_Channel_B7,
	
	KBI_Channel_C0,
	KBI_Channel_C1,
	KBI_Channel_C2,
	KBI_Channel_C3,
	KBI_Channel_C4,
	KBI_Channel_C5,
	KBI_Channel_C6,
	KBI_Channel_C7,
	
	KBI_Channel_D0,
	KBI_Channel_D1,
	KBI_Channel_D2,
	KBI_Channel_D3,
	KBI_Channel_D4,
	KBI_Channel_D5,
	KBI_Channel_D6,
	KBI_Channel_D7,
	
	KBI_Channel_E0,
	KBI_Channel_E1,
	KBI_Channel_E2,
	KBI_Channel_E3,
	KBI_Channel_E4,
	KBI_Channel_E5,
	KBI_Channel_E6,
	KBI_Channel_E7,
	
	KBI_Channel_F0,
	KBI_Channel_F1,
	KBI_Channel_F2,
	KBI_Channel_F3,
	KBI_Channel_F4,
	KBI_Channel_F5,
	KBI_Channel_F6,
	KBI_Channel_F7,
	
	KBI_Channel_G0,
	KBI_Channel_G1,
	KBI_Channel_G2,
	KBI_Channel_G3,
	KBI_Channel_G4,
	KBI_Channel_G5,
	KBI_Channel_G6,
	KBI_Channel_G7,
	
	KBI_Channel_H0,
	KBI_Channel_H1,
	KBI_Channel_H2,
	KBI_Channel_H3,
	KBI_Channel_H4,
	KBI_Channel_H5,
	KBI_Channel_H6,
	KBI_Channel_H7,
}KBI_ChannelType;

typedef enum
{
	KBI_TrigFalling = 0,
	KBI_TrigRising,
	KBI_TringFallingLow,
	KBI_TrigRisingHigh,
}KBI_TrigModeType;



void drv_kbi_Init(KBI_ChannelType KBI_Channel, KBI_TrigModeType KBI_TrigMode);

# endif

/********************************************  END OF FILE  *******************************************/

