#include "touch.h" 
#include "lcd.h"
#include "Framework.h"
#include "stdlib.h"
#include "math.h"
//////////////////////////////////////////////////////////////////////////////////	 

//////////////////////////////////////////////////////////////////////////////////

_m_tp_dev tp_dev=
{
	TP_Init,
	GT9147_Scan,
	0,
	0, 
	0,
	0,
	0,
	0,	  	 		
	0,
	0,	  	 		
};					
//Ĭ��Ϊtouch_type=0������.
u8 CMD_RDX=0XD0;
u8 CMD_RDY=0X90;

//��������ʼ��  		    
//����ֵ:0,û�н���У׼
//       1,���й�У׼
u8 TP_Init(void)
{	
    //0x5510
		if(GT9147_Init()==0)	//��GT9147
		{
			tp_dev.scan=GT9147_Scan;	//ɨ�躯��ָ��GT9147������ɨ��
		}
		tp_dev.touchtype|=0X80;	//������ 
		tp_dev.touchtype|=lcddev.dir&0X01;//������������ 
		return 0;									 
}


