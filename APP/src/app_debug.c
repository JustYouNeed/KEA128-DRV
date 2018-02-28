# include "app_debug.h"
# include "bsp_led.h"


ANO_InfoStruct ano_info;

extern Uart_Str uart_info;

uint8_t pidchecksum = 0;
	
void app_debug_Config(void)
{
	ano_info.aacx = 0;
	ano_info.aacy = 0;
	ano_info.aacz = 0;
	ano_info.gryox = 0;
	ano_info.gryoy = 0;
	ano_info.gyroz = 0;
	ano_info.Kd[0] = 0;
	ano_info.Ki[0] = 0;
	ano_info.Kp[0] = 0;
	
	ano_info.pit_p = DEFAULT_PIT_KP;
	ano_info.pit_i = DEFAULT_PIT_KI;
	ano_info.pit_d = DEFAULT_PIT_KD;
	
	ano_info.rol_p = DEFAULT_ROL_KP;
	ano_info.rol_i = DEFAULT_ROL_KI;
	ano_info.rol_d = DEFAULT_ROL_KD;
	
	ano_info.yaw_p = DEFAULT_YAW_KP;
	ano_info.yaw_i = DEFAULT_YAW_KI;
	ano_info.yaw_d = DEFAULT_YAW_KD;
	
	ano_info.REC_FLAG = 0;
}


void app_debug_SendChar(uint8_t byte)
{
	drv_uart_SendData(UART0, byte);
}

void ANO_Response(void)
{
	uint8_t SendBuff[8];
	uint8_t i;
	
	SendBuff[0] = 0XAA;//֡��ʼ
	SendBuff[1] = 0XAA;
	SendBuff[2] = 0XF0;
	SendBuff[3] = 0x03;
	SendBuff[4] = 0XBA;
	SendBuff[5] = (ano_info.RecBuff[ano_info.RecBuff[3] + 0x04]>>8)&0xff;
	SendBuff[6] = ano_info.RecBuff[ano_info.RecBuff[3] + 0x04]&0xff;
	
	for(i = 0;i<7;i++) SendBuff[7] += SendBuff[i];
	for(i = 0;i<8;i++)
		app_debug_SendChar(SendBuff[i]);
}

void ANO_PIDRes(uint8_t funcode)
{
	uint8_t SendBuff[8];
	uint8_t i;
	
	SendBuff[0] = 0XAA;//֡��ʼ
	SendBuff[1] = 0XAA;
	SendBuff[2] = 0XEF;
	SendBuff[3] = 7;
	SendBuff[4] = funcode;
	SendBuff[5] = ano_info.RecBuff[ano_info.RecBuff[3] + 0X04]&0xff;
//	SendBuff[6] = ano_info.RecBuff[ano_info.RecBuff[3] + 0x04]&0xff;
	
	for(i = 0;i<7;i++) SendBuff[6] += SendBuff[i];
	bsp_uart_SendDataToBuff(COM0, SendBuff, 7);
}

void ANO_DataProcess()
{
		switch(ano_info.REC_FLAG)
	{
		case ADJ_COMMAND:break;
		case REQUEST_PID: //PID������������
		{
			app_debug_PIDUpload();  //�ϴ���һ��PID����
		}break;
		case ADJ_SENSER:break;  //��������������
		case ADJ_PID1:app_debug_PIDDownload();	bsp_led_Toggle(1);ANO_PIDRes(ADJ_PID1); break; //���յ�һ��PID��������Ӧ
		case ADJ_PID2:ANO_PIDRes(ADJ_PID2); break; //
		case ADJ_PID3:ANO_PIDRes(ADJ_PID3); break; //
		case ADJ_PID4:ANO_PIDRes(ADJ_PID4); break; //
		case ADJ_PID5:ANO_PIDRes(ADJ_PID5); break; //
		case ADJ_PID6:ANO_PIDRes(ADJ_PID6); break; //
		case ADJ_OFFSET:break;                                //������ƫ����
		case BOOTMODE:break;                                  //����IAP����ģʽ����
	}
	ano_info.REC_FLAG = 0;     //���������ݺ���ձ�־��λ
}

