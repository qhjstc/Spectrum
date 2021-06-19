#ifndef BASEPROJECT_LCD_PAGE_H
#define BASEPROJECT_LCD_PAGE_H

#include "Framework.h"
#include "lcd.h"
#include "touch.h"
/****************************************************�����ṹ��**********************************************************/
/* ���������ṹ�� */
typedef struct{
    uint16_t    sx;         // ���Ͻ�x����
    uint16_t    sy;         // ���Ͻ�y����
    uint16_t    width;      // ������
    uint16_t    height;     // ������
    uint32_t    color;      // ������ɫ

    uint16_t     size;       // ��ʾ�ֵĴ�С
    uint8_t     str[10];    // ������ʾ

    void        (*Function)         ();
}lcd_button;

/**************************************************��������**************************************************************/
//�ڵ�
typedef struct b_node{
    lcd_button*             button;  // 5�������±�1--5(0Ϊ��Ч�ж�)
    struct b_node*          next;
}button_node;

// ͷ���
typedef struct b_head{
    int             length;
    button_node*    next;
    // ��������
    uint16_t                NowPress;       // ��ǰ���µİ����±�
    uint16_t                LastPress;      // �ϴΰ��µİ����±�
    uint8_t                 ButtonUp;       // ��ǰ�����Ƿ��ɿ���1Ϊ�ɿ�
}bhead;

// ����
typedef struct canvas_class{
    uint32_t*           color;
    u16                 width;			//LCD ���
    u16                 height;			//LCD �߶�
}page_canvas;

/**********************************************************************************************************************/
/* ������ */
typedef struct lcd_page_class{
    bhead*                  button_head;
    uint32_t                point_color;    // ���ʵ���ɫ
    uint32_t                back_color;    // ��������ɫ
    uint8_t                 direction;      //direction:0,������1,����
    uint8_t                 UpdateFlag;     // ˢ����־
    page_canvas             canvas;

    /*====================================================================================*/
    void    (*Show_Init)                (struct lcd_page_class* device);
    void    (*Button_Show_Init)         (struct lcd_page_class* device);
    void    (*Refresh)                  (struct lcd_page_class* device);
    void    (*Refresh_Button)           (struct lcd_page_class* device);
    void    (*Touch_Function)           (struct lcd_page_class* device);
    void    (*Touch_Scan)               (struct lcd_page_class* device);
    void    (*Change_Point_Color)       (struct lcd_page_class* device, uint32_t color);
    void    (*Change_Back_Color)        (struct lcd_page_class* device, uint32_t color);
    void    (*Change_Display_Direction) (struct lcd_page_class* device, uint32_t dir);

    /*=====================================================================================*/
    void    (*Add_Line)                 (struct lcd_page_class* device,uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
    void    (*Add_Rectangle)            (struct lcd_page_class* device, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
    void    (*Add_String)               (struct lcd_page_class* device, u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p, uint32_t color);
    void    (*Fill)                     (struct lcd_page_class* device, u16 sx,u16 sy,u16 ex,u16 ey,u32 color);
    /*=====================================================================================*/
    void    (*Add_Button)               (struct lcd_page_class* device, lcd_button* button, void(*function)());
    void    (*Delete_Button)            (struct lcd_page_class* device, lcd_button* button);
}lcd_page;

void LCD_Page_Prepare(lcd_page* device,  uint16_t width, uint16_t height, void(*refresh)(struct lcd_page_class* device)
                                        , void(show)(struct lcd_page_class* device));


#endif //BASEPROJECT_LCD_PAGE_H
