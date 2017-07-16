#include "main.h"

int main()
{
	int speed_temp,circle_temp,deg_temp,pangle_temp,pangle_sp_temp;
	BSP_Init();
	while(1){

	GPIO_ToggleBits(GPIOB,GPIO_Pin_0);
	BRUSH_COLOR=WHITE;
	BACK_COLOR=BLACK;
	LCD_DisplayString(30,30,16,"Speed:");
	LCD_DisplayString(30,60,16,"circle:");
	LCD_DisplayString(30,90,16,"degree:");
	LCD_DisplayString(30,120,16,"PendulumAngle:");
	LCD_DisplayString(30,150,16,"PendulumOmega:");
	
	circle_temp=motor_encoder.circle_cnt;
	speed_temp=(int)(motor_encoder.speed*10);
	deg_temp=(int)(motor_encoder.degree);
	pangle_temp=(int)(PAngle.degree*10);
	pangle_sp_temp=(int)(PAngle.speed);
	if (speed_temp>=0)
	{
	LCD_DisplayString(80+9*6,30,16," ");
	LCD_DisplayNum(80+10*6,30,(u32)speed_temp,4,16,0);
	}
	else
	{
	LCD_DisplayString(80+9*6,30,16,"-");
	LCD_DisplayNum(80+10*6,30,(u32)-speed_temp,4,16,0);
	}
	if (circle_temp>=0)
	{
	LCD_DisplayString(80+9*6,60,16," ");
	LCD_DisplayNum(80+10*6,60,(u32)circle_temp,4,16,0);
	}
	else
	{
	LCD_DisplayString(80+9*6,60,16,"-");
	LCD_DisplayNum(80+10*6,60,(u32)-circle_temp,4,16,0);
	}
	if (deg_temp>=0)
	{
	LCD_DisplayString(80+9*6,90,16," ");
	LCD_DisplayNum(80+10*6,90,(u32)deg_temp,4,16,0);
	}
	else
	{
	LCD_DisplayString(80+9*6,90,16,"-");
	LCD_DisplayNum(80+10*6,90,(u32)-deg_temp,4,16,0);
	}
	if (pangle_temp>=0)
	{
	LCD_DisplayString(80+11*6,120,16," ");
	LCD_DisplayNum(80+12*6,120,(u32)pangle_temp,4,16,0);
	}
	else
	{
	LCD_DisplayString(80+11*6,120,16,"-");
	LCD_DisplayNum(80+12*6,120,(u32)-pangle_temp,4,16,0);
	}
	if (pangle_sp_temp>=0)
	{
	LCD_DisplayString(80+11*6,150,16," ");
	LCD_DisplayNum(80+12*6,150,(u32)pangle_sp_temp,4,16,0);
	}
	else
	{
	LCD_DisplayString(80+11*6,150,16,"-");
	LCD_DisplayNum(80+12*6,150,(u32)-pangle_sp_temp,4,16,0);
	}
	if (chassis_out>=0)
	{
	LCD_DisplayString(80+11*6,180,16," ");
	LCD_DisplayNum(80+12*6,180,(u32)chassis_out,4,16,0);
	}
	else
	{
	LCD_DisplayString(80+11*6,180,16,"-");
	LCD_DisplayNum(80+12*6,180,(u32)-chassis_out,4,16,0);
	}
	if (speed_out>=0)
	{
	LCD_DisplayString(80+11*6,210,16," ");
	LCD_DisplayNum(80+12*6,210,(u32)speed_out,4,16,0);
	}
	else
	{
	LCD_DisplayString(80+11*6,210,16,"-");
	LCD_DisplayNum(80+12*6,210,(u32)-speed_out,4,16,0);
	}
	if (exp_angle>=0)
	{
	LCD_DisplayString(80+11*6,240,16," ");
	LCD_DisplayNum(80+12*6,240,(u32)100*exp_angle,4,16,0);
	}
	else
	{
	LCD_DisplayString(80+11*6,240,16,"-");
	LCD_DisplayNum(80+12*6,240,(u32)-100*exp_angle,4,16,0);
	}
	delay_ms(30);
	}
}
