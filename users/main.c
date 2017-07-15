#include "main.h"

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIM2_Configuration();
	LED_Configuration();
	LCD_Init();
	key_init();
	BRUSH_COLOR=RED;
	LCD_Clear(WHITE);
	while(1){
		LED_TOGGLE();
		LCD_Color_DrawPoint(x,y,RED);
		x++,y++;
		x = (x==240)?0:x;
		y = (y==320)?0:y;
		delay_ms(10);
	}
}
