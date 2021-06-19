/****************************************************************
LCD��غ���
****************************************************************/

#include "lcd_qhj.h"
#include "touch.h"

/*=============================================��������=================================================================*/
void Method_LCD_Init(lcd* device);
void Method_LCD_Show_Init(struct lcd_class* device);
void Method_LCD_Run       (struct lcd_class* device);
void Method_LCD_Add_Page(lcd* device, lcd_page* page);
void Method_LCD_Switch_Page(lcd* device, lcd_page* page);
/*==============================================��������================================================================*/
void Method_LCD_Init(lcd* device){
    /* USER CODE BEGIN */
    TFTLCD_Init();
    TP_Init();
    /* USER CODE END */
}

void Method_LCD_Run(struct lcd_class* device){
    /* USER CODE BEGIN */
    if(device->now_page == NULL){
        return;
    }
    if(device->now_page->UpdateFlag == 1){
        device->now_page->UpdateFlag = 0;
        device->Show_Init(device);
    }

    device->now_page->Refresh(device->now_page);            // ��ˢ�½���
    device->now_page->Touch_Scan(device->now_page);         // ����ɨ��
    device->now_page->Refresh_Button(device->now_page);     // ˢ�°�������
    device->now_page->button_head->LastPress = device->now_page->button_head->NowPress;
    if (device->now_page->button_head->ButtonUp){
        device->now_page->Touch_Function(device->now_page);         // ִ�а����Ĳ���
        device->now_page->button_head->ButtonUp = 0;
    }
    /* USER CODE END */
}

void Method_LCD_Show_Init(struct lcd_class* device){
    /* USER CODE BEGIN */
    LCD_Clear(device->now_page->back_color);
    device->now_page->Show_Init(device->now_page);
    device->now_page->Button_Show_Init(device->now_page);
    /* USER CODE END */
}

void Method_LCD_Refresh_Button(struct lcd_class* device){
    /* USER CODE BEGIN */
    device->now_page->Refresh_Button(device->now_page);
    /* USER CODE END */
}
/***********************************************************************************************************************/

void Method_LCD_Add_Page(lcd* device, lcd_page* page){
    page_node *new_page = (page_node*)malloc(sizeof(page_node));     //  �����µ�button�ڵ�
    new_page->page = page;
    new_page->next = NULL;

    if(device->page_head->next != NULL){                     // ���ͷָ���next��Ϊ�գ������button����
        page_node* page_pn = device->page_head->next;
        for(int i = 1; i < device->page_head->length; i++){
            page_pn = page_pn->next;
        }
        page_pn->next = new_page;
    }
    else{
        device->page_head->next = new_page;
    }
    device->page_head->length += 1;
    if(device->now_page == NULL){       // ���Ŀǰ��page�ǿյģ�ֱ�ӽ���ӵ�ҳ����ֵ
        device->now_page = page;
    }
//    printf("LCD�ɹ����һ��Page!\r\n");
}

void Method_LCD_Switch_Page(lcd* device, lcd_page* page){
    device->now_page = page;
    device->now_page->UpdateFlag = 1;
}

/*====================================================================================================================*/
void LCD_Prepare(lcd* device){
    device->page_head           = (phead*)malloc(sizeof(phead));
    device->page_head->next     = NULL;
    device->page_head->length   = 0;
    device->now_page            = NULL;

    device->Init                = Method_LCD_Init;
    device->Add_Page            = Method_LCD_Add_Page;
    device->Show_Init           = Method_LCD_Show_Init;
    device->Run                 = Method_LCD_Run;
    device->Refresh_Button      = Method_LCD_Refresh_Button;
    device->Switch_Page         = Method_LCD_Switch_Page;
}

