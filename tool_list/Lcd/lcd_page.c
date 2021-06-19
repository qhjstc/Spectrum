#include "lcd_page.h"
#include "string.h"

static uint8_t  Touch_Scan              ();

/* ����ɨ�� */
/* �����Ƿ��ɿ���tp_dev�ж���¼�����һ�εĴ������� */
static uint8_t Touch_Scan(){
    tp_dev.scan(0);  //ɨ�败����
    if ((tp_dev.sta & 0xC0) == TP_CATH_PRES)     //����������������һ�������ɿ�
    {
        tp_dev.sta &= ~(TP_CATH_PRES);  //��[�����������¼�]�ı�־���
        return 1;  // ���ظð������ɿ�
    }
    else
        return 0;  // ���ظü�δ�ɿ�����¼��ֵ
}

// ��ʾ����
void Show_Str_Mid(uint16_t sx, uint16_t sy, uint16_t lenx, uint16_t leny, uint8_t* str, uint16_t size){
    return;
//    u16 strlenthx=0;
//    u16 strlenthy=1;
//    if(*str>0x80){                              // �����ʾ�������ģ���ôleny*2
//        strlenthy = 2;
//    }
//    strlenthx=strlen((const char*)str);         // �ַ��ĳ���
//    strlenthx*=size/2;
//    strlenthy*=size/2;
//    if(strlenthx>lenx || strlenthx>leny){
//        Show_Str(x,y,lcddev.width,lcddev.height,str,size,1);
//    }
//    else{
//        strlenthx=(lenx-strlenthx)/2;
//        strlenthy=(leny-strlenthy)/2;
//        Show_Str(strlenthx+x,strlenthy+y,lcddev.width,lcddev.height,str,size,1);
//    }
}

/*=====================================================================================================================*/
void            Method_LCD_Page_Change_Point_Color              (struct lcd_page_class* device, uint32_t color);
void            Method_LCD_Page_Change_Back_Color               (struct lcd_page_class* device, uint32_t color);
void            Method_LCD_Page_Add_Button                      (struct lcd_page_class* device, lcd_button * button, void(*function)());
void            Method_LCD_Page_Button_Touch_Scan               (struct lcd_page_class* device);
void            Method_LCD_Page_Change_Display_Direction        (struct lcd_page_class* device, uint32_t dir);

