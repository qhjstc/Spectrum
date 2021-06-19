/*
*�汾��
*2021.6.4���£�
*1.���Ӷ�F7/H7��֧��
*2.��д��System_Timer�Ĳ������������������Լ�������ԭ�ӵĴ�����
*3.������F7/H7��GPIO��������������GPIO������F7/H7ϵ����Ҳ��ʹ��
*
*
*/


#ifndef _FRAMEWORK_H_
#define _FRAMEWORK_H_

#include <stdint.h>
#include "main.h"
/****************************************************************************************/
/*                                                                                      */
/*                                       ������                                         */
/*                                                                                      */
/****************************************************************************************/

/*======================================================================================*/

/*
*�������Ĳ������꣩��Ҫ�û������Լ���ʵ������������ã�����С�!�����!�������ı�ǣ���˵��
*�������뱻�������ã�����С�����ѡ�ģ��������ı�ǣ���˵���ú��Ӧ�ſ�ѡ���ܣ�����û���
*����ʹ�øù��ܣ��Ϳ��Բ����á�
*
*/

/*******************************
*!�����!                      *
*��Щ��ָ����ʹ�õ���������    *
*���Ӱ�쵽����GPIO��������    *
********************************/
//#define USE_STM32H7     //H7ϵ��
//#define USE_STM32F7   //F7ϵ��
#define USE_STM32F4   //F4ϵ��
//#define USE_STM32F1   //F1ϵ��
/*******************************/


/**********************************
*!����ģ�                        *
*������Ӧ��ͷ�ļ���stm32xxxx.h��  *
***********************************/
#include "stm32f407xx.h"
/**********************************/


/**************************************
*����ѡ�ģ�                           *
*������������������Ƶ               *
*����F103ϵ�����ֵΪ72000000         *
*����F407ϵ�����ֵΪ168000000        *
*����F429/439ϵ�����ֵΪ180000000    *
*�����Լ����...                      *
***************************************/
//#define SYSCLK_MAX_CLOCK    48000000
//#define SYSCLK_MAX_CLOCK    72000000
#define SYSCLK_MAX_CLOCK    168000000
//#define SYSCLK_MAX_CLOCK    180000000
//#define SYSCLK_MAX_CLOCK    400000000
/**************************************/


/****************************************
*!�����!                               *
*ϵͳ��ʱ��������                       *
*ϵͳ��ʱ���������ṩһ�����õ�ʱ�ӻ�׼ *
*�����������ṩͨ�õ���ʱ�����ͼ�ʱ���� *
*0����ʹ��ϵͳ��ʱ��                    *
*1��systick��ʱ��                       *
*2���û��Զ���                          *
*****************************************/
#define SYSTEM_TIMER        1
/****************************************/


#if SYSTEM_TIMER!=0

/**************************************
*!�����!                             *
*ָ����ʱ����ʱ��Ƶ�ʶ���systick��ʱ  *
*�����ֵͨ����SYSCLK��               *
*SYSCLK/8                             *
***************************************/
#define SYSTEM_TIMER_CLOCK  (SYSCLK_MAX_CLOCK>>3)
/**************************************/

#endif




