#ifndef __TOUCH_H__
#define __TOUCH_H__
#include "main.h"
#include "gt9147.h"

#define TP_PRES_DOWN 0x80  //����������	  
#define TP_CATH_PRES 0x40  //�а��������� 
#define CT_MAX_TOUCH  5    //������֧�ֵĵ���,�̶�Ϊ5��

//������������
typedef struct
{
	u8 (*init)(void);			//��ʼ��������������
	u8 (*scan)(u8);				//ɨ�败����.0,��Ļɨ��;1,��������;	 
	u16 x[CT_MAX_TOUCH]; 		//��ǰ����
	u16 y[CT_MAX_TOUCH];		//�����������5������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
								//x[4],y[4]�洢��һ�ΰ���ʱ������. 
	u8  sta;					//�ʵ�״̬ 
								//b7:����1/�ɿ�0; 
	                            //b6:0,û�а�������;1,�а�������. 
								//b5:����
								//b4~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)
/////////////////////������У׼����(����������ҪУ׼)//////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//b0:0,����(�ʺ�����ΪX����,����ΪY�����TP)
//   1,����(�ʺ�����ΪY����,����ΪX�����TP) 
//b1~6:����.
//b7:0,������
//   1,������ 
	u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��

//������оƬ��������	   
#define PEN         HAL_GPIO_ReadPin(T_PEN_GPIO_Port, T_PEN_Pin) //T_PEN
#define DOUT        HAL_GPIO_ReadPin(T_MISO_GPIO_Port,T_MISO_Pin) //T_MISO
#define TDIN(n)     (n?HAL_GPIO_WritePin(T_MOSI_GPIO_Port,T_MOSI_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(T_MOSI_GPIO_Port,T_MOSI_Pin,GPIO_PIN_RESET))//T_MOSI
#define TCLK(n)     (n?HAL_GPIO_WritePin(T_SCLK_GPIO_Port,T_SCLK_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(T_SCLK_GPIO_Port,T_SCLK_Pin,GPIO_PIN_RESET))//T_SCK
#define TCS(n)      (n?HAL_GPIO_WritePin(T_CS_GPIO_Port,T_CS_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(T_CS_GPIO_Port,T_CS_Pin,GPIO_PIN_RESET))//T_CS
   
//����������
u8 TP_Init(void);								//��ʼ��
 
#endif

















