/************************************************************************
*|----------------------------ADS1256驱动库----------------------------|*
*|-------------------------------@大四十七高材生-----------------------|*
*|------------------------------2021.4.25------------------------------|*
*|对ADS1256芯片的寄存器读写、数据读取等操作----------------------------|*
*|=====================================================================|*
*|移植指南：														   |*
*|	一、适用条件：													   |*
*|		ADS1256主频为7.68MHz。										   |*
*|	二、原理：														   |*
*|		本驱动库使用一个硬件SPI来驱动ADS1256芯片，完全使用软件方法来   |*
*|		操作芯片。													   |*
*|	三、MCU配置	：													   |*
*|		1.GPIO（引脚连接）：										   |*
*|			ADS1256		MCU											   |*
*|			  														   |*
*|			 SCLK-------SCLK										   |*
*|			 DIN--------MOSI										   |*
*|			 DOUT-------MISO										   |*
*|			 /CS--------GND											   |*
*|			/RESET------VCC											   |*
*|			/SYNC-------VCC											   |*
*|			其他--------任意										   |*
*|		2.SPI														   |*
*|			Ⅰ.主模式，具有收发功能									   |*
*|			Ⅱ.时钟频率在768kHz到1.92MHz之间							   |*
*|			Ⅲ.空闲时低电平，第二时钟边沿采样，MSB首先发送              |*
*|            (CPOL=0,CPHA=1)                                          |*
*|	四、调试信息：													   |*
*|			已在STM32F407ZET6上使用硬件SPI调试通过					   |*
*|  五、参考SPI初始化过程：                                            |*
*|      以下代码初始化SPI2作为ADS1256的SPI收发器                       |*
*|                                                                     |*
*|	    RCC->APB1ENR|=1<<14;	//SPI2时钟使能                         |*
*|	                                                                   |*   
*|	    //寄存器配置                                                   |*
*|	    u16 save=0;                                                    |*
*|	    save|=1<<9;	//软件从器件管理                                   |*
*|	    save|=1<<8;	//SSI=1                                            |*
*|	    save|=1<<2;	//主模式                                           |*
*|	    save|=1;	//下降沿采样                                       |*
*|	    save|=5<<3;	//波特率fPCLK/64                                   |*
*|	    save|=1<<6;	//SPI使能                                          |*
*|	    SPI2->CR1=save;	//写入SPI寄存器                                |*
*|  六、更新：                                                              |*
*|      1.【21.6.18】：补全了初始化函数，重新在F407上验证了代码的         |*
*|         正确性。                                                     |*
*************************************************************************/
#ifndef _ADS1256_H_
#define _ADS1256_H_
#include "Framework.h"


/*=======================================================================================*/

/*
*ADS1256输入缓冲使能/失能
*/
typedef enum
{
    BUFFER_ENABLE=1,
    BUFFER_DISABLE=0
} ads1256_buffer_status_type;

/*
*ADS1256通道类型，ADS1256最多有8个通道，COM也就是GND
*COM端实际上是不存在的，它用来表示单极性输入时的GND
*/
typedef enum
{
	ADS1256_CH0=0,	//通道0
	ADS1256_CH1=1,	//通道1
	ADS1256_CH2=2,	//通道2
	ADS1256_CH3=3,	//通道3
	ADS1256_CH4=4,	//通道4
	ADS1256_CH5=5,	//通道5
	ADS1256_CH6=6,	//通道6
	ADS1256_CH7=7,	//通道7
	ADS1256_COM=8	//共地端
} ads1256_channel_type;
	
/*
*采样率类型
*/
typedef enum
{
	ADS1256_SPS_5=5,		//5SPS
	ADS1256_SPS_10=10,		//10SPS
	ADS1256_SPS_15=15,		//15SPS
	ADS1256_SPS_25=25,		//25SPS
	ADS1256_SPS_30=30,		//30SPS
	ADS1256_SPS_50=50,		//50SPS
	ADS1256_SPS_60=60,		//60SPS
	ADS1256_SPS_100=100,	//100SPS
	ADS1256_SPS_500=500,	//500SPS
	ADS1256_SPS_1000=1000,	//1000SPS
	ADS1256_SPS_2000=2000,	//2000SPS
	ADS1256_SPS_3750=3750,	//3750SPS
	ADS1256_SPS_7500=7500,	//7500SPS
	ADS1256_SPS_15000=15000,//15000SPS
	ADS1256_SPS_30000=30000	//30000SPS
} ads1256_sps_type;

