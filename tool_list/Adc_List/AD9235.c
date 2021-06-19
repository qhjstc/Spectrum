#include "AD9235.h"

//真实电压值=测量值(0~0xfff)*k+b        (拟合)
#define k (0.002442f)
#define b (-5.0f)
/*==================================================用户函数============================================================*/

//#define DMA_Enable(dma)

// 设置DMA
void DMA_Set(ro periperal dma, void* dat_buf, uint32_t num){
    //补全你的代码
}

// 开启DMA
void DMA_Enable(ro periperal dma){
    //补全你的代码
}

// 关闭DMA
void DMA_Stop(ro periperal dma){

}

// 设置定时器的频率
void Timer_Set_Frequency(ro periperal tim, uint32_t fs){

}

// 开启定时器
void Timer_Enable(ro periperal tim){

}

// 关闭定时器
void Timer_Disable(ro periperal tim){

}

uint8_t Get_DMA_TCIF(ro periperal dma){

    return 0;
}

// 获取引脚状态(也就是获取值)
uint16_t GPIO_Group_Read(ro GPIO_TypeDef* gpio){
    u16 data = 0;
    data |= gpio->IDR;
    data |= 0x0fff;                             // 因为只有12个引脚，所以清楚前4位
    return data;
}

/*=====================================================================================================================*/

/***************************函数定义***********************************/
//void Method_AD9235_Get_One_Data(struct ad9235_class* device, void* dat_buf, uint32_t num){
//
//}

void Method_AD9235_Get_Data(struct ad9235_class* device, uint32_t fs, uint32_t num, void* datbuf, data_format_type fmt){
    int i;
    if (device->mode==HARDWARE){                                 // 硬件模式
        DMA_Set(device->dma,datbuf,num);                         // 设置DMA
        Timer_Set_Frequency(device->tim,fs);
        DMA_Enable(device->dma);
        Timer_Enable(device->tim);
        while (Get_DMA_TCIF(device->dma)==0);
        DMA_Stop(device->dma);
        Timer_Disable(device->tim);
    }
    else if (device->mode==SOFTWARE){                           // 软件模式
        SystemTimer_Timing_Ready(1000000.0f/fs);        // 设施system tick时间
        GPIO_Write(device->Sclk, 0);                      // 先清零
        SystemTimer_Timing_Begin();
        for (i=0; i<num; i++){
            GPIO_Write(device->Sclk, 1);
            ((uint16_t*)datbuf)[i]=GPIO_Group_Read(device->gpio);
            ((uint16_t*)datbuf)[i]&=0xfff;
            while (SystemTimer_Timing_Check()==0);
            GPIO_Write(device->Sclk, 0);
        }
    }

    if (fmt==FLOAT_Format){
        for (i=num-1;i>=0;i--){
            ((float*)datbuf)[num-1-i]=((uint16_t*)datbuf)[num-1-i]*k+b;
        }
    }
}

/**************************外部函数************************************/
void AD9235_Prepare(ad9235* dev, S_H_type mode,
                  uint32_t dma_value, void* dma_reg0, void* dma_reg1, inst_type dma_inst,
                  uint32_t tim_value, void* tim_reg0, void* tim_reg1, inst_type tim_inst,
                  gpio_type sclk,
                  GPIO_TypeDef* gpio
){
    _RO_WRITE(dev->mode,S_H_type,mode);

    if(dev->mode == HARDWARE){
        _RO_WRITE(dev->dma.Value,uint32_t,dma_value);
        _RO_WRITE(dev->dma.Register0,void*,dma_reg0);
        _RO_WRITE(dev->dma.Register1,void*,dma_reg1);
        _RO_WRITE(dev->dma.Instance,inst_type,dma_inst);

        _RO_WRITE(dev->tim.Value,uint32_t,tim_value);
        _RO_WRITE(dev->tim.Register0,void*,tim_reg0);
        _RO_WRITE(dev->tim.Register1,void*,tim_reg1);
        _RO_WRITE(dev->tim.Instance,inst_type,tim_inst);
    }
    else{
        _RO_WRITE(dev->Sclk,gpio_type,sclk);
    }
    _RO_WRITE(dev->gpio,GPIO_TypeDef*, gpio);

    dev->Get_Data = Method_AD9235_Get_Data;
}




