/***********************************************************
*!�����!                                                  *
*STM32�и�������Ĵ����Ķ���                               *
*Ҫʹ�õľͰ�ע��ȡ�������û����Ҫ�õ���������Լ���ӽ�ȥ*
************************************************************/
typedef union
{
    //ADC_TypeDef*                adc;
    //ADC_Common_TypeDef*         adc_common;
    //CAN_TxMailBox_TypeDef*      can_txmailbox;
    //CAN_FIFOMailBox_TypeDef*    can_fifomailbox;
    //CAN_FilterRegister_TypeDef* filterregister;
    //CAN_TypeDef*                can;
    //CRC_TypeDef*                crc;
    //DAC_TypeDef*                dac;
    //DBGMCU_TypeDef*             debugmcu;
    //DCMI_TypeDef*               dcmi;
    //DMA_Stream_TypeDef*         dma_stream;
    //DMA_TypeDef*                dma;
    //DMA2D_TypeDef*              dma2d;
    //ETH_TypeDef*                eth;
    //EXTI_TypeDef*               exti;
    //FLASH_TypeDef*              flash;
    //FMC_Bank1_TypeDef*          fmc_bank1;
    //FMC_Bank1E_TypeDef*         fmc_bank1e;
    //FMC_Bank2_3_TypeDef*        fmc_bank2_3;
    //FMC_Bank4_TypeDef*          fmc_bank4;
    //FMC_Bank5_6_TypeDef*        fmc_bank5_6;
    //GPIO_TypeDef*               gpio;
    //SYSCFG_TypeDef*             syscfg;
    //I2C_TypeDef*                i2c;
    //IWDG_TypeDef*               iwdg;
    //LTDC_TypeDef*               ltdc;
    //LTDC_Layer_TypeDef*         ltdc_layer;
    //PWR_TypeDef*                pwr;
    //RCC_TypeDef*                rcc;
    //RTC_TypeDef*                rtc;
    //SAI_TypeDef*                sai;
    //SAI_Block_TypeDef*          sai_block;
    //SDIO_TypeDef*               sdio;
    SPI_TypeDef*                spi;
    //TIM_TypeDef*                tim;
    //USART_TypeDef*              usart;
    //WWDG_TypeDef*               wwdg;
    //RNG_TypeDef*                rng;
    //USB_OTG_GlobalTypeDef*      usa_otg_global;
    //USB_OTG_DeviceTypeDef*      usb_otg_device;
    //USB_OTG_INEndpointTypeDef*  usb_otg_inendpoint;
    //USB_OTG_OUTEndpointTypeDef* usb_otg_outendpoint;
    //USB_OTG_HostTypeDef*        usb_otg_host;
    //USB_OTG_HostChannelTypeDef* usb_otg_hostchannel;
} peripheral_register_type;
/**********************************************************/

/*====================================END=====================================*/













/****************************************************************************************/
/*                                                                                      */
/*                                       ������                                         */
/*                                                                                      */
/****************************************************************************************/

/*======================================================================================*/

#define AHB_MAX_CLOCK       SYSCLK_MAX_CLOCK
#define APB1_MAX_CLOCK      (SYSCLK_MAX_CLOCK>>2)
#define APB2_MAX_CLOCK      (SYSCLK_MAX_CLOCK>>1)

/*
*Ϊ����ǿ����ɶ��ԣ����弸�ֿ��ܻ��õ�����������
*1.sign����־��
*        ���һ������ֻ�𵽱�־�����ã�ֻ�������޵ļ���״̬����
*        ��ôӦ����sign���Σ�����һ������������ʾADC�Ƿ��ȡ��
*        �ϣ���ô�ı�������һ����־λ������ֵֻ���߼������壬
*        û��ʵ�ʴ�С�����塣
*2.reg���Ĵ�����
*       �𵽼Ĵ������õı����������Σ�����ñ�����Ӧ���ⲿоƬ
*       �е�ĳ��ʵ�ʵļĴ�������Ӧ����reg���Ρ�
*3.ro��ֻ����
*      �ñ���ֻϣ�����û���ȡ���û���Ӧ�øı���ֵ�����һ����
*      ro���Σ���ô�ñ����������ֵ�Ժ���ã�����������ִ��
*      ���̶�����ı䡣
*4.vro��ֻ�����ҿ��ܾ�����_RO_WRITE�����ı�
*/
#define ro      const           //ֻ������
#define vro     volatile const  //vro

//ֻ�����͵�д�뷽��
//�����������壺���󡢶�����������͡�Ҫд���ֵ
#define _RO_WRITE(object,type,value)	*((type*)((uint32_t)(&object)))=value

typedef void*   inst_type;  //ʵ�����ͣ���Ӧ�������ʵ��

/*
*����ӿ���
*��ԼĴ���д������׼��д����HAL��д��������ӿ�
*��������Ŀ�������ø���д��������ͳһ��ʽ��������
*/
typedef struct peripheral_interface_class
{
    //���û����о��������ã�����б�Ҫʹ�õĻ�������ȻҲ���Բ�ʹ��
    ro uint32_t                    Value;

    //�������ļĴ�����ַ���磺TIM1��USART1��SPI2��
    ro peripheral_register_type    Register0;

    //�����õģ��������ļĴ�����ַ���磺TIM1��USART1��SPI2��
    //���һ��Register0�����òſ��������
    ro peripheral_register_type    Register1;

    //���ĳЩ���ж���Ľṹ��
    //��HAL���е�SPI_Handler��
    ro inst_type                   Instance;
} periperal;

