#include "Framework.h"

#if SYSTEM_TIMER==1

#define SYSTICK_1US_VALUE   (SYSTEM_TIMER_CLOCK/1000000.0f)
#define SYSTICK_MAX_US      (16777216/SYSTICK_1US_VALUE-1)

#define SYSTICK_1MS_VALUE   (SYSTEM_TIMER_CLOCK/1000.0f)
#define SYSTICK_MAX_MS      (16777216/SYSTICK_1MS_VALUE)

#define SystemTimer_Reset()                 SysTick->CTRL&=~1; \
                                            SysTick->VAL=0

#define SystemTimer_Start()                 SysTick->CTRL|=1

#define SystemTimer_Get_Time(start,now)     now<start?start-now:start+now-0xffffff


void SystemTimer_Init(void)
{
    SysTick->LOAD=0xffffff;
    SysTick->CTRL|=1;
}

void SystemTimer_Delay_Us(uint32_t time)
{
    uint32_t ticks;
    uint32_t told,tnow,tcnt=0;
    uint32_t reload=SysTick->LOAD;			//LOAD��ֵ
    ticks=time*SYSTICK_1US_VALUE; 			//��Ҫ�Ľ�����
    SystemTimer_Start();
    told=SysTick->VAL;        				//�ս���ʱ�ļ�����ֵ
    while(1)
    {
        tnow=SysTick->VAL;
        if(tnow!=told)
        {
            if(tnow<told)
                tcnt+=told-tnow;	//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
            else
                tcnt+=reload-tnow+told;
            told=tnow;
            if(tcnt>=ticks)
                break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
        }
    }
}

void SystemTimer_Delay_Ms(uint32_t time)
{
    uint32_t i;
    for (i=0;i<time;i++)
        SystemTimer_Delay_Us(1000);
}

void SystemTimer_Delay_S(uint32_t time)
{
    SystemTimer_Delay_Ms(time*1000);
}

void SystemTimer_Timing_Ready(float time_us)
{
    SystemTimer_Reset();
    SysTick->LOAD=SYSTICK_1US_VALUE*time_us;
    SysTick->VAL=0;
}

#elif SYSTEM_TIMER==2

#endif