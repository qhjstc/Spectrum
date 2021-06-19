## FFTʹ��˵��

###

- ��4����FFT������
```c
#include "arm_math.h"   
#define FFT_LENGTH	1024                    // ע��Ҫ����4�ı��� 
arm_cfft_radix4_instance_f32 scfft;         
float cfft_inputbuf[FFT_LENGTH*2]= {0};
float cfft_outputbuf[FFT_LENGTH] = {0};

void FFT_Init(){
    arm_cfft_radix4_init_f32(&scfft,FFT_LENGTH,0,1);        // ��ʼ��srfft�ṹ��, �趨FFT����ز���
}

void FFT(){
    for(i = 0; i < (FFT_LENGTH); i++){
    win = 0.50f - 0.50f*arm_cos_f32(2*pi*(i+1)) / FFT_LENGTH;
    volts[i] *= win;
    cfft_inputbuf[2*i] = volts[i];
    cfft_inputbuf[2*i+1] =0;                                // �鲿��ֵ0
    }
    
    arm_cfft_radix4_f32(&scfft,cfft_inputbuf);                      // FFT���㣨��4��
    arm_cmplx_mag_f32(cfft_inputbuf,cfft_outputbuf,FFT_LENGTH);     // ��������������÷�ֵ
}
```

- ��4ʵ��FFT������
```c
#include "arm_math.h"
#define FFT_LENGTH	1024                    // ע��Ҫ����4�ı��� 
arm_rfft_fast_instance_f32 srfft;
float rfft_inputbuf[FFT_LENGTH]= {0};       // ��������
float rfft_outputbuf[FFT_LENGTH] = {0};     // �������

void FFT_Init(){
    arm_rfft_fast_init_f32(&srfft, FFT_LENGTH);         // ��ʼ��
}

void FFT(){
    arm_rfft_fast_f32(&srfft, rfft_inputbuf, rfft_outputbuf, 0);
    arm_cmplx_mag_f32(rfft_outputbuf, testOutput, FFT_LENGTH);
}
```