//C���Ի�����������
//�ڽ�����������ת����ʱ����Щ������ܻ�����
typedef enum
{
    UCHAR_Format,
    CHAR_Format,
    USHORT_Format,
    SHORT_Format,
    INT_Format,
    UINT_Format,
    FLOAT_Format,
    DOUBLE_Format
} data_format_type;

//Ӳ�������
//ָ��һЩ���蹦�ܵ�ʵ�ַ���
//��Ӳ��SPI�����ģ��SPI
typedef enum
{
    SOFTWARE,
    HARDWARE
} S_H_type;


typedef enum
{
    Enable=1,
    Disable=0
} status_flag;



/*========================================END===========================================*/










/****************************************************************************************/
/*                                                                                      */
/*                                       GPIO����                                       */
/*                                                                                      */
/****************************************************************************************/

/*======================================================================================*/

/*
*�ⲿ�ִ���ο�������ԭ��
*ԭ��������Cortex�ں˵�λ���������ܣ�ʵ��GPIO�ĸ�Ч��/д
*���в���ʹ�ú�ʵ�֣���߲����ٶ�
*ϸ�ڲ���׸����������ʹ�÷���
*
*
*���F4/F1ϵ�У�
*1.GPIO������/��(GPIO_Write())
*����GPIO_Write(GPIOA_6)=1;����佫PA6����
*����GPIO_Write(GPIOI_15)=0;����佫PI15����
*
*2.GPIO�����ȡ(GPIO_Read())
*����GPIO_Read(GPIOB_0);����䷵��PB0�ϵ�����ֵ
*
*3.��ȡIO����ĳ���˿ڵ�ƫ��(GPIO_Get_Pin_Addr())
*����GPIO_Get_Pin_Addr(GPIOB_3);����䷵��:1<<3
*����GPIO_Get_Pin_Addr(GPIOA_12);����䷵��:1<<12
*
*4.��ȡIO����ĳ���˿ڵ����(GPIO_Get_Pin_Num())
*����GPIO_Get_Pin_Num(GPIOA_3);����䷵��:3
*����GPIO_Get_Pin_Num(GPIOA_12);����䷵��:12
*
*
*
*���F7ϵ�У�
*1.GPIO������/��(GPIO_Write())
*����GPIO_Write(GPIOA_6,1);����佫PA6����
*����GPIO_Write(GPIOI_15,0);����佫PI15����
*
*2.GPIO�����ȡ(GPIO_Read())
*����GPIO_Read(GPIOB_0);����䷵��PB0�ϵ�����ֵ
*
*3.��ȡIO����ĳ���˿ڵ�ƫ��(GPIO_Get_Pin_Addr())
*����GPIO_Get_Pin_Addr(GPIOB_3);����䷵��:1<<3
*����GPIO_Get_Pin_Addr(GPIOA_12);����䷵��:1<<12
*/







//////////////////////////////////////////////////////////////////////////////////


//bit0~bit15��1<<Pinx
//bit16~bit19��GPIOA=0,GPIOB=1,GPIOC=2,...
//bit20~bit23��PIN0_ADDR=0,PIN1_ADDR=1,PIN3_ADDR=3,...

//GPIO���ű�Ŷ���
typedef enum
{
    PIN0_ADDR=1<<0,
    PIN1_ADDR=1<<1,
    PIN2_ADDR=1<<2,
    PIN3_ADDR=1<<3,
    PIN4_ADDR=1<<4,
    PIN5_ADDR=1<<5,
    PIN6_ADDR=1<<6,
    PIN7_ADDR=1<<7,
    PIN8_ADDR=1<<8,
    PIN9_ADDR=1<<9,
    PIN10_ADDR=1<<10,
    PIN11_ADDR=1<<11,
    PIN12_ADDR=1<<12,
    PIN13_ADDR=1<<13,
    PIN14_ADDR=1<<14,
    PIN15_ADDR=1<<15
} pin_type;

