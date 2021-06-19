#include "ADS1256.h"
#include "USART.h"

//////////////////////////////用户配置区//////////////////////////////////

/********************************************************************
*功能：SPI写字节													*
*参数：1.dat：要写的字节											*
*说明：调用此方法后，应有一个字节的数据在MOSI上发出					*
*********************************************************************/
void ADS1256_Hard_SPI_Write(ro periperal* spi, uint8_t dat)
{
    uint8_t save;
	while (((spi->Register0.spi->SR>>1)&1)==0);
	spi->Register0.spi->DR=dat;
	while ((spi->Register0.spi->SR&1)==0);
	save=spi->Register0.spi->DR;
}
	
/********************************************************************
*功能：SPI读字节													*
*返回值：读到的数据													*
*说明：调用此方法后，应从MISO上读取一个字节数据						*
*********************************************************************/
uint8_t ADS1256_Hard_SPI_Read(ro periperal* spi)
{
  	while (((spi->Register0.spi->SR>>1)&1)==0);
	spi->Register0.spi->DR=0;
	while ((spi->Register0.spi->SR&1)==0);	
	
	return spi->Register0.spi->DR;
}
/////////////////////////////////////////////////////////////////////////





////////////////////代码区//////////////////////////
//常用指令定义
#define WAKEUP		0x00	//唤醒
#define RDATA		0x01	//读数据
#define RDATAC		0x03	//连续读数据
#define SDATAC		0x0f	//停止连续读数据
#define RREG		0x10	//读寄存器
#define WREG		0x50	//写寄存器
#define RESET		0xfe	//复位
#define SELFCAL		0xf0	//自校准

//常用寄存器地址定义
#define REG_STATUS	0		//STATUS
#define REG_MUX		1		//MUX
#define REG_ADCON	2		//ADCON
#define REG_DRATE	3		//DRATE

//软件SPI写字节
void ADS1256_Soft_SPI_Write(gpio_type sclk, gpio_type mosi, uint8_t dat)
{
    int i;
    GPIO_Write(sclk,0);
    delay_ms(1);                        // 这是什么bug？就tm离谱
    for (i=0;i<8;i++)
    {
        GPIO_Write(mosi,(dat>>(7-i))&0x01);
        GPIO_Write(sclk,1);
        SystemTimer_Delay_Us(1);
        GPIO_Write(sclk,0);
        SystemTimer_Delay_Us(1);
    }
    GPIO_Write(mosi,0);
}

//软件SPI读字节
uint8_t ADS1256_Soft_SPI_Read(gpio_type sclk, gpio_type miso)
{
    uint8_t save=0;
    int i;
    GPIO_Write(sclk,0);
    delay_ms(1);
    for (i=0;i<8;i++)
    {
        save<<=1;
        GPIO_Write(sclk,1);
        SystemTimer_Delay_Us(1);
        GPIO_Write(sclk,0);
        save|=GPIO_Read(miso);
        SystemTimer_Delay_Us(1);
    }
    return save;
}

//软件/硬件SPI写字节
void ADS1256_SPI_Write_Byte(ads1256* device, uint8_t dat){
    if (device->SPI_Mode==HARDWARE)
        ADS1256_Hard_SPI_Write(&device->SPI,dat);
    else
        ADS1256_Soft_SPI_Write(device->SCLK,device->MOSI,dat);
}

//软件/硬件SPI读字节
uint8_t ADS1256_SPI_Read_Byte(ads1256* device)
{
    if (device->SPI_Mode==HARDWARE)
        return ADS1256_Hard_SPI_Read(&device->SPI);
    else
        return ADS1256_Soft_SPI_Read(device->SCLK,device->MISO);
}

//读取一次数据
uint32_t ADS1256_Read_Once(ads1256* device);

uint32_t ADS1256_Read_Once(ads1256* device)
{
	uint32_t save=0;
	
    
	device->Send_Command(device,RDATA);
	SystemTimer_Delay_Us(8);
    

    save+=ADS1256_SPI_Read_Byte(device);
    save<<=8;
    save+=ADS1256_SPI_Read_Byte(device);
    save<<=8;
    save+=ADS1256_SPI_Read_Byte(device);

	return save;
}


//类里各种方法的定义，以Method开头
void 	Method_Self_Calibration		(ads1256* device);
uint8_t Method_Get_DRDY_Bit			(ads1256* device);
void 	Method_Set_Gain				(ads1256* device, ads1256_pga_type gain);
void 	Method_Set_Sample_Rate		(ads1256* device, ads1256_sps_type sample_rate);
void 	Method_Set_Psoitive_Channel	(ads1256* device, ads1256_channel_type ch);
void 	Method_Set_Negative_Channel	(ads1256* device, ads1256_channel_type ch);
void 	Method_Set_Input_Buffer		(ads1256* device, ads1256_buffer_status_type flag);
void 	Method_Get_Data				(struct ads1256_class* device, uint32_t fs, void* dat_buf, uint32_t num,  data_format_type dat_fmt);
void	Method_Send_Command			(ads1256* device, uint8_t cmd);
void 	Method_Write_Register		(ads1256* device, uint8_t addr, uint8_t dat);
uint8_t Method_Read_Register		(ads1256* device, uint8_t addr);

