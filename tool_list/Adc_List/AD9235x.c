#include "AD9235x.h"

/*====================================================================================================================*/
/********************************************************************
*���ܣ�SPIд�ֽ�													*
*������1.dat��Ҫд���ֽ�											*
*˵�������ô˷�����Ӧ��һ���ֽڵ�������MOSI�Ϸ���					*
*********************************************************************/
void AD9235x_Hard_SPI_Write_Byte(ro periperal* spi, uint8_t dat)
{
    HAL_SPI_Transmit(spi->Instance, &dat, 1, 1000);
}

/********************************************************************
*���ܣ�SPI���ֽ�													*
*����ֵ������������													*
*˵�������ô˷�����Ӧ��MISO�϶�ȡһ���ֽ�����						*
*********************************************************************/
uint8_t AD9235x_Hard_SPI_Read_Byte(ro periperal* spi)
{
    uint8_t data;
    HAL_SPI_Receive(spi->Instance, &data, 1, 1000);
    return data;
}
/////////////////////////////////////////////////////////////////////////

//���SPIд�ֽ�
void AD9235x_Soft_SPI_Write_Byte(gpio_type sclk, gpio_type mosi, uint8_t dat){
    int i;
    GPIO_Write(sclk,0);
    delay_ms(1);                        // ����ʲôbug����tm����
    for (i=0;i<8;i++){
        GPIO_Write(mosi,(dat>>(7-i))&0x01);
        GPIO_Write(sclk,1);
        SystemTimer_Delay_Us(1);
        GPIO_Write(sclk,0);
        SystemTimer_Delay_Us(1);
    }
    GPIO_Write(mosi,0);
}

//���SPI���ֽ�
uint8_t AD9235x_Soft_SPI_Read_Byte(gpio_type sclk, gpio_type miso){
    uint8_t save=0;
    int i;
    GPIO_Write(sclk,0);
    delay_ms(1);
    for (i=0;i<8;i++){
        save<<=1;
        GPIO_Write(sclk,1);
        SystemTimer_Delay_Us(1);
        GPIO_Write(sclk,0);
        save|=GPIO_Read(miso);
        SystemTimer_Delay_Us(1);
    }
    return save;
}
/**********************************************************************************************************************/
//���/Ӳ��SPIд�ֽ�
void AD9235x_SPI_Write_Byte(ad9235x* device, uint8_t dat)
{
    if (device->SPI_Mode==HARDWARE)
        AD9235x_Hard_SPI_Write_Byte(&device->SPI,dat);
    else
        AD9235x_Soft_SPI_Write_Byte(device->SCLK,device->MOSI,dat);
}

//���/Ӳ��SPI���ֽ�
uint8_t AD9235x_SPI_Read_Byte(ad9235x* device){
    if (device->SPI_Mode==HARDWARE)
        return AD9235x_Hard_SPI_Read_Byte(&device->SPI);
    else
        return AD9235x_Soft_SPI_Read_Byte(device->SCLK,device->MISO);
}
/*====================================================================================================================*/

void Method_AD9235x_Send_Commend(struct ad9235x_class* device, ads9235_commend cmd){
    AD9235x_SPI_Write_Byte(device, cmd);
}

void Method_AD9235x_Get_Data(struct ad9235x_class* device, uint32_t num, void* dat_buf, data_format_type dat_fmt){
    GPIO_Write(device->CS, 0);                      // ����Ƭѡ��
    Method_AD9235x_Send_Commend(device, Get_Data);
    for(int i = 0; i < num; i++){
        uint16_t data = 0;
        data |= AD9235x_SPI_Read_Byte(device);      // �ȶ��߰�λ
        data <<= 8;
        data |= AD9235x_SPI_Read_Byte(device);      // �ٶ��Ͱ�λ
        ((uint32_t*)dat_buf)[i] = data;
    }

    if (dat_fmt==FLOAT_Format){
        return;
    }
}

/**************************�ⲿ����************************************/
void AD9235x_Prepare(ad9235x* dev, S_H_type mode, uint32_t spi_value, void* spi_reg0, void* spi_reg1,
                     inst_type inst, gpio_type sclk, gpio_type mosi, gpio_type miso, gpio_type cs){
    _RO_WRITE(dev->SPI_Mode,S_H_type,mode);

    if(dev->SPI_Mode == HARDWARE){
        _RO_WRITE(dev->SPI.Value, uint32_t, spi_value);
        _RO_WRITE(dev->SPI.Register0, void*, spi_reg0);
        _RO_WRITE(dev->SPI.Register1, void*, spi_reg1);
        _RO_WRITE(dev->SPI.Instance, inst_type, inst);

    }
    else{
        _RO_WRITE(dev->SCLK,gpio_type, sclk);
        _RO_WRITE(dev->MOSI,gpio_type, mosi);
        _RO_WRITE(dev->MISO,gpio_type, miso);
    }

    _RO_WRITE(dev->CS, gpio_type, cs);

    dev->Get_Data       = Method_AD9235x_Get_Data;
    dev->Send_Commend   = Method_AD9235x_Send_Commend;
}