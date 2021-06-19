//
// Created by QHJSTC on 2021/4/25.
//

#ifndef BASEPROJECT_LED_H
#define BASEPROJECT_LED_H

#include "Framework.h"
#include "lcd.h"

/*=====================================================================================================================*/
typedef struct led_class{
    /*===============================��Ա����====================================*/
    GPIO_TypeDef*       Port;         // GPIO��
    uint16_t            Pin;          // Pin����

    /*===============================��Ա����====================================*/
    void (*On)      (struct led_class* device);
    void (*Off)     (struct led_class* device);
    void (*Toggle)  (struct led_class* device);
}led;

/*=====================================================================================================================*/
void New_LED(led *device, GPIO_TypeDef* Port, uint16_t Pin);


#endif //BASEPROJECT_LED_H

