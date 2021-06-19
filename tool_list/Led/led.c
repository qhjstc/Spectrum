//
// һ��Led�򵥵Ĺ��캯��
//

#include "led.h"

/*************��������*****************/
void Method_Led_On(led* device);
void Method_Led_Off(led* device);
void Method_Led_Toggle(led* device);

//void test(){
//    printf("hello");
//}

// ��Led
void Method_Led_On(led* device){
    HAL_GPIO_WritePin(device->Port, device->Pin, GPIO_PIN_SET);
}

// �ر�Led
void Method_Led_Off(led* device){
    HAL_GPIO_WritePin(device->Port, device->Pin, GPIO_PIN_RESET);
}

// Led��ת��ƽ
void Method_Led_Toggle(led* device){
    HAL_GPIO_TogglePin(device->Port, device->Pin);
}

/****************************************/
// ����һ���µ�LED��
void New_LED(led *device, GPIO_TypeDef* Port, uint16_t Pin){
    // ��ʼ��Led�ĳ�Ա����
    device->Port = Port;
    device->Pin = Pin;

    // ��ʼ��Led�ĺ���
    device->On = Method_Led_On;
    device->Off = Method_Led_Off;
    device->Toggle = Method_Led_Toggle;
}



