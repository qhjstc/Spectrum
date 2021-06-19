#ifndef BASEPROJECTF4_AD9235X_H
#define BASEPROJECTF4_AD9235X_H

#include "Framework.h"

typedef enum{
    Get_Data = 0x0e,
    Set_Sample_Rate
}ads9235_commend;

typedef struct ad9235x_class{
    /*===========================��Ա����=========================*/
    ro          S_H_type                    SPI_Mode;

    ro          periperal                   SPI;                //SPI���裨SPI_Mode==HARDWAREʱ��Ч��
    ro          gpio_type                   SCLK;               //SCLK���ţ�SPI_Mode==SOFTWAREʱ��Ч��
    ro          gpio_type                   MOSI;               //MOSI���ţ�SPI_Mode==SOFTWAREʱ��Ч��
    ro          gpio_type                   MISO;               //MISO���ţ�SPI_Mode==SOFTWAREʱ��Ч��
    ro          gpio_type                   CS;
    /*===========================����============================*/

    void    (*Send_Commend)             (struct ad9235x_class* device, ads9235_commend cmd);

    /**************************************************************
     *
     *************************************************************/
    void 	(*Get_Data)				   (struct ad9235x_class* device, uint32_t num, void* dat_buf, data_format_type fmt);

}ad9235x;


// ����һ��ad9235
void AD9235x_Prepare(ad9235x* dev, S_H_type mode, uint32_t spi_value, void* spi_reg0, void* spi_reg1,
                     inst_type inst, gpio_type sclk, gpio_type mosi, gpio_type miso, gpio_type cs);


#endif //BASEPROJECTF4_AD9235X_H

