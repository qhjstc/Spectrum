/***************************************************************************
*|------------------------------------------------------------------------
*|-------------------------------ADF4351������------------------------------
****************************************************************************/
#ifndef BASEPROJECT_ADF4351_H
#define BASEPROJECT_ADF4351_H

#include <stdint.h>
#include "Framework.h"

/*============================================ADF4351�Ĵ�������=========================================================*/
/********************Register0**************************/
typedef struct{
    uint16_t int_value;     // ��������
    uint16_t frac_value;    // С������
}adf4351_register_0;

/********************Register1**************************/
typedef enum {
    PRESCALER_4_5 = 0,
    PRESCALER_8_9
} adf4351_prescaler_type;

typedef struct{
    uint8_t                 phase_adjust;       // ��λ������0: �ر�, 1: ����
    adf4351_prescaler_type  prescaler;          // Ԥ��Ƶ��0: 4/5, 1: 8/9
    uint16_t                phase_value;        // ��λֵ��0 ~ 4096
    uint16_t                mod_value;          // mode value
}adf4351_register_1;

/********************Register2**************************/
typedef enum {
    LOW_NOISE_MODE = 0,
    LOW_SPUR_MODE = 3
} adf4351_low_noise_spur_mode_type;

typedef enum {
    MUXOUT_3_STATE = 0,
    MUXOUT_DVDD,
    MUTOUT_DGND,
    MUXOUT_R_DIVIDER,
    MUXOUT_N_DIVIDER,
    MUXOUT_ANALOG_LOCK,
    MUXOUT_DIGITAL_LOCK
} adf4351_muxout_type;

typedef enum {
    CHARGE_PUMP_CURRENT_0_31 = 0,
    CHARGE_PUMP_CURRENT_0_63,
    CHARGE_PUMP_CURRENT_0_94,
    CHARGE_PUMP_CURRENT_1_25,
    CHARGE_PUMP_CURRENT_1_56,
    CHARGE_PUMP_CURRENT_1_88,
    CHARGE_PUMP_CURRENT_2_19,
    CHARGE_PUMP_CURRENT_2_50,
    CHARGE_PUMP_CURRENT_2_81,
    CHARGE_PUMP_CURRENT_3_13,
    CHARGE_PUMP_CURRENT_3_44,
    CHARGE_PUMP_CURRENT_3_75,
    CHARGE_PUMP_CURRENT_4_06,
    CHARGE_PUMP_CURRENT_4_38,
    CHARGE_PUMP_CURRENT_4_69,
    CHARGE_PUMP_CURRENT_5_00
} adf4351_charge_pump_current_type;

typedef enum {
    LDF_FRAC_N = 0,
    LDF_INT_N
} adf4351_ldf_type;

typedef enum {
    LDP_10ns = 0,
    LDP_6ns
} adf4351_ldp_type;

typedef enum {
    PD_POLARITY_NEGTIVE = 0,
    PD_POLARITY_POSTIVE
} adf4351_pd_polarity_type;

typedef struct{
    adf4351_low_noise_spur_mode_type    low_noise_spur_mode;    // �������͵���ɢģʽ
    adf4351_muxout_type                 muxout;                 // ��·����
    uint8_t                             ref_double;             // ����2��Ƶ��0: �ر�, 1: ����
    uint8_t                             ref_div2;               // ����2��Ƶ��0: �ر�, 1: ����
    uint16_t                            r_counter;              // ����R��Ƶ��1 ~ 1023
    uint8_t                             double_buffer;          // ˫���壬0: �ر�, 1: ����
    adf4351_charge_pump_current_type    charge_pump_current;    // ��ɱõ���
    adf4351_ldf_type                    ldf;                    // ������⹦�ܣ�����С��N��Ƶģʽ��������Ϊ0;��������N��Ƶģʽ��������Ϊ1
    adf4351_ldp_type                    ldp;                    // ������⾫�ȣ�����С��N��Ƶģʽ��������Ϊ0;��������N��Ƶģʽ��������Ϊ1
    adf4351_pd_polarity_type            pd_polarity;            // ����������
    uint8_t                             power_down;             // �ضϣ�0: ����������1: �ض�
    uint8_t                             cp_3_state;             // ��ɱ���̬������Ϊ1ʱ����ɱý�����̬ģʽ����������ʱ��Ӧ����Ϊ0
    uint8_t                             counter_reset;          // ��Ƶ����λ������Ϊ1ʱ��RFƵ�ʺϳ���N��Ƶ����R��Ƶ�����ڸ�λ״̬����������ʱ��Ӧ����Ϊ0
}adf4351_register_2;

