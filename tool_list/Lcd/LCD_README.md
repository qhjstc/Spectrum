# STM32配合Stm32Cube软件库
可以配合STM32多种芯片型号使用，目前支持（STM32 F4， STM32 F7）

## Description
主要是介绍LCD的使用。

## Usage
###1、Variable介绍
variable中的函数需要在`main.c`中调用，
- `variable.c`
  - 需要调用的函数:
    - Variable_Init();
      - 里面放着函数的初始化，
  

###2、LCD介绍
<div> <font color="#483d8b">LCD可以提供显示，触摸功能，需要申请变量lcd。</font></div>

- `lcd_qhj.c`
  - 主要用到四个函数(这几个函数都不需要自己更改):
    
    | 函数      | 参数| 描述|是否需要修改|
    |----------|-----|------|------|
    |Init(struct lcd_class* device)|device:调用的lcd|函数可以由用户自己修改，函数中需要放入LCD外设初始化，触摸初始化。|可能需要|
    |Run(struct lcd_class* device)|device:调用的lcd|函数可以由用户自己修改，LCD运行函数里面放着一个LCD刷新屏幕，扫描按键，实施按键函数等操作。|可能需要|
    |Add_Page(struct lcd_class* device, lcd_page* page)|device:调用的lcd, page:添加的page|给LCD添加一个Page|不需要|
    |Show_Init(struct lcd_class* device)|device:调用的lcd|界面显示初始化，已经写好了。|不需要|
    |Refresh_Button(struct lcd_class* device)|device:调用的lcd|界面按键刷新按键，已经写好了。|不需要|

- `lcd_page.c`
    - 需要自己添加的函数
      
      | 函数| 参数|功能|是否需要修改|
      |----------|-----|-------|-----|
      |Show_Init(struct lcd_page_class* device)|device:调用的page|Page画面的初始化，需要用户自己写，然后添加。|需要|
      |Refresh(struct lcd_page_class* device)|device:调用的page|Page画面的刷新，需要用户自己写，然后添加。|需要|
        
    - 关于界面操作的函数 
    
        - 说明：<font color="#ff7f50"> 不同外设需要修改里面的部分函数,测试过正点原子的RGB屏和TFT屏都能使用(只要修改初始化函数就可以了)。
               </font>
          
      | 函数| 参数|描述|是否需要修改|
      |----------|-----|-------|-----|
      |Change_Point_Color(<font color="##3CB371">struct lcd_page_class* device, uint32_t color</font>)|device:调用的page, color:颜色|修改Page画笔的颜色|可能需要|
      |Change_Back_Color(<font color="##3CB371">struct lcd_page_class* device, uint32_t color</font>)|device:调用的page, color:颜色|修改Page背景的颜色|可能需要|
      |Change_Display_direction(struct lcd_page_class* device, uint32_t dir)|device:调用的page, dir:显示方向（0,竖屏；1,横屏）|修改画面显示的方向|可能需要|
      |Add_Line(<font color="##3CB371">struct lcd_page_class* device,uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color</font>)|device:调用的page|添加一条线|可能需要|
      |Add_Rectangle(<font color="##3CB371">struct lcd_page_class* device, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color</font>)|device:调用的page|添加一个矩形窗|可能需要|
      |Add_String(<font color="##3CB371">struct lcd_page_class* device, u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p, uint32_t color</font>)|device:调用的page|添加一个字符串|可能需要|

    - 关于控件的函数

        | 函数| 参数|描述|是否需要修改|
          |----------|-----|-------|-----|
        |Add_Button(<font color="##3CB371">struct lcd_page_class* device, lcd_button* button, void(*function)()</font>)|device:调用的page, button:添加的button|Page添加一个Button |不需要|
        |Delete_Button(<font color="##3CB371">struct lcd_page_class* device, lcd_button* button</font>)|device:调用的page, button:删除的button|Page删除一个Button|不需要|
    

    
