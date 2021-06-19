## FFT使用说明

###

- 基4虚数FFT，样例
```c
#include "arm_math.h"   
#define FFT_LENGTH	1024                    // 注意要输入4的倍数 
arm_cfft_radix4_instance_f32 scfft;         
float cfft_inputbuf[FFT_LENGTH*2]= {0};
float cfft_outputbuf[FFT_LENGTH] = {0};

void FFT_Init(){
    arm_cfft_radix4_init_f32(&scfft,FFT_LENGTH,0,1);        // 初始化srfft结构体, 设定FFT的相关参数
}

void FFT(){
    for(i = 0; i < (FFT_LENGTH); i++){
    win = 0.50f - 0.50f*arm_cos_f32(2*pi*(i+1)) / FFT_LENGTH;
    volts[i] *= win;
    cfft_inputbuf[2*i] = volts[i];
    cfft_inputbuf[2*i+1] =0;                                // 虚部赋值0
    }
    
    arm_cfft_radix4_f32(&scfft,cfft_inputbuf);                      // FFT计算（基4）
    arm_cmplx_mag_f32(cfft_inputbuf,cfft_outputbuf,FFT_LENGTH);     // 把运算结果复数求得幅值
}
```

- 基4实数FFT，样例
```c
#include "arm_math.h"
#define FFT_LENGTH	1024                    // 注意要输入4的倍数 
arm_rfft_fast_instance_f32 srfft;
float rfft_inputbuf[FFT_LENGTH]= {0};       // 输入数组
float rfft_outputbuf[FFT_LENGTH] = {0};     // 输出数组

void FFT_Init(){
    arm_rfft_fast_init_f32(&srfft, FFT_LENGTH);         // 初始化
}

void FFT(){
    arm_rfft_fast_f32(&srfft, rfft_inputbuf, rfft_outputbuf, 0);
    arm_cmplx_mag_f32(rfft_outputbuf, testOutput, FFT_LENGTH);
}
```