void ANO_USART_Handler(void)
{
	uint8_t RecvData;  //�ֽڽ����ݴ�
	uint8_t i = 0;  //
	uint8_t checkSum = 0; //
	static uint8_t uCnt = 0;
	
	(void)UART0_S1;
	
	if(UART0->S1 & UART_S1_RDRF_MASK)  /*  �������ݼĴ�����  */
	{
		RecvData = UART0->D;		/*  ��ȡ���ݲ�������ջ�����  */
		
		switch(uCnt)
		{
			case 0X00:
			{
					if(0XAA == RecvData)	
					{
						ano_info.RecBuff[uCnt++] = RecvData;  //֡��ʼ�ж�
					}
					else uCnt = 0X00;
			}break;
			case 0X01:
			{
				if(0XAF == RecvData)	
				{
					ano_info.RecBuff[uCnt++] = RecvData;//֡��ʼ�ж�
					
				}
				else uCnt = 0X00;
			}break;
			case 0X02:ano_info.RecBuff[uCnt++] = RecvData; break;  //������
			case 0X03:ano_info.RecBuff[uCnt++] = RecvData; break; //���ݳ��ȣ���ȥ�������Լ���ʼ֡������
			default:if(uCnt < (ano_info.RecBuff[3] + 0X05)) ano_info.RecBuff[uCnt++] = RecvData;break;//��������
			//��0x05����Ϊ ano_info[len+4]�з��ż���ͣ�������������ʱ��uCnt = len+0x05,����������
		}
		
		if(uCnt == (ano_info.RecBuff[3] + 0X05))  //�Ѿ���������������֡
		{
			uCnt = 0;
			for(i = 0;i < ano_info.RecBuff[3] + 0x04; i++) //�������Ͳ��������һ���ļ���ͣ�
			{
				checkSum += ano_info.RecBuff[i]; //��������
			}
			
			if((checkSum&0xff) != ano_info.RecBuff[ano_info.RecBuff[3] + 0X04]) 
			{
				ano_info.REC_FLAG = 0; //���մ���
			}
			else 
			{
				if(ano_info.REC_FLAG == ADJ_PID1) pidchecksum = checkSum;
				ano_info.REC_FLAG = ano_info.RecBuff[2];		//���ݼ������󣬱��湦����
		#if ANO_DATA_PRECESS_ON==1  //ѡ���Ƿ������һ֡���ݺ��Զ�����
				ANO_DataProcess();
		#endif
			}
		}
	}
	
	bsp_uart_IRQHandler(&uart_info);
}



uint8_t ANO_DataUpload(uint8_t *buff, uint8_t funCode, uint8_t len)
{
	uint8_t SendBuff[32];
	uint8_t i;
	if(len>27)return 0;//���ݳ��ȳ�������
	if(funCode>0xff) return 1;//���������
		
	SendBuff[0] = 0XAA; //֡��ʼ
	SendBuff[1] = 0XAA; //֡��ʼ
	SendBuff[2] = funCode;  //������
	SendBuff[3] = len;   //���ݳ��ȣ���ȥ��ʼ��͹������Լ�����
	
	//��Ҫ���͵����ݸ��Ƶ�������
	for(i = 0; i < len; i++) SendBuff[i + 4] = buff[i];
	//����У���
	for(i = 0; i< len + 4; i++) SendBuff[len + 4] += SendBuff[i];
	//ѭ����������
//	for(i = 0; i< len + 5; i++) 
//		app_debug_SendChar(SendBuff[i]);
	
	bsp_uart_SendDataToBuff(COM0, SendBuff, len + 5);
	
	return 2;
}

uint8_t ANO_DataSend(uint8_t *buff,uint8_t funCode, uint8_t len)
{
	uint8_t SendBuff[32];
	uint8_t i;
	
	for(i = 0; i < 32; i++) SendBuff[i] = 0X00;
	if(len>27)return 0;//���ݳ��ȳ�������
	if(funCode>0xff) return 1;//���������
		
	SendBuff[0] = 0XAA; //֡��ʼ
	SendBuff[1] = 0XAF; //֡��ʼ
	SendBuff[2] = funCode;  //������
	SendBuff[3] = len;   //���ݳ��ȣ���ȥ��ʼ��͹������Լ�����
	
	//��Ҫ���͵����ݸ��Ƶ�������
	for(i = 0; i < len; i++) SendBuff[i + 4] = buff[i];
	//����У���
	for(i = 0; i< len + 4; i++) SendBuff[len + 4] += SendBuff[i];
	//ѭ����������
	for(i = 0; i< len + 5; i++) 
		app_debug_SendChar(SendBuff[i]);
	return 2;
}