/*
*增益类型，信号被采集前会先经过内部PGA的放大
*该值指定了PGA的实际增益
*/
typedef enum
{
	ADS1256_PGA_1=1,	//1倍，对应采样范围：+-2*Vref
	ADS1256_PGA_2=2,	//2倍，对应采样范围：+-Vref
	ADS1256_PGA_4=4,	//4倍，对应采样范围：+-Vref/2
	ADS1256_PGA_8=8,	//8倍，对应采样范围：+-Vref/4
	ADS1256_PGA_16=16,	//16倍，对应采样范围：+-Vref/8
	ADS1256_PGA_32=32,	//32倍，对应采样范围：+-Vref/16
	ADS1256_PGA_64=64	//64倍，对应采样范围：+-Vref/32
} ads1256_pga_type;

/*
*输入模式
*该值指定各种输入测量模式
*/
typedef enum 
{
	ADS1256_Single,		//单端
	ADS1256_Different	//差分
} ads1256_mode_type;


/*=======================================================================================*/

/*
*ads1256类(size:64)
*包含了控制ADS1256所需的各种信息
*任何对ADS1256的操作都应先创建一个该类的实例
*/
typedef struct ads1256_class
{	
	/*==================================成员变量=======================================*/
    ro          S_H_type                    SPI_Mode;
    ro          ads1256_buffer_status_type	Buffer_Enable;	    //输入缓冲是否开启？
	vro         ads1256_pga_type	  		Gain;			    //当前增益
	vro         ads1256_sps_type 	  		Sample_Rate;	    //当前采样率
	vro         ads1256_mode_type	  		Input_Mode;		    //当前输入测量模式
	vro         ads1256_channel_type 		Positive_Channel;   //同相输入端
	vro         ads1256_channel_type		Negative_Channel;   //反相输入端
	ro          periperal                   SPI;                //SPI外设（SPI_Mode==HARDWARE时有效）
    ro          gpio_type                   SCLK;               //SCLK引脚（SPI_Mode==SOFTWARE时有效）
    ro          gpio_type                   MOSI;               //MOSI引脚（SPI_Mode==SOFTWARE时有效）
    ro          gpio_type                   MISO;               //MISO引脚（SPI_Mode==SOFTWARE时有效）

	
	/*===================================方法=======================================*/
	/********************************************************************
	*功能：设置输入缓冲													*
	*参数：1.device：类的实例											*
	*	   2.flag：操作码，只能是：										*
	*			   BUFFER_ENABLE：使能									*
	*	    	   BUFFER_DISABLE：失能									*
	*说明：无															*
	*********************************************************************/
    void 	(*Set_Input_Buffer_Status) (struct ads1256_class* device, ads1256_buffer_status_type flag);
	
	/********************************************************************
	*功能：设置通道的正输入端											*
	*参数：1.device：类的实例											*
	*	   2.ch：要设置的输入通道										*
	*说明：任何一个输入端等于ADS1256_COM都将使							*
	*	   Input_Mode等于ADS1256_Single，反之等于ADS1256_Different		*
	*																	*
	*********************************************************************/
    void 	(*Set_Positive_Channel)    (struct ads1256_class* device, ads1256_channel_type ch);
	
	/********************************************************************
	*功能：设置通道的负输入端											*
	*参数：1.device：类的实例											*
	*	   2.ch：要设置的输入通道										*
	*说明：任何一个输入端等于ADS1256_COM都将使							*
	*	   Input_Mode等于ADS1256_Single，反之等于ADS1256_Different		*
	*																	*
	*********************************************************************/
    void 	(*Set_Negative_Channel)    (struct ads1256_class* device, ads1256_channel_type ch);
	
	/********************************************************************
	*功能：设置增益值													*
	*参数：1.device：类的实例											*
	*	   2.gain：增益值												*
	*说明：无															*
	*********************************************************************/
    void 	(*Set_PGA_Gain)            (struct ads1256_class* device, ads1256_pga_type gain);
	
	/********************************************************************
	*功能：设置采样率													*
	*参数：1.device：类的实例											*
	*	   2.sample_rate：采样率										*
	*说明：无															*
	*********************************************************************/
    void 	(*Set_Sample_Rate)         (struct ads1256_class* device, ads1256_sps_type samp_rate);
	
	/********************************************************************
	*功能：ADS1256进行一次自校准										*
	*参数：1.device：类的实例											*
	*说明：自校准包括一次自偏移校准和自增益校准							*
	*********************************************************************/
	void 	(*Self_Calibration)		   (struct ads1256_class* device);
	
	/********************************************************************
	*功能：返回DRDY的值													*
	*参数：1.device：类的实例											*
	*说明：DRDY为0代表可以进行读数据操作。此外每次改变某些配置都要等待	*
	*	   DRDY回到0。但是本库中所有的方法都已经确保改变参数后DRDY		*
	*	   等于0，所以无需再调用此方法									*
	*********************************************************************/
	uint8_t (*Get_DataReady_Bit)	   (struct ads1256_class* device);
	
	/********************************************************************
	*功能：获取ADC数据													*
	*参数：1.device：类的实例											*
	*	   2.dat_buf：数据缓存区										*
	*	   3.num：样本数												*
	*	   4.dat_fmt：数据格式											*
	*说明：得到的数据将会按照dat_fmt指定的格式存放在dat_buf中			*
	*********************************************************************/
	void 	(*Get_Data)				   (struct ads1256_class* device, uint32_t fs, void* dat_buf, uint32_t num,  data_format_type dat_fmt);
	
	/********************************************************************
	*功能：发送指令														*
	*参数：1.device：类的实例											*
	*	   2.cmd：要发送的指令码										*
	*********************************************************************/
	void	(*Send_Command)			   (struct ads1256_class* device, uint8_t cmd);
	
	/********************************************************************
	*功能：写寄存器														*
	*参数：1.device：类的实例											*
	*	   2.addr：寄存器地址											*
	*	   3.dat：要写入的数据											*
	*说明：不建议直接调用此方法，除非你真的知道自己在干什么				*
	*********************************************************************/
	void 	(*Write_Register)		   (struct ads1256_class* device, uint8_t addr, uint8_t dat);
	
	/********************************************************************
	*功能：读寄存器														*
	*参数：1.device：类的实例											*
	*	   2.addr：寄存器地址											*
	*********************************************************************/
	uint8_t (*Read_Register)		   (struct ads1256_class* device, uint8_t addr);
} ads1256;