/********************Register3**************************/
typedef enum {
    BAND_SELECT_CLOCK_MODE_LOW = 0,
    BAND_SELECT_CLOCK_MODE_HIGH
} adf4351_band_select_clock_mode_type;

typedef enum {
    ABP_6ns = 0,
    ABP_3ns
} adf4351_abp_type;

typedef enum {
    CLOCK_DIV_MODE_CLOCK_DIVIDER_OFF = 0,
    CLOCK_DIV_MODE_FAST_LOCK_ENABLE,
    CLOCK_DIV_MODE_RESYNC_ENABLE
} adf4351_clock_div_mode_type;

typedef struct{
    adf4351_band_select_clock_mode_type band_select_clock_mode;     // Ƶ��ѡ��ʱ��ģʽ
    adf4351_abp_type                    abp;                        // �����������ȣ���Ϊ1ʱ��PFD������������Ϊ3ns���ɸ�������N��Ƶ��������λ��������ɢ���ܡ�����С��N��Ƶ������������ʹ��3ns����
    uint8_t                             charge_cancellation;        // �����������Ϊ1��ʹ�ܵ�ɱõ���������ܣ�����Խ����� ��N��Ƶģʽ�µ�PFD��ɢ����С��N��Ƶģʽ�£�Ӧ����Ϊ0
    uint8_t                             csr;                        // ��������ʹ�ܣ�0�رգ�1����
    adf4351_clock_div_mode_type         clock_div_mode;             // ʱ�ӷ�Ƶ��ģʽ
    uint16_t                            clock_divider_value;        // ʱ�ӷ�Ƶ��ֵ��0 �� 4095
}adf4351_register_3;

/********************Register4**************************/
typedef enum {
    FEEDBACK_SIGNAL_DIVIDED = 0,
    FEEDBACK_SIGNAL_FUNDAMENTAL
} adf4351_feedback_select_type;

typedef enum {
    AUX_OUTPUT_SELECT_DIVIDED = 0,
    AUX_OUTPUT_SELECT_FUNDAMENTAL
} adf4351_aux_output_select_type;

typedef enum {
    AUX_OUTPUT_POWER_neg_4 = 0,
    AUX_OUTPUT_POWER_neg_1,
    AUX_OUTPUT_POWER_pos_2,
    AUX_OUTPUT_POWER_pos_5
} adf4351_aux_output_power_type;

typedef enum {
    RF_OUTPUT_POWER_neg_4 = 0,
    RF_OUTPUT_POWER_neg_1,
    RF_OUTPUT_POWER_pos_2,
    RF_OUTPUT_POWER_pos_5
} adf4351_rf_output_power_type;

typedef enum {
    OUTPUT_DIVIDER_1 = 0,
    OUTPUT_DIVIDER_2,
    OUTPUT_DIVIDER_4,
    OUTPUT_DIVIDER_8,
    OUTPUT_DIVIDER_16,
    OUTPUT_DIVIDER_32,
    OUTPUT_DIVIDER_64,
} adf4351_output_divider_type;

typedef struct{
    adf4351_feedback_select_type    feedback_select;            // ����ѡ��0: ��Ƶ��, 1: ԭʼ
    uint8_t                         vco_power_down;             // VCO�ضϣ�0�ϵ磬1�ض�
    uint8_t                         mtld;                       // ��������⵽�������������Ϊ1�����ж�RF������ĵ�Դ������ֱ��������������·��⵽����ʵ������Ϊֹ
    adf4351_aux_output_select_type  aux_output_select;          // �������ѡ��
    uint8_t                         aux_output_enable;          // �������ʹ�ܣ�0���������1�������
    adf4351_aux_output_power_type   aux_output_power;           // �����������
    uint8_t                         rf_output_enable;           // RF���ʹ�ܣ�0���������1�������
    adf4351_rf_output_power_type    rf_output_power;            // RF�������
    uint8_t                         band_select_clock_divider;  // Ƶ��ѡ��ʱ�ӷ�Ƶ��ֵ��1 ~ 255��R��Ƶ�������Ĭ������Ƶ��ѡ���߼�ʱ�ӣ��������ֵ̫��(>125 kHz)�����������һ����Ƶ�����Խ�R��Ƶ�����ϸ��Ϊ��С��ֵ
    adf4351_output_divider_type     output_divider;
}adf4351_register_4;

