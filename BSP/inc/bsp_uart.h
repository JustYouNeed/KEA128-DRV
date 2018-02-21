/**
  *******************************************************************************************************
  * File Name: bsp_uart.h
  * Author: Vector
  * Version: V1.0.0
  * Date: 2018-2-11
  * Brief: ���ļ��������йش��ڲ����ı����뺯��
  *******************************************************************************************************
  * History
	*		1.Author: Vector
	*			Date:	2018-2-11
  *			Mod: �����ļ�
  *
  *******************************************************************************************************
  */	

# ifndef __BSP_UART_H
# define __BSP_UART_H

# include "derivative.h"


# define UART_BAUD		9600
# define UART_TX_BUFF_SIZE	512
# define UART_RX_BUFF_SIZE	512

/*  ���ڱ��ö�ٱ���  */
typedef enum
{
	COM0 = 0x01,
	COM1 = 0x02,
	COM2 = 0x03,
}COM_PORT_ENUM;


/*  ���ڿ��ƽṹ�嶨��  */
typedef struct
{
	UART_Type *uart;	/*  ����ָ��  */
	uint8_t *pTxBuff;	/*  �������ݻ�����  */
	uint8_t *pRxBuff;	/*  �������ݻ�����  */
	uint16_t TxBuffSize;	/*  ���ͻ�������С  */
	uint16_t RxBuffSize;	/*  ���ջ�������С  */
	
	__IO uint16_t TxWrite;	/*  ���ڷ���FIFO��д����  */
	__IO uint16_t TxRead;		/*  ���ڷ���FIFO�Ķ�����  */
	__IO uint16_t TxCount;	/*  ͳ�ƻ���Ҫ���͵�����  */
	
	__IO uint16_t RxWrite;	/*  ���ڽ���FIFO��д����  */
	__IO uint16_t RxRead;		/*  ���ڽ������ݵĶ�����  */
	__IO uint16_t RxCount;	/*  ͳ�ƻ���Ҫ����ȡ��������  */
	
	void (*_cbSendBefor)(void *p_arg);	/*  ��������ǰ�Ļص�ָ��  */
	void (*_cbSendOver)(void *p_arg);		/*  ���ͺ�Ļص�ָ��  */
	void (*_cbRecvData)(uint8_t byte);	/*  ���յ�����ʱ�Ļص�ָ��  */
}Uart_Str;

void bsp_uart_Init(void);
void bsp_uart_Put(Uart_Str *pUart,uint8_t byte);
void bsp_uart_ClearTxBuff(COM_PORT_ENUM Port);
void bsp_uart_ClearRxBuff(COM_PORT_ENUM Port);
void bsp_uart_SendDataToBuff(COM_PORT_ENUM Port, uint8_t *buff, uint16_t length);
uint8_t bsp_uart_GetBbsp_uart_GetCharyte(COM_PORT_ENUM Port, uint8_t *byte);
uint8_t bsp_uart_Printf(const char *format, ...);

void bsp_uart_IRQHandler(Uart_Str *pUart);

# endif


/********************************************  END OF FILE  *******************************************/