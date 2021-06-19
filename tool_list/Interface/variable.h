

#ifndef BASEPROJECT_VARIABLE_H
#define BASEPROJECT_VARIABLE_H
#include "Framework.h"
#include "lcd_qhj.h"
#include "lcd_page.h"
#include "led.h"
#include "ADS1256.h"
#include "ADF4351.h"


extern lcd      base_lcd;
extern lcd_page page1;

extern led      led1;
extern adf4351  adf4351_1;

void Variable_Init(void);
void Variable_Loop(void);

#endif //BASEPROJECT_VARIABLE_H