/********************Register5**************************/
typedef enum {
    LD_PIN_MODE_LOW = 0,
    LD_PIN_MODE_DIGITAL_LOCK_DETECT = 1,
    LD_PIN_MODE_HIGH = 3
} adf4351_ld_pin_mode_type;

typedef struct{
    adf4351_ld_pin_mode_type        ld_pin_mode;       // ����������Ź�����ʽ
}adf4351_register_5;

/*=================================================ADF4351 Class======================================================*/
/*
 * ADF4351��
 * ��ΪADF4351�ļĴ������涫��ʵ��̫���ˣ����Ե��������˼Ĵ����Ľṹ��
 */
typedef struct adf4351_class{
    /*===================================��Ա����===============================*/
    adf4351_register_0          register0;                  // �Ĵ�������
    adf4351_register_1          register1;
    adf4351_register_2          register2;
    adf4351_register_3          register3;
    adf4351_register_4          register4;
    adf4351_register_5          register5;
    uint32_t                    reference_frequency;        // ����Ƶ��, ��λ: MHz
    float                       output_frequency;           // ���Ƶ�ʣ���λ: MHz
    float                       channel_spacing;            // Ƶ�ʼ������λ: KHz(һ������100k)

    ro      S_H_type            mode;
    ro      gpio_type           sclk;
    ro      gpio_type           mosi;
    ro      gpio_type           le;
    ro      gpio_type           ce;
    ro      periperal           spi;                        // ADF4351 SPI

    /*===================================����==========================================*/
    /********************************************************************
	*���ܣ��������໷���													*
	*������1.device�����ʵ��											    *
	*	   2.frequency�����õ����Ƶ��										*
	*˵������															    *
	*********************************************************************/
    void    (*Set_Output_Frequency)             (struct adf4351_class* device, float frequency);

    /********************************************************************
	*���ܣ���������ֵ													    *
	*������1.device�����ʵ��											    *
	*	   2.reference_frequency:����ο�Ƶ��							    *
    *	    3.channel_spacing:�����Ƶ�ʼ��(һ������100k)                   *
	*˵������															    *
	*********************************************************************/
    void    (*Set_Common_Param)                 (struct adf4351_class* device, uint32_t reference_frequency, float channel_spacing);

    /********************************************************************
    *���ܣ�����													        *
    *������1.device�����ʵ��											    *
    *	   2.power: ������ʣ��ֱ�������ģʽ                                 *
    *	            (RF_OUTPUT_POWER_neg_4,RF_OUTPUT_POWER_neg_1,       *
    *	            RF_OUTPUT_POWER_pos_2,RF_OUTPUT_POWER_pos_5         *
    *˵������															    *
    *********************************************************************/
    void    (*Set_Aux_Output_Power)             (struct adf4351_class* device, adf4351_rf_output_power_type power);

    /********************************************************************
    *���ܣ�д�Ĵ���													*
    *������1.device�����ʵ��											*
    *	   2.word: ��Ҫд��ļĴ���ֵ��Ҫ������λ32λ������					*
    *˵������															*
    *********************************************************************/
    void    (*Write_Reg)                        (struct adf4351_class*, uint32_t word);

} adf4351;


// �ඨ��
//typedef struct adf4351_class* adf4351;


/*================================================================================*/
/********************************************************************

*********************************************************************/
//void New_ADF4351(adf4351* device, uint16_t value, peripheral_register_type reg0, peripheral_register_type reg1,
//                 inst_type instance);
void ADF4351_Prepare(adf4351* device,  S_H_type, uint32_t value, void* reg0, void* reg1,
                   inst_type instance, gpio_type sclk, gpio_type mosi, gpio_type le, gpio_type ce);

#endif //BASEPROJECT_ADF4351_H