typedef enum
{
    GPIO_GROUPA=0<<16,
    GPIO_GROUPB=1<<16,
    GPIO_GROUPC=2<<16,
    GPIO_GROUPD=3<<16,
    GPIO_GROUPE=4<<16,
    GPIO_GROUPF=5<<16,
    GPIO_GROUPG=6<<16,
    GPIO_GROUPH=7<<16,
    GPIO_GROUPI=8<<16
} gpio_group_type;

typedef enum
{
    PIN0_NUM=0<<20,
    PIN1_NUM=1<<20,
    PIN2_NUM=2<<20,
    PIN3_NUM=3<<20,
    PIN4_NUM=4<<20,
    PIN5_NUM=5<<20,
    PIN6_NUM=6<<20,
    PIN7_NUM=7<<20,
    PIN8_NUM=8<<20,
    PIN9_NUM=9<<20,
    PIN10_NUM=10<<20,
    PIN11_NUM=11<<20,
    PIN12_NUM=12<<20,
    PIN13_NUM=13<<20,
    PIN14_NUM=14<<20,
    PIN15_NUM=15<<20
} pin_num_type;

typedef enum
{
    GPIOA_0=PIN0_ADDR+PIN0_NUM+GPIO_GROUPA,
    GPIOA_1=PIN1_ADDR+PIN1_NUM+GPIO_GROUPA,
    GPIOA_2=PIN2_ADDR+PIN2_NUM+GPIO_GROUPA,
    GPIOA_3=PIN3_ADDR+PIN3_NUM+GPIO_GROUPA,
    GPIOA_4=PIN4_ADDR+PIN4_NUM+GPIO_GROUPA,
    GPIOA_5=PIN5_ADDR+PIN5_NUM+GPIO_GROUPA,
    GPIOA_6=PIN6_ADDR+PIN6_NUM+GPIO_GROUPA,
    GPIOA_7=PIN7_ADDR+PIN7_NUM+GPIO_GROUPA,
    GPIOA_8=PIN8_ADDR+PIN8_NUM+GPIO_GROUPA,
    GPIOA_9=PIN9_ADDR+PIN9_NUM+GPIO_GROUPA,
    GPIOA_10=PIN10_ADDR+PIN10_NUM+GPIO_GROUPA,
    GPIOA_11=PIN11_ADDR+PIN11_NUM+GPIO_GROUPA,
    GPIOA_12=PIN12_ADDR+PIN12_NUM+GPIO_GROUPA,
    GPIOA_13=PIN13_ADDR+PIN13_NUM+GPIO_GROUPA,
    GPIOA_14=PIN14_ADDR+PIN14_NUM+GPIO_GROUPA,
    GPIOA_15=PIN15_ADDR+PIN15_NUM+GPIO_GROUPA,

    GPIOB_0=PIN0_ADDR+PIN0_NUM+GPIO_GROUPB,
    GPIOB_1=PIN1_ADDR+PIN1_NUM+GPIO_GROUPB,
    GPIOB_2=PIN2_ADDR+PIN2_NUM+GPIO_GROUPB,
    GPIOB_3=PIN3_ADDR+PIN3_NUM+GPIO_GROUPB,
    GPIOB_4=PIN4_ADDR+PIN4_NUM+GPIO_GROUPB,
    GPIOB_5=PIN5_ADDR+PIN5_NUM+GPIO_GROUPB,
    GPIOB_6=PIN6_ADDR+PIN6_NUM+GPIO_GROUPB,
    GPIOB_7=PIN7_ADDR+PIN7_NUM+GPIO_GROUPB,
    GPIOB_8=PIN8_ADDR+PIN8_NUM+GPIO_GROUPB,
    GPIOB_9=PIN9_ADDR+PIN9_NUM+GPIO_GROUPB,
    GPIOB_10=PIN10_ADDR+PIN10_NUM+GPIO_GROUPB,
    GPIOB_11=PIN11_ADDR+PIN11_NUM+GPIO_GROUPB,
    GPIOB_12=PIN12_ADDR+PIN12_NUM+GPIO_GROUPB,
    GPIOB_13=PIN13_ADDR+PIN13_NUM+GPIO_GROUPB,
    GPIOB_14=PIN14_ADDR+PIN14_NUM+GPIO_GROUPB,
    GPIOB_15=PIN15_ADDR+PIN15_NUM+GPIO_GROUPB,

    GPIOC_0=PIN0_ADDR+PIN0_NUM+GPIO_GROUPC,
    GPIOC_1=PIN1_ADDR+PIN1_NUM+GPIO_GROUPC,
    GPIOC_2=PIN2_ADDR+PIN2_NUM+GPIO_GROUPC,
    GPIOC_3=PIN3_ADDR+PIN3_NUM+GPIO_GROUPC,
    GPIOC_4=PIN4_ADDR+PIN4_NUM+GPIO_GROUPC,
    GPIOC_5=PIN5_ADDR+PIN5_NUM+GPIO_GROUPC,
    GPIOC_6=PIN6_ADDR+PIN6_NUM+GPIO_GROUPC,
    GPIOC_7=PIN7_ADDR+PIN7_NUM+GPIO_GROUPC,
    GPIOC_8=PIN8_ADDR+PIN8_NUM+GPIO_GROUPC,
    GPIOC_9=PIN9_ADDR+PIN9_NUM+GPIO_GROUPC,
    GPIOC_10=PIN10_ADDR+PIN10_NUM+GPIO_GROUPC,
    GPIOC_11=PIN11_ADDR+PIN11_NUM+GPIO_GROUPC,
    GPIOC_12=PIN12_ADDR+PIN12_NUM+GPIO_GROUPC,
    GPIOC_13=PIN13_ADDR+PIN13_NUM+GPIO_GROUPC,
    GPIOC_14=PIN14_ADDR+PIN14_NUM+GPIO_GROUPC,
    GPIOC_15=PIN15_ADDR+PIN15_NUM+GPIO_GROUPC,

    GPIOD_0=PIN0_ADDR+PIN0_NUM+GPIO_GROUPD,
    GPIOD_1=PIN1_ADDR+PIN1_NUM+GPIO_GROUPD,
    GPIOD_2=PIN2_ADDR+PIN2_NUM+GPIO_GROUPD,
    GPIOD_3=PIN3_ADDR+PIN3_NUM+GPIO_GROUPD,
    GPIOD_4=PIN4_ADDR+PIN4_NUM+GPIO_GROUPD,
    GPIOD_5=PIN5_ADDR+PIN5_NUM+GPIO_GROUPD,
    GPIOD_6=PIN6_ADDR+PIN6_NUM+GPIO_GROUPD,
    GPIOD_7=PIN7_ADDR+PIN7_NUM+GPIO_GROUPD,
    GPIOD_8=PIN8_ADDR+PIN8_NUM+GPIO_GROUPD,
    GPIOD_9=PIN9_ADDR+PIN9_NUM+GPIO_GROUPD,
    GPIOD_10=PIN10_ADDR+PIN10_NUM+GPIO_GROUPD,
    GPIOD_11=PIN11_ADDR+PIN11_NUM+GPIO_GROUPD,
    GPIOD_12=PIN12_ADDR+PIN12_NUM+GPIO_GROUPD,
    GPIOD_13=PIN13_ADDR+PIN13_NUM+GPIO_GROUPD,
    GPIOD_14=PIN14_ADDR+PIN14_NUM+GPIO_GROUPD,
    GPIOD_15=PIN15_ADDR+PIN15_NUM+GPIO_GROUPD,

    GPIOE_0=PIN0_ADDR+PIN0_NUM+GPIO_GROUPE,
    GPIOE_1=PIN1_ADDR+PIN1_NUM+GPIO_GROUPE,
    GPIOE_2=PIN2_ADDR+PIN2_NUM+GPIO_GROUPE,
    GPIOE_3=PIN3_ADDR+PIN3_NUM+GPIO_GROUPE,
    GPIOE_4=PIN4_ADDR+PIN4_NUM+GPIO_GROUPE,
    GPIOE_5=PIN5_ADDR+PIN5_NUM+GPIO_GROUPE,
    GPIOE_6=PIN6_ADDR+PIN6_NUM+GPIO_GROUPE,
    GPIOE_7=PIN7_ADDR+PIN7_NUM+GPIO_GROUPE,
    GPIOE_8=PIN8_ADDR+PIN8_NUM+GPIO_GROUPE,
    GPIOE_9=PIN9_ADDR+PIN9_NUM+GPIO_GROUPE,
    GPIOE_10=PIN10_ADDR+PIN10_NUM+GPIO_GROUPE,
    GPIOE_11=PIN11_ADDR+PIN11_NUM+GPIO_GROUPE,
    GPIOE_12=PIN12_ADDR+PIN12_NUM+GPIO_GROUPE,
    GPIOE_13=PIN13_ADDR+PIN13_NUM+GPIO_GROUPE,
    GPIOE_14=PIN14_ADDR+PIN14_NUM+GPIO_GROUPE,
    GPIOE_15=PIN15_ADDR+PIN15_NUM+GPIO_GROUPE,

    GPIOF_0=PIN0_ADDR+PIN0_NUM+GPIO_GROUPF,
    GPIOF_1=PIN1_ADDR+PIN1_NUM+GPIO_GROUPF,
    GPIOF_2=PIN2_ADDR+PIN2_NUM+GPIO_GROUPF,
    GPIOF_3=PIN3_ADDR+PIN3_NUM+GPIO_GROUPF,
    GPIOF_4=PIN4_ADDR+PIN4_NUM+GPIO_GROUPF,
    GPIOF_5=PIN5_ADDR+PIN5_NUM+GPIO_GROUPF,
    GPIOF_6=PIN6_ADDR+PIN6_NUM+GPIO_GROUPF,
    GPIOF_7=PIN7_ADDR+PIN7_NUM+GPIO_GROUPF,
    GPIOF_8=PIN8_ADDR+PIN8_NUM+GPIO_GROUPF,
    GPIOF_9=PIN9_ADDR+PIN9_NUM+GPIO_GROUPF,
    GPIOF_10=PIN10_ADDR+PIN10_NUM+GPIO_GROUPF,
    GPIOF_11=PIN11_ADDR+PIN11_NUM+GPIO_GROUPF,
    GPIOF_12=PIN12_ADDR+PIN12_NUM+GPIO_GROUPF,
    GPIOF_13=PIN13_ADDR+PIN13_NUM+GPIO_GROUPF,
    GPIOF_14=PIN14_ADDR+PIN14_NUM+GPIO_GROUPF,
    GPIOF_15=PIN15_ADDR+PIN15_NUM+GPIO_GROUPF,

    GPIOG_0=PIN0_ADDR+PIN0_NUM+GPIO_GROUPG,
    GPIOG_1=PIN1_ADDR+PIN1_NUM+GPIO_GROUPG,
    GPIOG_2=PIN2_ADDR+PIN2_NUM+GPIO_GROUPG,
    GPIOG_3=PIN3_ADDR+PIN3_NUM+GPIO_GROUPG,
    GPIOG_4=PIN4_ADDR+PIN4_NUM+GPIO_GROUPG,
    GPIOG_5=PIN5_ADDR+PIN5_NUM+GPIO_GROUPG,
    GPIOG_6=PIN6_ADDR+PIN6_NUM+GPIO_GROUPG,
    GPIOG_7=PIN7_ADDR+PIN7_NUM+GPIO_GROUPG,
    GPIOG_8=PIN8_ADDR+PIN8_NUM+GPIO_GROUPG,
    GPIOG_9=PIN9_ADDR+PIN9_NUM+GPIO_GROUPG,
    GPIOG_10=PIN10_ADDR+PIN10_NUM+GPIO_GROUPG,
    GPIOG_11=PIN11_ADDR+PIN11_NUM+GPIO_GROUPG,
    GPIOG_12=PIN12_ADDR+PIN12_NUM+GPIO_GROUPG,
    GPIOG_13=PIN13_ADDR+PIN13_NUM+GPIO_GROUPG,
    GPIOG_14=PIN14_ADDR+PIN14_NUM+GPIO_GROUPG,
    GPIOG_15=PIN15_ADDR+PIN15_NUM+GPIO_GROUPG,

    GPIOH_0=PIN0_ADDR+PIN0_NUM+GPIO_GROUPH,
    GPIOH_1=PIN1_ADDR+PIN1_NUM+GPIO_GROUPH,
    GPIOH_2=PIN2_ADDR+PIN2_NUM+GPIO_GROUPH,
    GPIOH_3=PIN3_ADDR+PIN3_NUM+GPIO_GROUPH,
    GPIOH_4=PIN4_ADDR+PIN4_NUM+GPIO_GROUPH,
    GPIOH_5=PIN5_ADDR+PIN5_NUM+GPIO_GROUPH,
    GPIOH_6=PIN6_ADDR+PIN6_NUM+GPIO_GROUPH,
    GPIOH_7=PIN7_ADDR+PIN7_NUM+GPIO_GROUPH,
    GPIOH_8=PIN8_ADDR+PIN8_NUM+GPIO_GROUPH,
    GPIOH_9=PIN9_ADDR+PIN9_NUM+GPIO_GROUPH,
    GPIOH_10=PIN10_ADDR+PIN10_NUM+GPIO_GROUPH,
    GPIOH_11=PIN11_ADDR+PIN11_NUM+GPIO_GROUPH,
    GPIOH_12=PIN12_ADDR+PIN12_NUM+GPIO_GROUPH,
    GPIOH_13=PIN13_ADDR+PIN13_NUM+GPIO_GROUPH,
    GPIOH_14=PIN14_ADDR+PIN14_NUM+GPIO_GROUPH,
    GPIOH_15=PIN15_ADDR+PIN15_NUM+GPIO_GROUPH,

    GPIOI_0=PIN0_ADDR+PIN0_NUM+GPIO_GROUPI,
    GPIOI_1=PIN1_ADDR+PIN1_NUM+GPIO_GROUPI,
    GPIOI_2=PIN2_ADDR+PIN2_NUM+GPIO_GROUPI,
    GPIOI_3=PIN3_ADDR+PIN3_NUM+GPIO_GROUPI,
    GPIOI_4=PIN4_ADDR+PIN4_NUM+GPIO_GROUPI,
    GPIOI_5=PIN5_ADDR+PIN5_NUM+GPIO_GROUPI,
    GPIOI_6=PIN6_ADDR+PIN6_NUM+GPIO_GROUPI,
    GPIOI_7=PIN7_ADDR+PIN7_NUM+GPIO_GROUPI,
    GPIOI_8=PIN8_ADDR+PIN8_NUM+GPIO_GROUPI,
    GPIOI_9=PIN9_ADDR+PIN9_NUM+GPIO_GROUPI,
    GPIOI_10=PIN10_ADDR+PIN10_NUM+GPIO_GROUPI,
    GPIOI_11=PIN11_ADDR+PIN11_NUM+GPIO_GROUPI,
    GPIOI_12=PIN12_ADDR+PIN12_NUM+GPIO_GROUPI,
    GPIOI_13=PIN13_ADDR+PIN13_NUM+GPIO_GROUPI,
    GPIOI_14=PIN14_ADDR+PIN14_NUM+GPIO_GROUPI,
    GPIOI_15=PIN15_ADDR+PIN15_NUM+GPIO_GROUPI,

    GPIO_NONE
} gpio_type;

