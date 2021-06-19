# ADF4351使用手册

## 1、包含文件
- `ADF4351.c`
- `ADF4351.h`

## 2、函数介绍
- ADF4351结构体函数

| 函数 | 参数| 功能|是否需要改写|
|-----|-----|-----|------|
|void Set_Output_Frequency(<font color="##3CB371">struct adf4351_class* device, float frequency</font>)| device:配置的adf4351, frequency:输出频率(单位:MHz, 注意范围).|设置ADF4351的输出频率;|不需要|
|void Set_Common_Param(<font color="##3CB371">struct adf4351_class* device, uint32_t reference_frequency, float channel_spacing</font>)|device:配置的adf4351, frequency:参考频率(单位:MHz,一般为100M), channel_spacing:间隔频率(单位:KHz,一般为100k).|设置ADF4351的参考频率和间隔频率;|不需要 |
|void Set_Aux_Output_Power(<font color="##3CB371">struct adf4351_class* device, adf4351_rf_output_power_type power</font>)|device:配置的adf4351, power:RF输出功率(0:-4dbm, 1:-2dbm, 2:+2dbm, 3:+5dbm)|设置ADF4351的输出功率;|不需要|

- 用户配置函数

|函数|参数|功能|是否需要改写|
|-----|-----|-----|------|
|void ADF4351_Spi_Transmit(<font color="##3CB371">adf4351* device, uint8_t data</font>)|device:配置的adf4351, data:传输的数据(8位)|初始化ADF4351|需要|

- Prepare函数

    1、`void ADF4351_Prepare(adf4351* device, S_H_type mode, uint32_t value, void* reg0, void* reg1,
                            inst_type instance, gpio_type sclk, gpio_type mosi, gpio_type le, gpio_type ce)`
  
    2、参数:

    - **device**: 需要配置的adf4351;
    - **mode**: 模式（HARDWARE or SOFTWARE）;
    - **value**: 非必要（一般设置为0）;
    - **reg0**: spi寄存器0(不使用时设置0);
    - **reg1**: spi寄存器1(不使用时设置为0);
    - **instance**: HAL库的spi句柄(不使用时设置为0);
    - **sclk**: adf4351的sclk引脚(不使用软件模拟spi的时候设置为0);
    - **mosi**: adf4351的mosi引脚(不使用软件模拟spi的时候设置为0);
    - **le**: adf4351的le引脚(不使用软件模拟spi的时候设置为0);
    - **ce**: adf4351的ce引脚(不使用软件模拟spi的时候设置为0);
    
## 3、使用样例
```c
1、"main.c"
    adf4351 adf4351_1;
    ADF4351_Prepare(&adf4351_1, HARDWARE, 0, 0, 0, &hspi3,0,0, GPIOC_4, GPIOC_5);
    adf4351_1.Set_Output_Frequency(&adf4351_1, 250); // 设置输出频率为250M;
    
2、"ADF4351.c"
    void ADF4351_Spi_Transmit(ro periperal* spi, uint8_t data){
    HAL_SPI_Transmit(spi->Instance, &data, 1, 1000);
    }
_________________________________________________________________________________________
```









