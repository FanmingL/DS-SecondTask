#include "main.h"
float exp_angle=0.0f;
static void Task_2ms(void)
{

}
		float position_out,speed_out,chassis_out;
static void Task_5ms(void)
{
	float inner_loop_time=GetInnerLoop(MS_5MS_TIME)/1000000.0f;
		position_out= -PID_calculate( inner_loop_time,            //周期
														0,				//前馈
														exp_angle,				//期望值（设定值）
														-PAngle.sin,			//反馈值
														&PitchP_arg, //PID参数结构体
														&PitchP_val,	//PID数据结构体
														0.1			//integration limit，积分限幅
														 );			//输出	
	speed_out= inner_loop_time* PID_calculate( inner_loop_time,            //周期
														0,				//前馈
														position_out,				//期望值（设定值）
														PAngle.speed,			//反馈值
														&PitchS_arg, //PID参数结构体
														&PitchS_val,	//PID数据结构体
														1500			//integration limit，积分限幅
														 );			//输出
		
		//DOWN();
}
static void Task_10ms(void)
{
	float inner_loop_time=GetInnerLoop(MS_20MS_TIME)/1000000.0f;
	Refresh_Encoder();
			chassis_out= PID_calculate( inner_loop_time,            //周期
														0,				//前馈
														motor_encoder.speed+2*position_out*inner_loop_time,				//期望值（设定值）
														motor_encoder.speed,			//反馈值
														&Chassis_arg, //PID参数结构体
														&Chassis_left_val,	//PID数据结构体
														32			//integration limit，积分限幅
														 );			//输出	
	 chassis_out=LIMIT(chassis_out,-1000,1000);
	//	chassis_out=(my_abs(chassis_out)>1000)?1000:my_abs(chassis_out);
	if(PAngle.degree<135||PAngle.degree>240){
		chassis_out=0;	
		PWM_out=chassis_out;
	}else{
		if (chassis_out>0){
			UP();
		PWM_out=(u16)((chassis_out));}
		else {
		DOWN();
			PWM_out=(u16)(-(chassis_out));
		}
	}
}
static void Task_20ms(void)
{
	
	
}
static void Task_50ms(void)
{
	
		Refresh_Angle();

}
void ControlTask(void)
{
	static u32 MS_TIME=0;
	MS_TIME++;
	DataTransferTask(MS_TIME);
	if(MS_TIME%2==0)Task_2ms();
	if(MS_TIME%5==0)Task_5ms();
	if(MS_TIME%10==0)Task_10ms();
	if(MS_TIME%20==0)Task_20ms();
	if(MS_TIME%50==0)Task_50ms();
}