void            Method_LCD_Page_Add_Line                        (struct lcd_page_class* device,uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
void            Method_LCD_Page_Add_Rectangle                   (struct lcd_page_class* device, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
void            Method_LCD_Page_Add_String                      (struct lcd_page_class* device, u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p, uint32_t color);
/*******************************************��ʾ����*********************************************************************/

void Method_LCD_Page_Add_Line(struct lcd_page_class* device,uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color){
    /* USER CODE BEGIN */
    POINT_COLOR = color;
    LCD_DrawLine(x1, y1, x2, y2);
    POINT_COLOR = device->point_color;
    /* USER CODE END */
}

void Method_LCD_Page_Add_Rectangle(struct lcd_page_class* device, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color){
    /* USER CODE BEGIN */
    POINT_COLOR = color;
    LCD_DrawRectangle(x1, y1, x2, y2);
    POINT_COLOR = device->point_color;
    /* USER CODE END */
}

void Method_LCD_Page_Add_String(struct lcd_page_class* device, u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p, uint32_t color){
    POINT_COLOR = color;
//    u8 x0=x;
//    width+=x;
//    height+=y;
//    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
//    {
//        if(x>=width){x=x0;y+=size;}
//        if(y>=height)break;//�˳�
//        LCD_ShowChar(x,y,*p,size,0);
//        x+=size/2;
//        p++;
//    }
    LCD_ShowString(x, y, width, height, size, p);
    POINT_COLOR = device->point_color;
}

void Method_LCD_Page_Fill(struct lcd_page_class* device, u16 sx,u16 sy,u16 ex,u16 ey,u32 color){
//    u16 i,j;
//    u16 xlen=0;
//    xlen=ex-sx+1;
//    for(i=sy;i<=ey;i++){
//        for(j=0;j<xlen;j++){
//            *(device->canvas.color + i*device->canvas.height + sx + j) = color;	//��ʾ��ɫ
//        }
////        printf("%d,%x\r\n",ey-sy+1,device->canvas.color + i*device->canvas.height + sx + j);
//    }
//    LCD_Refresh(sx, sy, ex, ey, device->canvas.color);
        LCD_Fill(sx, sy, ex, ey, color);
}

/**********************************************************************************************************************/
void    Method_LCD_Page_Button_Show_Init        (struct lcd_page_class* device);
void    Method_LCD_Page_Refresh_Button          (struct lcd_page_class* device);

void Method_LCD_Page_Button_Show_Init(struct lcd_page_class* device){
    button_node* button_pn;
    if(device->button_head->next == NULL){
        return;
    }
    button_pn = device->button_head->next;
    for (int i = 1; i <= device->button_head->length; i++){
        LCD_DrawRectangle(button_pn->button->sx, button_pn->button->sy, button_pn->button->sx + button_pn->button->width,
                          button_pn->button->sy + button_pn->button->height);
        LCD_Fill(button_pn->button->sx + 1, button_pn->button->sy + 1, button_pn->button->sx + button_pn->button->width - 1,
                 button_pn->button->sy + button_pn->button->height - 1, button_pn->button->color);
        button_pn = button_pn->next;
        Show_Str_Mid(button_pn->button->sx,button_pn->button->sy,button_pn->button->width, button_pn->button->height, button_pn->button->str, button_pn->button->size);
    }
}

void Method_LCD_Page_Refresh_Button(struct lcd_page_class* device){
    button_node* button_pn;
    if(device->button_head->next == NULL){
        return;
    }
    button_pn = device->button_head->next;
    if(device->button_head->NowPress != 0){             // ��ǰ������Чλ��
        for(int i = 1; i < device->button_head->NowPress; i++){
            button_pn = button_pn->next;
        }
        LCD_Fill(button_pn->button->sx + 1, button_pn->button->sy + 1, button_pn->button->sx + button_pn->button->width - 1,
                 button_pn->button->sy + button_pn->button->height - 1, LBBLUE);
    };
    if (device->button_head->LastPress != 0 && device->button_head->NowPress != device->button_head->LastPress){     // �ϴΰ�����Чλ���ҵ�ǰ�ƿ�
        for(int i = 1; i < device->button_head->LastPress; i++){
            button_pn = button_pn->next;
        }
        LCD_Fill(button_pn->button->sx + 1, button_pn->button->sy + 1, button_pn->button->sx + button_pn->button->width - 1,
                 button_pn->button->sy + button_pn->button->height - 1, button_pn->button->color);
    }
    POINT_COLOR = BLACK;
}

void Method_LCD_Page_Touch_Function(struct lcd_page_class* device){
    button_node* button_pn;
    if(device->button_head->next == NULL || device->button_head->NowPress == 0){
        return;
    }
    button_pn = device->button_head->next;
    for(int i = 1; i < device->button_head->NowPress; i++){
        button_pn = button_pn->next;
    }
    button_pn->button->Function();
}

void Method_LCD_Page_Change_Point_Color(struct lcd_page_class* device, uint32_t color){
    /* USER CODE BEGIN */
    device->point_color = color;
    POINT_COLOR = device->point_color;
    /* USER CODE END */
}

void Method_LCD_Page_Change_Back_Color(struct lcd_page_class*device, uint32_t color){
    device->back_color = color;
    BACK_COLOR = device->back_color;
}

void Method_LCD_Page_Change_Display_Direction(struct lcd_page_class* device, uint32_t dir){
    /* USER CODE BEGIN */
    device->direction = dir;
    LCD_Display_Dir(device->direction);
    tp_dev.touchtype|=lcddev.dir&0X01;//������������
    uint16_t temp = device->canvas.height;
    device->canvas.height = device->canvas.width;
    device->canvas.width = temp;
    /* USER CODE END */
}

/**********************************************************************************************************************/
void Method_LCD_Page_Add_Button(struct lcd_page_class* device, lcd_button* button, void(*function)()){
    button_node* new_button = (button_node*)malloc(sizeof(button_node));     //  �����µ�button�ڵ�
    button->Function   = function;
    new_button->button = button;
    new_button->next = NULL;

    if(device->button_head->next != NULL){                     // ���ͷָ���next��Ϊ�գ������button����
        button_node* button_pn = device->button_head->next;
        for(int i = 1; i < device->button_head->length; i++){
            button_pn = button_pn->next;
        }
        button_pn->next = new_button;
    }
    else{
        device->button_head->next = new_button;
    }
    device->button_head->length += 1;
//    printf("Page�ɹ����һ��Button!\r\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Method_LCD_Page_Delete_Button(struct lcd_page_class* device, lcd_button* button){
    if(device->button_head->next == NULL){
        return;
    }
    button_node* button_pn = device->button_head->next;
    for(int i = 1; i <= device->button_head->length-1; i++){
        if(button_pn->next->button == button){
            LCD_Fill(button->sx, button->sy, button->sx+button->width, button->sy+button->height, device->back_color);
            free(button_pn->next);
            if(button_pn->next != NULL) {
                button_pn->next = button_pn->next->next;
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* page button scan */
void Method_LCD_Page_Button_Touch_Scan(struct lcd_page_class* device){
    device->button_head->ButtonUp = Touch_Scan();
    if(device->button_head->next == NULL){
        return;
    }
    button_node* button_pn = device->button_head->next;
    for (int i = 1; i <= device->button_head->length; i++){
        if (tp_dev.x[0] >= button_pn->button->sx && tp_dev.x[0] <= button_pn->button->sx + button_pn->button->width)
        {
            if (tp_dev.y[0] >= button_pn->button->sy && tp_dev.y[0] <= button_pn->button->sy + button_pn->button->height)
            {
                device->button_head->NowPress = i;
                return;
            }
        }
        button_pn = button_pn->next;
    }
    device->button_head->NowPress = 0;
}

/*===============================================================================================================================*/
void LCD_Page_Prepare(lcd_page* device,  uint16_t width, uint16_t height, void(*refresh)(struct lcd_page_class* device)
                    , void(show)(struct lcd_page_class* device)){
    device->button_head                 = (bhead*)malloc(sizeof(bhead));
    device->button_head->next           = NULL;
    device->button_head->NowPress       = 0;
    device->button_head->length         = 0;
    device->button_head->LastPress      = 0;

    u8 sramx=0;
//    device->canvas.color                = mymalloc(sramx, 1024*1024);   // ����2k���ڴ�
    device->canvas.height               = 480;
    device->canvas.width                = 800;
    device->point_color                 = BLACK;
    device->back_color                  = WHITE;
    device->direction                   = 0;
    device->UpdateFlag                  = 1;

    device->Add_Button                  = Method_LCD_Page_Add_Button;
    device->Change_Display_Direction    = Method_LCD_Page_Change_Display_Direction;
    device->Button_Show_Init            = Method_LCD_Page_Button_Show_Init;
    device->Refresh_Button              = Method_LCD_Page_Refresh_Button;
    device->Touch_Function              = Method_LCD_Page_Touch_Function;
    device->Touch_Scan                  = Method_LCD_Page_Button_Touch_Scan;

    device->Add_Rectangle               = Method_LCD_Page_Add_Rectangle;
    device->Add_String                  = Method_LCD_Page_Add_String;
    device->Add_Line                    = Method_LCD_Page_Add_Line;
    device->Fill                        = Method_LCD_Page_Fill;

    device->Refresh                     = refresh;
    device->Show_Init                   = show;
//    printf("�ɹ�����һ��Page!\r\n");
}