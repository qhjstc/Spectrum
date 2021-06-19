
#include "ADF4351.h"
#include "math.h"
///////////////////////////////////////////////////////////////////////////////////////////////
// �û���������

void ADF4351_Spi_Transmit(ro periperal* spi, uint8_t data);
// �û��Լ�ʵ�ֵ�spi����,ÿ��ֻд8λ,(ע��ֻ����д��������CS���ŵ���������)
void ADF4351_Spi_Transmit(ro periperal* spi, uint8_t data){
    /* USER CODE BEGIN */
    HAL_SPI_Transmit(spi->Instance, &data, 1, 1000);
    /* USER CODE END */
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//ADF4351 VCO�����Χ
#define VCO_MAX_FREQUENCY 4400.
#define VCO_MIN_FREQUENCY 2200.

//���üĴ�����ַ����
#define REG_0	0
#define REG_1   1
#define REG_2	2
#define REG_3	3
#define REG_4   4
#define REG_5   5

/*=====================================��������================================================*/
uint32_t    ADF4351_Generate_Register(uint8_t reg_num, adf4351* device);
float       ADF4351_Get_Actual_Frequency(adf4351* device);
void        Method_ADF4351_Set_Output_Frequency(adf4351* device, float frequency);
void        Method_ADF4351_Write_Reg(adf4351* device, uint32_t word);
void        Method_ADF4351_Set_Aux_Output_Power(adf4351* device, adf4351_rf_output_power_type power);
void        Method_ADF4351_Set_Common_Param(adf4351* device, uint32_t reference_frequency, float channel_spacing);
/*======================================��ѧ���㷽��==============================================*/
/**
 * շת����������Լ��
 */
uint32_t GCD(uint32_t a, uint32_t b) {
    return a == 0 ? b : GCD(b % a, a);
}
/*========================================ADF4351����===========================================*/

/**
 * ͨ������ֵ����ADF4351����ֵ���������������֤�����Ƿ����Ҳ�����޸����õ�ֵ����ʹ����ֵ�Ǵ����
 * @
 * @return ADF4351�����ṹ��
 */
void ADF4351_Calculate_Parameter(adf4351* device) {
    // output frequency should be less than 4400MHz and grater than 35MHz, VCO frequency is 2200 to 4400
    if (device->output_frequency > VCO_MIN_FREQUENCY) {
        device->register4.output_divider = OUTPUT_DIVIDER_1;
    } else if (device->output_frequency > VCO_MIN_FREQUENCY / 2) {
        device->register4.output_divider = OUTPUT_DIVIDER_2;
    } else if (device->output_frequency > VCO_MIN_FREQUENCY / 4) {
        device->register4.output_divider = OUTPUT_DIVIDER_4;
    } else if (device->output_frequency > VCO_MIN_FREQUENCY / 8) {
        device->register4.output_divider = OUTPUT_DIVIDER_8;
    } else if (device->output_frequency > VCO_MIN_FREQUENCY / 16) {
        device->register4.output_divider = OUTPUT_DIVIDER_16;
    } else if (device->output_frequency > VCO_MIN_FREQUENCY / 32) {
        device->register4.output_divider = OUTPUT_DIVIDER_32;
    } else {
        device->register4.output_divider = OUTPUT_DIVIDER_64;
    }
    // PFD
    const float pfd_frequency = device->reference_frequency * (device->register2.ref_double + 1) / (device->register2.ref_div2 + 1) / device->register2.r_counter;
    // ����Ƶ��
    const float feedback_frequency = device->register4.feedback_select == FEEDBACK_SIGNAL_FUNDAMENTAL ? (device->output_frequency * (1 << device->register4.output_divider)) : device->output_frequency;
    // N=����Ƶ��/PFD
    const float N = feedback_frequency / pfd_frequency;
    device->register0.int_value = (uint16_t)N;
    // ��������ȡ��
    device->register1.mod_value = roundf(pfd_frequency * 1e3 / device->channel_spacing);
    // ��֤MOD < 0xfff
    if (device->register1.mod_value > 0xfff) {
        device->register1.mod_value = 0xfff;
    }
    // ��������ȡ��
    device->register0.frac_value = round(device->register1.mod_value * (N - device->register0.int_value));
    // Լ��
    const uint32_t gcd = GCD(device->register0.frac_value, device->register1.mod_value);
    device->register0.frac_value /= gcd;
    device->register1.mod_value /= gcd;

    // INT������ڵ���75(prescaler=8/9)��23(prescaler=4/5)
    if (device->register1.prescaler == PRESCALER_8_9 && device->register0.int_value < 75) {
        device->register0.int_value = 75;
    }
    if (device->register1.prescaler == PRESCALER_4_5 && device->register0.int_value < 23) {
        device->register0.int_value = 23;
    }
}

/**
 * ���ɼĴ���ֵ
 * @param reg_num �Ĵ����ţ�0 ~ 5
 * @param device ADF4351���ýṹ���ָ��
 * @return �Ĵ���ֵ
 */
uint32_t ADF4351_Generate_Register(uint8_t reg_num, adf4351* device) {
    uint32_t value = reg_num;
    switch (reg_num) {
        case 0: {
            value |= device->register0.int_value << 15u;
            value |= device->register0.frac_value << 3u;
            break;
        }
        case 1: {
            value |= device->register1.phase_adjust << 28u;
            value |= device->register1.prescaler << 27u;
            value |= device->register1.phase_value<< 15u;
            value |= device->register1.mod_value << 3u;
            break;
        }
        case 2: {
            value |= device->register2.low_noise_spur_mode << 29u;
            value |= device->register2.muxout << 26u;
            value |= device->register2.ref_double << 25u;
            value |= device->register2.ref_div2 << 24u;
            value |= device->register2.r_counter << 14u;
            value |= device->register2.double_buffer << 13u;
            value |= device->register2.charge_pump_current << 9u;
            value |= device->register2.ldf << 8u;
            value |= device->register2.ldp << 7u;
            value |= device->register2.pd_polarity << 6u;
            value |= device->register2.power_down << 5u;
            value |= device->register2.cp_3_state << 4u;
            value |= device->register2.counter_reset << 3u;
            break;
        }
        case 3: {
            value |= device->register3.band_select_clock_mode << 23u;
            value |= device->register3.abp << 22u;
            value |= device->register3.charge_cancellation << 21u;
            value |= device->register3.csr << 18u;
            value |= device->register3.clock_div_mode << 15u;
            value |= device->register3.clock_divider_value << 3u;
            break;
        }
        case 4: {
            value |= device->register4.feedback_select << 23u;
            value |= device->register4.output_divider << 20u;
            value |= device->register4.band_select_clock_divider << 12u;
            value |= device->register4.vco_power_down << 11u;
            value |= device->register4.mtld << 10u;
            value |= device->register4.aux_output_select << 9u;
            value |= device->register4.aux_output_enable << 8u;
            value |= device->register4.aux_output_power << 6u;
            value |= device->register4.rf_output_enable << 5u;
            value |= device->register4.rf_output_power << 3u;
            break;
        }
        case 5: {
            value |= 0x180000u; // reserved
            value |= device->register5.ld_pin_mode << 22u;
            break;
        }
        default: {
            // unknow reg_num, set to 0
            reg_num = 0;
            break;
        }
    }
    return value;
}

/**
 * �����ʵƵ��
 * @param device ADF4351���ýṹ���ָ��
 * @return ��ʵ��Ƶ�ʣ���λ: MHz
 */
float ADF4351_Get_Actual_Frequency(adf4351* device) {
    float pfd_frequency = device->reference_frequency * (device->register2.ref_double + 1) / (device->register2.ref_div2 + 1);
    if (device->register2.r_counter) {
        pfd_frequency /= device->register2.r_counter;
    }
    return pfd_frequency * (device->register0.int_value + (float)device->register0.frac_value / device->register1.mod_value) / (1u << device->register4.output_divider);
}

/*==========================================================================================================**/
/**
 * д�Ĵ���
 * @param word �Ĵ���ֵ����������λ
 */
void Method_ADF4351_Write_Reg(adf4351* device, uint32_t word) {
    // һ��д8λ�������λ��ʼд
    GPIO_Pin_Reset(device->le);
    SystemTimer_Delay_Ms(5);
    ADF4351_Spi_Transmit(&device->spi, (0xff&(word>>24)));
    ADF4351_Spi_Transmit(&device->spi, (0xff&(word>>16)));
    ADF4351_Spi_Transmit(&device->spi, (0xff&(word>>8)));
    ADF4351_Spi_Transmit(&device->spi, (0xff&(word>>0)));
    SystemTimer_Delay_Ms(5);
    GPIO_Pin_Set(device->le);
    SystemTimer_Delay_Ms(5);
    GPIO_Pin_Reset(device->le);
    SystemTimer_Delay_Ms(5);
}

void Method_ADF4351_Set_Output_Frequency(adf4351* device, float frequency){
    device->output_frequency = frequency;
    ADF4351_Calculate_Parameter(device);
    // �ֱ�Ҫд0��1��4�Ĵ���
    device->Write_Reg(device, ADF4351_Generate_Register(REG_4, device));
    device->Write_Reg(device, ADF4351_Generate_Register(REG_1, device));
    device->Write_Reg(device, ADF4351_Generate_Register(REG_0, device));
}

void Method_ADF4351_Set_Common_Param(adf4351* device, uint32_t reference_frequency, float channel_spacing){
    device->reference_frequency = reference_frequency;
    device->channel_spacing     = channel_spacing;
    device->Write_Reg(device, ADF4351_Generate_Register(REG_5, device));
    device->Write_Reg(device, ADF4351_Generate_Register(REG_4, device));
    device->Write_Reg(device, ADF4351_Generate_Register(REG_3, device));
    device->Write_Reg(device, ADF4351_Generate_Register(REG_2, device));
    device->Write_Reg(device, ADF4351_Generate_Register(REG_1, device));
    device->Write_Reg(device, ADF4351_Generate_Register(REG_0, device));
}

void Method_ADF4351_Set_Aux_Output_Power(adf4351* device, adf4351_rf_output_power_type power){
    device->register4.rf_output_power = power;
    device->Write_Reg(device, ADF4351_Generate_Register(REG_4, device));
}

/*================================================================================================*/
void ADF4351_Prepare(adf4351* device, S_H_type mode, uint32_t value, void* reg0, void* reg1,
                     inst_type instance, gpio_type sclk, gpio_type mosi, gpio_type le, gpio_type ce){

    // ����һЩ����
    device->reference_frequency = 100;
    device->output_frequency    = 556;
    device->channel_spacing     = 100;

    _RO_WRITE(device->mode, S_H_type, mode);
    _RO_WRITE(device->spi.Value, uint32_t, value);
    _RO_WRITE(device->spi.Register0, void*, reg0);
    _RO_WRITE(device->spi.Register1, void*, reg1);
    _RO_WRITE(device->spi.Instance, inst_type, instance);
    _RO_WRITE(device->sclk, gpio_type, sclk);
    _RO_WRITE(device->mosi, gpio_type, mosi);
    _RO_WRITE(device->le, gpio_type, le);
    _RO_WRITE(device->ce, gpio_type, ce);

    // Register 1
    device->register1.prescaler = PRESCALER_4_5;
    device->register1.phase_adjust = 0;
    device->register1.phase_value = 1;
    // Register 2
    device->register2.r_counter                     = 1;
    device->register2.ref_double                    = 0;
    device->register2.ref_div2                      = 1;
    device->register2.low_noise_spur_mode           = LOW_NOISE_MODE;
    device->register2.muxout                        = MUXOUT_ANALOG_LOCK;
    device->register2.double_buffer                 = 0;
    device->register2.charge_pump_current           = CHARGE_PUMP_CURRENT_2_50;
    device->register2.ldf                           = LDF_FRAC_N;
    device->register2.ldp                           = LDP_10ns;
    device->register2.pd_polarity                   = PD_POLARITY_POSTIVE;
    device->register2.power_down                    = 0;
    device->register2.cp_3_state                    = 0;
    device->register2.counter_reset                 = 0;
    // Register 3
    device->register3.band_select_clock_mode        = BAND_SELECT_CLOCK_MODE_LOW;
    device->register3.abp                           = ABP_6ns;
    device->register3.charge_cancellation           = 0;
    device->register3.csr                           = 0;
    device->register3.clock_div_mode                = CLOCK_DIV_MODE_CLOCK_DIVIDER_OFF;
    device->register3.clock_divider_value           = 150;
    //Register 4
    device->register4.feedback_select               = FEEDBACK_SIGNAL_FUNDAMENTAL;
    device->register4.vco_power_down                = 0;
    device->register4.mtld                          = 0;
    device->register4.aux_output_select             = AUX_OUTPUT_SELECT_DIVIDED;
    device->register4.aux_output_enable             = 0;
    device->register4.aux_output_power              = AUX_OUTPUT_POWER_neg_4;
    device->register4.rf_output_enable              = 1;
    device->register4.rf_output_power               = RF_OUTPUT_POWER_pos_5;
    device->register4.band_select_clock_divider     = 200;
    // Register 5
    device->register5.ld_pin_mode                   = LD_PIN_MODE_DIGITAL_LOCK_DETECT;
    // ����
    device->Write_Reg               = Method_ADF4351_Write_Reg;
    device->Set_Output_Frequency    = Method_ADF4351_Set_Output_Frequency;
    device->Set_Common_Param        = Method_ADF4351_Set_Common_Param;
    device->Set_Aux_Output_Power    = Method_ADF4351_Set_Aux_Output_Power;

    // �����ADF4351�Ĳ���
    ADF4351_Calculate_Parameter(device);
    GPIO_Pin_Set(device->ce);
    SystemTimer_Delay_Ms(5);
    // дADF4351�Ĵ���
    device->Write_Reg(device, ADF4351_Generate_Register(REG_5, device));
    device->Write_Reg(device, ADF4351_Generate_Register(REG_4, device));
    device->Write_Reg(device, ADF4351_Generate_Register(REG_3, device));
    device->Write_Reg(device, ADF4351_Generate_Register(REG_2, device));
    device->Write_Reg(device, ADF4351_Generate_Register(REG_1, device));
    device->Write_Reg(device, ADF4351_Generate_Register(REG_0, device));
}



