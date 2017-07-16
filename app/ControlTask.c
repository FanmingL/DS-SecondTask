#include "main.h"
float exp_angle=0.0f;
int LowSpeedMode=0;
static void QP(float inner_loop_time)
{
	if (my_abs(PAngle.speed)<100){
			speed_out= -PID_calculate( inner_loop_time,            //周期
														0,				//前馈
								(180.0f-PAngle.degree)/my_abs(180.0f-PAngle.degree)*200.0f,				//期望值（设定值）
													//	0,
														PAngle.speed,			//反馈值
														&PitchS_arg, //PID参数结构体
														&PitchS_val,	//PID数据结构体
														500			//integration limit，积分限幅
														 );			//输出
		chassis_out= -PID_calculate( inner_loop_time,            //周期
														0,				//前馈
														motor_encoder.speed+speed_out*6.0f*inner_loop_time,				//期望值（设定值）
														motor_encoder.speed,			//反馈值
														&Chassis_arg, //PID参数结构体
														&Chassis_left_val,	//PID数据结构体
														100			//integration limit，积分限幅
														 );			//输出	
	 
	 
		chassis_out=LIMIT(chassis_out,-1000,1000);
		if (chassis_out>0){
			UP();
		PWM_out=(u16)((chassis_out));}
		else {
		DOWN();
			PWM_out=(u16)(-(chassis_out));
		}
	}
//	else if (my_abs(PAngle.speed)<100&&(LowSpeedMode==0)){
//			PWM_out=0;
//	}
	if (PAngle.degree<5&&PAngle.degree>0){
		if (my_abs(PAngle.speed)>300){LowSpeedMode=1;}
		else LowSpeedMode=0;
	}

}
static void PID_Control(float inner_loop_time)
{
	if (my_abs(PAngle.speed)<300){
	exp_angle = -PID_calculate( inner_loop_time,            //周期
														0,				//前馈
														0,				//期望值（设定值）
														motor_encoder.speed,			//反馈值
														&Theta_arg, //PID参数结构体
														&Theta_val,	//PID数据结构体
														0.3			//integration limit，积分限幅
														 );			//输出	
	}
	else 
	{
		exp_angle=0;
	}
	
	position_out= PID_calculate( inner_loop_time,            //周期
														0,				//前馈
														exp_angle,				//期望值（设定值）
														-PAngle.sin,			//反馈值
														&PitchP_arg, //PID参数结构体
														&PitchP_val,	//PID数据结构体
														0.3			//integration limit，积分限幅
														 );			//输出	
	speed_out= -PID_calculate( inner_loop_time,            //周期
														0,				//前馈
														position_out,				//期望值（设定值）
													//	0,
														PAngle.speed,			//反馈值
														&PitchS_arg, //PID参数结构体
														&PitchS_val,	//PID数据结构体
														500			//integration limit，积分限幅
														 );			//输出
	chassis_out= -PID_calculate( inner_loop_time,            //周期
														0,				//前馈
														motor_encoder.speed+speed_out*6.0f*inner_loop_time,				//期望值（设定值）
														motor_encoder.speed,			//反馈值
														&Chassis_arg, //PID参数结构体
														&Chassis_left_val,	//PID数据结构体
														100			//integration limit，积分限幅
														 );			//输出	
	 
	 
	 chassis_out=LIMIT(chassis_out,-1000,1000);
	
	if(PAngle.degree<120||PAngle.degree>240){
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
static void Task_2ms(void)
{

}
float position_out,speed_out,chassis_out;
static void Task_5ms(void)
{
	float inner_loop_time=GetInnerLoop(MS_5MS_TIME)/1000000.0f;
}
int Speed_Dog=0,Speed_feed=100;

static void Task_10ms(void)
{
	float inner_loop_time=GetInnerLoop(MS_10MS_TIME)/1000000.0f;
	Refresh_Angle();
	Refresh_Encoder();
//	PID_Control(inner_loop_time);
//	if(PAngle.degree>150&&PAngle.degree<210)
		PID_Control(inner_loop_time);
//		else QP(inner_loop_time);
}
static void Task_20ms(void)
{
	
	
}
static void Task_50ms(void)
{
	

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
