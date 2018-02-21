/**
  *******************************************************************************************************
  * File Name: bsp_timer.h
  * Author: Vector
  * Version: V1.0.0
  * Date: 2018-2-11
  * Brief: ���ļ��������й������ʱ����һЩ����
  *******************************************************************************************************
  * History
	*		1.Data: 2018-2-11
	* 		Author: Vector
  *			Mod: �����ļ�
  *
  *******************************************************************************************************
  */	
# ifndef __BSP_TIMER_H
# define __BSP_TIMER_H

# include "derivative.h"

# define SOFT_TIMER_COUNT			4

typedef void (*_cbTimerCallBack)(void);		/*  �����ʱ���ص�������������  */

/*  �����ʱ�����ƽṹ��  */
typedef struct	
{
	volatile uint8_t v_ucMode;		/*  ģʽ  */
	volatile uint8_t v_ucFlag;		/*  ��ʱ�����־  */
	volatile uint32_t v_uiCount;	/*  ��ʱ������  */
	volatile uint32_t v_uiPreLoad;	/*  ��װ��ֵ  */
	
	uint8_t ucUsed;					/*  �Ƿ��Ѿ�ʹ��  */
	_cbTimerCallBack _cbTimer;	/*  �ص�����  */
	
}SoftTimer_Str;

/*  �����ʱ��ģʽö�ٱ���  */
typedef enum
{
	TIMER_MODE_ONCE = 0x00,
	TIMER_MODE_AUTO
}TIMER_MODE_ENUM;

void bsp_tim_SoftConfig(void);  /* ��ʼ�������ʱ�� */
int8_t bsp_tim_CreateTimer(uint8_t ucTimerId, uint32_t uiPeriod, _cbTimerCallBack  _cbTimer, TIMER_MODE_ENUM eMode);
int8_t bsp_tim_DeleteTimer(uint8_t ucTimerId);
_cbTimerCallBack bsp_tim_SetTimerCB(uint8_t TimerId, _cbTimerCallBack  _cbTimer);
int8_t bsp_tim_TimerCheck(uint8_t ucTimerId);
int32_t bsp_tim_GetRunTime(void);
int32_t bsp_tim_CheckRunTime(int32_t iLastTime);
_cbTimerCallBack bsp_tim_GetCB(uint8_t ucTimerId);

void bsp_tim_DelayMs(uint16_t ui_nMs);
void bsp_tim_DelayUs(uint16_t ui_nUs);

# endif

/********************************************  END OF FILE  *******************************************/