uint8_t Method_Read_Register(ads1256* device, uint8_t addr)
{
	uint8_t save;
	

    ADS1256_SPI_Write_Byte(device,RREG+addr);
    ADS1256_SPI_Write_Byte(device,0);
    delay_ms(6);
    save=ADS1256_SPI_Read_Byte(device);

	return save;
}

void Method_Write_Register(ads1256* device, uint8_t addr, uint8_t dat)
{
	ADS1256_SPI_Write_Byte(device,WREG+addr);
    ADS1256_SPI_Write_Byte(device,0);
    ADS1256_SPI_Write_Byte(device,dat);
	SystemTimer_Delay_Us(5);
}

void Method_Send_Command(ads1256* device, uint8_t cmd)
{
    ADS1256_SPI_Write_Byte(device,cmd);
}

void ADS1256_Prepare(ads1256* dev, S_H_type mode, uint32_t spi_value, void* spi_reg0, void* spi_reg1,
                    inst_type inst, gpio_type sclk, gpio_type mosi, gpio_type miso)
{
    dev->Get_Data               =   Method_Get_Data;
    dev->Get_DataReady_Bit      =   Method_Get_DRDY_Bit;
    dev->Read_Register          =   Method_Read_Register;
    dev->Self_Calibration       =   Method_Self_Calibration;
    dev->Send_Command           =   Method_Send_Command;
    dev->Set_Input_Buffer_Status=   Method_Set_Input_Buffer;
    dev->Set_Negative_Channel   =   Method_Set_Negative_Channel;
    dev->Set_PGA_Gain           =   Method_Set_Gain;
    dev->Set_Positive_Channel   =   Method_Set_Psoitive_Channel;
    dev->Set_Sample_Rate        =   Method_Set_Sample_Rate;
    
    _RO_WRITE(dev->SPI_Mode,S_H_type,mode);
    
    if (mode==HARDWARE)
    {
        //配置dev->spi（外设接口）
        _RO_WRITE(dev->SPI.Value,uint32_t,spi_value);
        _RO_WRITE(dev->SPI.Register0,void*,spi_reg0);
        _RO_WRITE(dev->SPI.Register1,void*,spi_reg1);
        _RO_WRITE(dev->SPI.Instance,void*,inst);
    }
    else if (mode==SOFTWARE)
    {
        //配置软件接口
        _RO_WRITE(dev->SCLK,gpio_type,sclk);
        _RO_WRITE(dev->MOSI,gpio_type,mosi);
        _RO_WRITE(dev->MISO,gpio_type,miso);
    }
    
    //等待上电
	SystemTimer_Delay_Ms(40);
	
	//复位
	Method_Send_Command(dev,RESET);
	while (Method_Get_DRDY_Bit(dev));
	//唤醒
	Method_Send_Command(dev,WAKEUP);
	while (Method_Get_DRDY_Bit(dev));
	//自校准
	Method_Send_Command(dev,SELFCAL);
	while (Method_Get_DRDY_Bit(dev));
	SystemTimer_Delay_Ms(10);

	_RO_WRITE(dev->Buffer_Enable,ads1256_buffer_status_type,BUFFER_DISABLE);
	_RO_WRITE(dev->Input_Mode,ads1256_mode_type,ADS1256_Different);
	_RO_WRITE(dev->Positive_Channel,ads1256_channel_type,ADS1256_CH0);
	_RO_WRITE(dev->Negative_Channel,ads1256_channel_type,ADS1256_CH1);
	_RO_WRITE(dev->Gain,ads1256_pga_type,ADS1256_PGA_1);
	_RO_WRITE(dev->Sample_Rate,ads1256_sps_type,ADS1256_SPS_30000);
}

void Method_Self_Calibration(ads1256* device)
{
	Method_Send_Command(device,SELFCAL);
	while (Method_Get_DRDY_Bit(device));
}

uint8_t Method_Get_DRDY_Bit(ads1256* device)
{
	return Method_Read_Register(device,REG_STATUS)&1;
}

void Method_Set_Gain(ads1256* device, ads1256_pga_type gain)
{
	switch (gain)
	{
		case ADS1256_PGA_1:
			Method_Write_Register(device,REG_ADCON,0x20);
			break;
		case ADS1256_PGA_2:
			Method_Write_Register(device,REG_ADCON,0x21);
			break;
		case ADS1256_PGA_4:
			Method_Write_Register(device,REG_ADCON,0x22);
			break;
		case ADS1256_PGA_8:
			Method_Write_Register(device,REG_ADCON,0x23);
			break;
		case ADS1256_PGA_16:
			Method_Write_Register(device,REG_ADCON,0x24);
			break;
		case ADS1256_PGA_32:
			Method_Write_Register(device,REG_ADCON,0x25);
			break;
		case ADS1256_PGA_64:
			Method_Write_Register(device,REG_ADCON,0x26);
			break;
		default:
			break;
	}
	Method_Self_Calibration(device);
	
	_RO_WRITE(device->Gain,ads1256_pga_type,gain);
}