/*=======================================================================================*/




/********************************************************************
*功能：ads1256类构造方法											*
*参数：1.dev：类的实例						                        *
*	   2.mode：spi的实现模式（软件/硬件）						    *
*	   3.spi_value：SPI.Value的值                                   *
*      4.spi_reg0：SPI.Register0的值                                * 
*      5.spi_reg1：SPI.Register1的值                                *
*      6.spi_inst：SPI.Instance的值                                 *
*      7.sclk：SCLK引脚                                             *  
*      8.mosi：MOSI引脚                                             *
*      9.miso：MISO引脚                                             *
*说明：SPI不会在此函数内被配置！！！用户应提前自行配置。而配置参数	*
*	   可以参考文档开头的“移植指南”。                               *
*      只有mode=SOFTWARE时才需要设置sclk,mosi,miso的值，此时value,  *
*      spi_reg0,spi_reg1,spi_inst的值无效；当mode=HARDWARE则相反    *
*********************************************************************/
void ADS1256_Prepare(ads1256* dev, S_H_type mode, uint32_t spi_value, void* spi_reg0, void* spi_reg1,
                    inst_type inst, gpio_type sclk, gpio_type mosi, gpio_type miso);
void Soft_SPI_Write(gpio_type sclk, gpio_type mosi, uint8_t dat);
#endif