void app_debug_PIDUpload(void)
{
	uint8_t Buff[18];
	uint8_t i;
	short temp;
	for(i = 0;i< 18; i++) Buff[i] = 0x00;
	
	temp = (short)(ano_info.rol_p*ANO_PID_TRAN_FAC_P);
	Buff[0] = BYTE2(temp);
	Buff[1] = BYTE1(temp);
	
	temp = (short)(ano_info.rol_i*ANO_PID_TRAN_FAC_I);
	Buff[2] = BYTE2(temp);
	Buff[3] = BYTE1(temp);
	
	temp = (short)(ano_info.rol_d*ANO_PID_TRAN_FAC_D);
	Buff[4] = BYTE2(temp);
	Buff[5] = BYTE1(temp);
	
	temp = (short)(ano_info.pit_p*ANO_PID_TRAN_FAC_P);
	Buff[6] = BYTE2(temp);
	Buff[7] = BYTE1(temp);
	
	temp = (short)(ano_info.pit_i*ANO_PID_TRAN_FAC_I);
	Buff[8] = BYTE2(temp);
	Buff[9] = BYTE1(temp);
	
	temp = (short)(ano_info.pit_d*ANO_PID_TRAN_FAC_D);
	Buff[10] = BYTE2(temp);
	Buff[11] = BYTE1(temp);
	
	temp = (short)(ano_info.yaw_p*ANO_PID_TRAN_FAC_P);
	Buff[12] = BYTE2(temp);
	Buff[13] = BYTE1(temp);
	
	temp = (short)(ano_info.yaw_i*ANO_PID_TRAN_FAC_I);
	Buff[14] = BYTE2(temp);
	Buff[15] = BYTE1(temp);
	
	temp = (short)(ano_info.yaw_d*ANO_PID_TRAN_FAC_D);
	Buff[16] = BYTE2(temp);
	Buff[17] = BYTE1(temp);
//	
	ANO_DataUpload(Buff,0x10,18);
}

void app_debug_PIDDownload(void)
{
	//ȡǰ������8λ�����ݺϲ���һ��16λ�����ݣ���ǿ��ת����һ��float�͵�����
	//ת����ɺ������Ӧ�Ĵ�������
	ano_info.rol_p = (float)((int16_t)((ano_info.RecBuff[4]<<8)|(ano_info.RecBuff[5])))/ANO_PID_TRAN_FAC_P;
	ano_info.rol_i = (float)((int16_t)(ano_info.RecBuff[6]<<8)|(ano_info.RecBuff[7]))/ANO_PID_TRAN_FAC_I;
	ano_info.rol_d = (float)((int16_t)(ano_info.RecBuff[8]<<8)|(ano_info.RecBuff[9]))/ANO_PID_TRAN_FAC_D;
	
	ano_info.pit_p = (float)((int16_t)((ano_info.RecBuff[10]<<8)|(ano_info.RecBuff[11])))/ANO_PID_TRAN_FAC_P;
	ano_info.pit_i = (float)((int16_t)(ano_info.RecBuff[12]<<8)|(ano_info.RecBuff[13]))/ANO_PID_TRAN_FAC_I;
	ano_info.pit_d = (float)((int16_t)(ano_info.RecBuff[14]<<8)|(ano_info.RecBuff[15]))/ANO_PID_TRAN_FAC_D;

	ano_info.yaw_p = (float)((int16_t)((ano_info.RecBuff[16]<<8)|(ano_info.RecBuff[17])))/ANO_PID_TRAN_FAC_P;
	ano_info.yaw_i = (float)((int16_t)(ano_info.RecBuff[18]<<8)|(ano_info.RecBuff[19]))/ANO_PID_TRAN_FAC_I;
	ano_info.yaw_d = (float)((int16_t)(ano_info.RecBuff[20]<<8)|(ano_info.RecBuff[21]))/ANO_PID_TRAN_FAC_D;
}

void app_debug_SensorDataReport(void)
{
	uint8_t Buff[18];
	uint8_t i;
	for(i = 0;i< 18; i++) Buff[i] = 0x00;
	
	Buff[0] = (100>>8)&0xff;
	Buff[1] = 100&0xff;
	
	Buff[2] = (90 >> 8) & 0xff;
	Buff[3] = 90 & 0xff;
	
	Buff[4] = (80 >> 8) & 0xff;
	Buff[5] = 80 & 0xff;
	
	Buff[6] = (70 >> 8) & 0xff;
	Buff[7] = 70 & 0xff;
	
	Buff[8] = (60 >> 8) & 0xff;
	Buff[9] = 60 & 0xff;
	
	Buff[10] = (50 >> 8) & 0xff;
	Buff[11] = 50 & 0xff;
	
	Buff[12] = (40 >> 8) & 0xff;
	Buff[13] = 40 & 0xff;
	
	Buff[14] = (30 >> 8) & 0xff;
	Buff[15] = 30 & 0xff;
	
	Buff[16] = (20 >> 8) & 0xff;
	Buff[17] = 20 & 0xff;
	
	ANO_DataUpload(Buff,0x02,18);
}
	