void Method_Set_Sample_Rate(ads1256* device, ads1256_sps_type sample_rate)
{
	switch (sample_rate)
	{
		case ADS1256_SPS_5:
			Method_Write_Register(device,REG_DRATE,0x13);
			break;
		case ADS1256_SPS_10:
			Method_Write_Register(device,REG_DRATE,0x23);
			break;
		case ADS1256_SPS_15:
			Method_Write_Register(device,REG_DRATE,0x33);
			break;
		case ADS1256_SPS_25:
			Method_Write_Register(device,REG_DRATE,0x43);
			break;
		case ADS1256_SPS_30:
			Method_Write_Register(device,REG_DRATE,0x53);
			break;
		case ADS1256_SPS_50:
			Method_Write_Register(device,REG_DRATE,0x63);
			break;
		case ADS1256_SPS_60:
			Method_Write_Register(device,REG_DRATE,0x72);
			break;
		case ADS1256_SPS_100:
			Method_Write_Register(device,REG_DRATE,0x82);
			break;
		case ADS1256_SPS_500:
			Method_Write_Register(device,REG_DRATE,0x92);
			break;
		case ADS1256_SPS_1000:
			Method_Write_Register(device,REG_DRATE,0xa1);
			break;
		case ADS1256_SPS_2000:
			Method_Write_Register(device,REG_DRATE,0xb0);
			break;
		case ADS1256_SPS_3750:
			Method_Write_Register(device,REG_DRATE,0xc0);
			break;
		case ADS1256_SPS_7500:
			Method_Write_Register(device,REG_DRATE,0xd0);
			break;
		case ADS1256_SPS_15000:
			Method_Write_Register(device,REG_DRATE,0xe0);
			break;
		case ADS1256_SPS_30000:
			Method_Write_Register(device,REG_DRATE,0xf0);
			break;
		default:
			break;
	}
	Method_Self_Calibration(device);
	_RO_WRITE(device->Sample_Rate,ads1256_sps_type,sample_rate);
}

void Method_Set_Input_Buffer(ads1256* device, ads1256_buffer_status_type flag)
{
	Method_Write_Register(device,REG_STATUS,flag<<1);
	Method_Self_Calibration(device);
	_RO_WRITE(device->Buffer_Enable,ads1256_buffer_status_type,flag);
}

void Method_Set_Psoitive_Channel(ads1256* device, ads1256_channel_type ch)
{
	Method_Write_Register(device,REG_MUX,(ch<<4)+device->Negative_Channel);
	while (Method_Get_DRDY_Bit(device));
	
	_RO_WRITE(device->Positive_Channel,ads1256_channel_type,ch);
	if ((device->Positive_Channel==ADS1256_COM)||(device->Negative_Channel==ADS1256_COM))
		_RO_WRITE(device->Input_Mode,ads1256_mode_type,ADS1256_Single);
	else
		_RO_WRITE(device->Input_Mode,ads1256_mode_type,ADS1256_Different);
}

void Method_Set_Negative_Channel(ads1256* device, ads1256_channel_type ch)
{
	Method_Write_Register(device,REG_MUX,(device->Positive_Channel<<4)+ch);
	while (Method_Get_DRDY_Bit(device));
	
	_RO_WRITE(device->Negative_Channel,ads1256_channel_type,ch);
	if ((device->Positive_Channel==ADS1256_COM)||(device->Negative_Channel==ADS1256_COM))
		_RO_WRITE(device->Input_Mode,ads1256_mode_type,ADS1256_Single);
	else
		_RO_WRITE(device->Input_Mode,ads1256_mode_type,ADS1256_Different);
}

void Method_Get_Data(struct ads1256_class* device, uint32_t fs, void* dat_buf, uint32_t num,  data_format_type dat_fmt)
{
	uint32_t i,save1,save2;
	
    //准备倒计时，1000000/fs(us)对应频率也就是fs
    SystemTimer_Timing_Ready(1000000.0f/fs);
    
    //开启系统定时器的倒计时
    //开启以后每次达到设置的计时时间后，SystemTimer_Timing_Check()会返回1
    //当读到SystemTimer_Timing_Check()==1后，该标志位会自动清零
    //如果在到达计时时间后，一直未读取SystemTimer_Timing_Check()，那么该标志位会
    //一直为1，直到用户去读取
    SystemTimer_Timing_Begin();
	for (i=0;i<num;i++)
	{
		while (Method_Get_DRDY_Bit(device));
		((uint32_t*)dat_buf)[i]=ADS1256_Read_Once(device);
        //读取标志位
        //等待计时时间到达
        while (SystemTimer_Timing_Check()==0);
    }
    
	if (dat_fmt==FLOAT_Format)
	{
		save1=device->Gain*8388607;
		for (i=0;i<num;i++)
		{
			save2=((uint32_t*)dat_buf)[i];
			//判断正负性
			if (save2>>23)
				((float*)dat_buf)[i]=(0x1000000-save2)*-5.0f/save1;
			else
				((float*)dat_buf)[i]=save2*5.0f/save1;
		}
	}
}
