/********************************************************
 * AD9235��FPGAͨ�� (SPI: CPOL = 1, CPHA = 1)
 *
 *******************************************************/

#ifndef BASEPROJECT_AD9235X_H
#define BASEPROJECT_AD9235X_H

#include "Framework.h"

typedef struct ad9235_class{
    /*===========================��Ա����=========================*/
    ro  S_H_type        mode;

    ro  periperal       dma;
    ro  periperal       tim;

    ro  gpio_type       Sclk;
    ro  GPIO_TypeDef*   gpio;
    /*===========================����============================*/

    /**************************************************************
     *
     *************************************************************/
    void 	(*Get_Data)				   (struct ad9235_class* device, uint32_t fs, uint32_t num, void* datbuf, data_format_type fmt);

    /**************************************************************
     * ����: SPIдһ���ֽ�
     * ����: 1.dat: Ҫд������
     * ˵��: CPHA = 1, CPOL = 1;
     *************************************************************/
    void    (*SPI_Write_Byte)           (uint8_t dat);


    /************************************************************
     * ����: SPI����һ���ֽ�
     * ����: ��
     * ˵��: CPHA = 1, CPOL = 1;
     *************************************************************/
    uint8_t (*SPI_Read_Byte)            (void);

}ad9235;


// ����һ��ad9235
void AD9235_Prepare(ad9235* dev, S_H_type mode,
                    uint32_t dma_value, void* dma_reg0, void* dma_reg1, inst_type dma_inst,
                    uint32_t tim_value, void* tim_reg0, void* tim_reg1, inst_type tim_inst,
                    gpio_type sclk,
                    GPIO_TypeDef* gpio);


#endif //BASEPROJECT_AD9235X_H