#define GPIO_Get_Pin_Num(x)		(x>>20)
#define _Get_GPIO_Num(x)		((x>>16)&0xf)

#define GPIO_Get_Pin_Addr(x)    (x&0xffff)
#define _Get_GPIO_Addr(x)	    ((GPIO_TypeDef*)((_Get_GPIO_Num(x)<<10)+GPIOA_BASE))




#if defined USE_STM32F4 || defined USE_STM32F1
//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).M4ͬM3����,ֻ�ǼĴ�����ַ����.
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) 	((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  		*((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)  MEM_ADDR(BITBAND(addr, bitnum))

//ODR��IDR��ַƫ����
#if defined USE_STM32F4
#define ODR_OFFSET 20
#define IDR_OFFSET 16
#elif defined USE_STM32F1
#define ODR_OFFSET 12
#define IDR_OFFSET 8
#endif

#define _GPIO_Write(x)		BIT_ADDR(((uint32_t)_Get_GPIO_Addr(x)+ODR_OFFSET),GPIO_Get_Pin_Num(x))
#define GPIO_Read(x)		BIT_ADDR(((uint32_t)_Get_GPIO_Addr(x)+IDR_OFFSET),GPIO_Get_Pin_Num(x))

#define GPIO_Write(x,y)     _GPIO_Write(x)=y

#define GPIO_Pin_Set(x)      _GPIO_Write(x)=1
#define GPIO_Pin_Reset(x)    _GPIO_Write(x)=0



#endif

#if defined USE_STM32F7 || defined USE_STM32H7

#define BSRR_OFFSET         0x18
#define IDR_OFFSET          0x10

//x��GPIO�˿ڣ�y��Ҫд���ֵ��0/1��
#define GPIO_Write(x,y)      *(((uint16_t*)((uint32_t)_Get_GPIO_Addr(x)+BSRR_OFFSET))+((~(y))&1))|=GPIO_Get_Pin_Addr(x)
#define GPIO_Read(x)         (((*((uint16_t*)((uint32_t)_Get_GPIO_Addr(x)+IDR_OFFSET)))>>GPIO_Get_Pin_Num(x))&1)

#define GPIO_Pin_Set(x)      GPIO_Write(x,1)
#define GPIO_Pin_Reset(x)    GPIO_Write(x,0)

#endif
/*=========================================END==========================================*/










/****************************************************************************************/
/*                                                                                      */
/*                                     ϵͳ��ʱ��                                       */
/*                                                                                      */
/****************************************************************************************/

/*======================================================================================*/

/*
*ϵͳ��ʱ����һ�����õĶ�ʱ����Ϊ����ϵͳ�ṩͨ�õġ��򵥵ġ���׼�ĵ���ʱ����ʱ����
*�κ�һ����Ĵ��붼����ʹ�øö�ʱ�������Ҹö�ʱ�������ڲ�ͬ�Ŀ��б����ã�������Ϊÿ��������������һ�����趨ʱ���ˣ�
*Ĭ������¸ö�ʱ����SysTick��ʱ�����Ƽ����������û�Ҳ����ָ��Ϊ������ʱ��
*��ϵͳ��ʱ����ָ��ΪSysTick��ʱ��ʱ���û�����ҪΪ���д�κ��������룬������ֱ��ʹ��
*����Ҫע�ⲻͬ������SysTick��ʱ��Ƶ�ʿ��ܲ�ͬ����������ҪΪϵͳ��ʱ���ṩ��ȷ��ʱ��Ƶ��
*����ᵼ�¶�ʱʱ�䲻׼
*
*����ʱ������ʾ��
*
*SystemTimer_Timing_Ready(1000);   //ϵͳ��ʱ��׼������ʱʱ��Ϊ��x(us)
*SystemTimer_Timing_Begin();    //��ʼ����ʱ
*for (i=0;i<10;i++)
*{
*   Process();                     //ִ��һЩ����
*   while (SystemTimer_Timing_Check()==0);  //�ȴ�����ʱ����
*}
*
*ִ���������Ľ���ǣ�Process()��ִ����10�Σ�����ÿ1000us��ִ��һ��
*
*����ʱ׼�������û�е��ÿ�ʼ����ʱ��������Ӧ��ȡ������ʱ��
*SystemTimer_Timing_Ready(1000);   //ϵͳ��ʱ��׼������ʱʱ��Ϊ��x(us)
*SystemTimer_Timing_Cancel();    //ȡ������ʱ
*
*
*
*/








//���ʹ��ϵͳ��ʱ��
#if SYSTEM_TIMER!=0

void SystemTimer_Init(void);

//us����ʱ
void SystemTimer_Delay_Us(uint32_t time);

//ms����ʱ
void SystemTimer_Delay_Ms(uint32_t time);

//s����ʱ
void SystemTimer_Delay_S(uint32_t time);

//���ʹ��SysTick��ʱ��
#if SYSTEM_TIMER==1

//��ʼ����ʱ
#define SystemTimer_Timing_Begin()          SysTick->CTRL|=1

//��鵹��ʱ������־λ
#define SystemTimer_Timing_Check()          ((SysTick->CTRL>>16)&1)

//ȡ������ʱ
#define SystemTimer_Timing_Cancel()         SysTick->CTRL|=1

//׼������ʱ
void SystemTimer_Timing_Ready(float time_us);

#define delay_ms(x)                         SystemTimer_Delay_Ms(x)
#define delay_us(x)                         SystemTimer_Delay_Us(x)

#elif SYSTEM_TIMER==2

void SystemTimer_Timing_Ready(uint32_t time_us);

void SystemTimer_Reset();

void SystemTimer_Timing_Begin();

uint8_t SystemTimer_Timing_Check();

void SystemTimer_Timing_End();

void SystemTimer_Reset(void);

#endif

#endif

/*===========================================END========================================*/





#endif