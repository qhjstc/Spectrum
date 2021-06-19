#ifndef BASEPROJECT_LCD_PAGE_H
#define BASEPROJECT_LCD_PAGE_H

#include "Framework.h"
#include "lcd.h"
#include "touch.h"
/****************************************************按键结构体**********************************************************/
/* 按键参数结构体 */
typedef struct{
    uint16_t    sx;         // 左上角x坐标
    uint16_t    sy;         // 左上角y坐标
    uint16_t    width;      // 按键宽
    uint16_t    height;     // 按键高
    uint32_t    color;      // 按键颜色

    uint16_t     size;       // 显示字的大小
    uint8_t     str[10];    // 文字显示

    void        (*Function)         ();
}lcd_button;

/**************************************************按键链表**************************************************************/
//节点
typedef struct b_node{
    lcd_button*             button;  // 5个按键下标1--5(0为无效判定)
    struct b_node*          next;
}button_node;

// 头结点
typedef struct b_head{
    int             length;
    button_node*    next;
    // 按键操作
    uint16_t                NowPress;       // 当前按下的按键下标
    uint16_t                LastPress;      // 上次按下的按键下标
    uint8_t                 ButtonUp;       // 当前按键是否松开，1为松开
}bhead;

// 画布
typedef struct canvas_class{
    uint32_t*           color;
    u16                 width;			//LCD 宽度
    u16                 height;			//LCD 高度
}page_canvas;

/**********************************************************************************************************************/
/* 主界面 */
typedef struct lcd_page_class{
    bhead*                  button_head;
    uint32_t                point_color;    // 画笔的颜色
    uint32_t                back_color;    // 背景的颜色
    uint8_t                 direction;      //direction:0,竖屏；1,横屏
    uint8_t                 UpdateFlag;     // 刷屏标志
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
