#ifndef _DATATRANSFER_H_
#define _DATATRANSFER_H_

void ANO_DT_Send_Status(float angle_rol, float angle_pit, float angle_yaw, s32 alt, u8 fly_model, u8 armed);
void Usart1_DataPrepare(u8 com_data);
void ANO_DT_Send_Senser(s16 a_x,s16 a_y,s16 a_z,s16 g_x,s16 g_y,s16 g_z,s16 m_x,s16 m_y,s16 m_z);
void DataTransferTask(u32 sys_time);
void Data_Receive_Anl(u8 *data_buf,u8 num);
extern u8 send_pid1,send_pid2,send_pid3,appTosave;
void ANO_DT_Send_PID(u8 group,float p1_p,float p1_i,float p1_d,float p2_p,float p2_i,float p2_d,float p3_p,float p3_i,float p3_d);
extern vs16 ControlMode;
#endif
