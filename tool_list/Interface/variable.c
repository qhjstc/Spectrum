
#include "variable.h"
#include "spi.h"
#include "usart.h"
/*************************************************�������***************************************************************/
#define ADS1256_LENGTH  100
float ADS1256_Value[ADS1256_LENGTH] = {0};

/*************************************************�������***************************************************************/
// ����һ��lcd
lcd base_lcd;

// ����page
lcd_page spectrum_page;
lcd_page page2;

// ����button
lcd_button button1 = {700, 0, 100, 80, YELLOW,24,  "test"};
lcd_button button2 = {700, 80, 100, 80, YELLOW, 24, "test2"};
lcd_button button3 = {700,160, 100, 80, YELLOW, 24, "test3"};
lcd_button button4 = {700,240, 100, 80, YELLOW, 24, "test3"};
lcd_button button5 = {700,320, 100, 80, YELLOW, 24, "test3"};
lcd_button button6 = {700,400, 100, 80, YELLOW, 24, "test3"};

// ����һ��led
led led1;

// ����һ��adf4351
adf4351 adf4351_1;

// ����һ��ad1256
ads1256 ads1256_1;

/*==========================================��������====================================================================*/
/*******************************************LCD Page*******************************************************************/
void Spectrum_Page_Init_Show(struct lcd_page_class* device){
    // ��������ʼ�ĳ���
    /* USER CODE BEGIN */
    device->back_color = WHITE;
    POINT_COLOR = device->point_color;
    BACK_COLOR  = device->back_color;
    device->Change_Display_Direction(device, 1);            // ת����ʾ����

    device->Fill(device, 50, 50, 699, 430, BLACK);          // �����ʾ���ν���
//    device->Add_Rectangle(device, 50, 50, 600, 430, YELLOW);

    device->Add_Rectangle(device, 0, 0, 700, 50, BLUE);    // ��ӿ�ͼ����
    device->Add_Rectangle(device, 0, 50, 50, 430, BLUE);
    device->Add_Rectangle(device, 0, 430, 700, 479, BLUE);
    /* USER CODE END */
}

void Spectrum_Page_Refresh(struct lcd_page_class* device) {
    // ������Ҫ���еĽ���ˢ�³���
    /* USER CODE BEGIN */

    /* USER CODE END */
}

void Page2_Init_Show(struct lcd_page_class* device){
    // ��������ʼ�ĳ���
    /* USER CODE BEGIN */
    POINT_COLOR = device->point_color;
    BACK_COLOR  = device->back_color;
    device->Change_Display_Direction(device, 1);
    device->Fill(device, 50, 50, 600, 430, BLACK);
    device->Add_Rectangle(device, 50, 50, 600, 430, YELLOW);
    /* USER CODE END */
}

void Page2_Refresh(struct lcd_page_class* device) {
    // ������Ҫ���еĽ���ˢ�³���
    /* USER CODE BEGIN */

    /* USER CODE END */
}

/*************************************************Button***************************************************************/
void Button1_Function();
void Button1_Function(){
    // ����ý��水���Ĺ���
    /* USER CODE BEGIN */
    printf("�����˵�һ������\r\n");
    base_lcd.Switch_Page(&base_lcd, &page2);
    /* USER CODE END */
}

void Button2_Function();
void Button2_Function(){
    /* USER CODE BEGIN */
    printf("�����˵ڶ�������\r\n");
    /* USER CODE END */
}

void Button3_Function(){
    printf("�����˵���������\r\n");
//    base_lcd.
}

void Button4_Function(){
    printf("�����˵���������\r\n");
//    base_lcd.
}

void Button5_Function(){
    printf("�����˵���������\r\n");
//    base_lcd.
}

void Button6_Function(){
    printf("�����˵���������\r\n");
//    base_lcd.
}
/*************************************************��ʼ������*************************************************************/
void Variable_Init(){
    SystemTimer_Init();

    /********************LED***************************/
    New_LED(&led1, LED1_GPIO_Port, LED1_Pin);
    /**************************************************/

    /*******************LCD***************************/
    LCD_Prepare(&base_lcd);
    base_lcd.Init(&base_lcd);

    LCD_Page_Prepare(&spectrum_page,  lcddev.width, lcddev.height,Spectrum_Page_Refresh, Spectrum_Page_Init_Show);  // ��ʼ���µ�Page
    spectrum_page.Add_Button(&spectrum_page, &button1, Button1_Function);
    spectrum_page.Add_Button(&spectrum_page, &button2, Button2_Function);
    spectrum_page.Add_Button(&spectrum_page, &button3, Button3_Function);
    spectrum_page.Add_Button(&spectrum_page, &button4, Button4_Function);
    spectrum_page.Add_Button(&spectrum_page, &button5, Button5_Function);
    spectrum_page.Add_Button(&spectrum_page, &button6, Button6_Function);
    base_lcd.Add_Page(&base_lcd, &spectrum_page);

    LCD_Page_Prepare(&page2,  lcddev.width, lcddev.height,Page2_Refresh, Page2_Init_Show);
    base_lcd.Add_Page(&base_lcd, &page2);
    printf("��ʼ��LCD���!\r\n");
    /**************************************************/

    /*****************ADF4351**************************/
    ADF4351_Prepare(&adf4351_1, HARDWARE, 0, 0, 0, &hspi3,0,0, GPIOC_4, GPIOC_5);
    adf4351_1.Set_Output_Frequency(&adf4351_1, 250);

    /*************************************************/

    /*****************ADS1256************************/
    HAL_GPIO_WritePin(ADS1256_CS_GPIO_Port, ADS1256_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ADS1256_RST_GPIO_Port, ADS1256_RST_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ADS1256_SYNC_GPIO_Port, ADS1256_SYNC_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ADS1256_MOSI_GPIO_Port, ADS1256_MOSI_Pin, GPIO_PIN_RESET);
    delay_ms(50);
    ADS1256_Prepare(&ads1256_1, SOFTWARE, 0, 0, 0, 0, GPIOD_7, GPIOG_10, GPIOG_13);
    ads1256_1.Set_Input_Buffer_Status(&ads1256_1, BUFFER_DISABLE);
    ads1256_1.Set_Positive_Channel(&ads1256_1, ADS1256_CH0);
    ads1256_1.Set_Negative_Channel(&ads1256_1, ADS1256_CH1);
    ads1256_1.Set_PGA_Gain(&ads1256_1, ADS1256_PGA_1);
    ads1256_1.Set_Sample_Rate(&ads1256_1, ADS1256_SPS_25);
    /************************************************/

    delay_ms(500);
//    ads1256_1.Get_Data(&ads1256_1, 1000, ADS1256_Value, ADS1256_LENGTH, FLOAT_Format);
//    for(int i = 1; i < ADS1256_LENGTH; i++){
//        printf("ADS1256[%d] = %lf\r\n", i, ADS1256_Value[i]);
//    }
    printf("��ʼ���������!\r\n");
}


void Variable_Loop(){
    ads1256_1.Get_Data(&ads1256_1, 25, ADS1256_Value, ADS1256_LENGTH, FLOAT_Format);
    for(int i = 1; i < ADS1256_LENGTH; i++){
        printf("ADS1256[%d] = %lf\r\n", i, ADS1256_Value[i]);
    }
    delay_ms(500);
    delay_ms(500);
    base_lcd.Run(&base_lcd);
}



