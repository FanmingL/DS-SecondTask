#include "main.h"


void BSP_Init(void)	
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIM2_Configuration();
	TIM6_Configuration();
	LED_Configuration();
	LCD_Init();
	key_init();
	PWM_Configuration();
	Para_ResetToFactorySetup();
	MotorEnable();
	BRUSH_COLOR=RED;
	BACK_COLOR=WHITE;
	LCD_Clear(BLACK);
	GPIO_Configuration();
	Encoder_Configuration();
	Usart1_Init(115200);
	Adc_Init();
	Encoder_Start();
	TIM6_Start();
}


