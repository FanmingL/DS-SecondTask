#ifndef TIMER_H_
#define TIMER_H_


void TIM2_Configuration(void);
#define Get_Time_Micros() (TIM2->CNT)

void delay_ms(u32 ms);
void delay_us(u32 us);







#endif
