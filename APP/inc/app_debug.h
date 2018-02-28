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
	
/*
	*******************************************************************************************************
	*                              INCLUDE FILES
	*******************************************************************************************************
*/
# include "bsp_uart.h"

//PID�������ϴ�������ʱʹ�õı任����
# define ANO_PID_TRAN_FAC_P 100
# define ANO_PID_TRAN_FAC_I 100
# define ANO_PID_TRAN_FAC_D	10


//Ĭ��PID������ʹ�����ߵ���ʱ���Ա�֤�����ʼ��ʱ��PID����
# define DEFAULT_PIT_KP	0
# define DEFAULT_PIT_KI	0
# define DEFAULT_PIT_KD	0

# define DEFAULT_ROL_KP 28
# define DEFAULT_ROL_KI 34
# define DEFAULT_ROL_KD 45

# define DEFAULT_YAW_KP	0
# define DEFAULT_YAW_KI	0
# define DEFAULT_YAW_KD	0


# define ANO_USART_Handler	UART0_IRQHandler


# define ANO_DATA_PRECESS_ON	1   //	ѡ���Ƿ��Զ���������

																										//              1111 1111 1111 1111
# define BYTE1(num)	(uint8_t)(num & 0XFF)           //ȡ��8λ                      1111
# define BYTE2(num) (uint8_t)((num >> 8) & 0XFF)    //��8λ                   1111
# define BYTE3(num)	(uint8_t)((num >> 16) & 0XFF)		//��16λ             1111
# define BYTE4(num)	(uint8_t)((num >> 24) & 0XFF)   //��32λ        1111 

//�������������룬��λ������
//01 ACCУ׼
//02 GYROУ׼
//03 ACC��GYROУ׼
//04 MAGУ׼
//05 BAROУ׼
# define ADJ_COMMAND	0x01	

//��λ�����󷵻�PID����������
# define REQUEST_PID  0x02

//��λ����������������������
//int16	int16	int16 int16 int16 int16 int16 int16 int16 int16
//THR		YAW		ROL		PIT		AUX1	AUX2	AUX3	AUX4	AUX5	AUX6
# define ADJ_SENSER	0x03

//��λ������PID����1������
//���ݸ�ʽ����
//int16	int16	int16 int16 int16 int16 int16 int16 int16 
//ROL_P	ROL_I	ROL_D	PIT_P	PIT_I	PIT_D	YAW_P	YAW_I	YAW_D
# define ADJ_PID1	0x10

//��λ������PID����2������
//���ݸ�ʽ����
//int16	int16	int16 int16 int16 int16 int16  int16  int16 
//ALT_P	ALT_I	ALT_D	POS_P	POS_I	POS_D	PID1_P PID1_I PID3_D 
# define ADJ_PID2	0x11


//��λ������PID����3������
//���ݸ�ʽ����
//int16		int16		int16	
//PID2_P	PID2_I	PID2_D		
# define ADJ_PID3	0x12

# define ADJ_PID4 0x13
# define ADJ_PID5 0x14
# define ADJ_PID6 0x15

//��λ��������̬ƫ�����
//���ݸ�ʽ����
//int16 						int16
//OFFSET_ROL*1000		OFFSET_PIT*1000
# define ADJ_OFFSET	0x16

//��λ���������bootmode������
# define BOOTMODE	0xf0

//�����Զ��帡�������ݣ�һ��4��
# define REC_FLOAT	0XF1

//����16λ����
# define REC_INT16	0XF2

//����32λ���Σ��з���
# define REC_INT32	0XF3

//�����ַ�������
# define REC_STRING	0XF4

# define REC_COM		0XF5
	
	
typedef struct{

#if ANO_DRIVER_BY_USER==1
	void (*init)(u32 bound);//�û��Լ��Ĵ��ڳ�ʼ������
	void (*ano_sendchar)(uint8_t byte); //�û��ṩ���ֽڷ��ͺ���
#endif
	
	uint8_t RecBuff[32]; //���ջ�����
	uint8_t REC_FLAG;    //���湦����
	float roll,pitch,yaw;		//����ǣ������ǣ�����ǣ�
	float aacx,aacy,aacz;   //������ٶ�
	float gryox,gryoy,gyroz;  //���ٶ�
	float magx,magy,magz; //��������������
	
	float alt_p,alt_i,alt_d;  
	float pos_p,pos_i,pos_d;  //λ��ʽPID����
	
	float rol_p,rol_i,rol_d; // �����PID����
	
	float pit_p,pit_i,pit_d;	//������PID����
	
	float yaw_p,yaw_i,yaw_d;	//�����PID����
	
	
	float Kp[6],Ki[11],Kd[11];	//������λ������12��PID����
	
	float f_Num1, f_Num2, f_Num3, f_Num4; //���յ���4������������
	int16_t i16_Num1, i16_Num2, i16_Num3, i16_Num4; //���յ���4��16λ�з�����������
	int32_t i32_Num1, i32_Num2, i32_Num3, i32_Num4;//���յ���4��32λ�з�����������
	uint8_t String[32];	//���յ����ַ�������
	
	uint8_t Command1, Command2, Command3, Command4, Command5, Command6;	
}ANO_InfoStruct;

extern ANO_InfoStruct ano_info;
	
void app_debug_Config(void);
void app_debug_PIDUpload(void);
void app_debug_PIDDownload(void);
void app_debug_SensorDataReport(void);
	
/********************************************  END OF FILE  *******************************************/
	

