#include "main.h"
/*----------USART1---PA9---PA10----*/
/*----------USART2---PD5---PD6-----*/
/************************************/
/*******����1����*********************/
u8 Rx_1_Buf[256];	
u8 Tx1Buffer[256];
u8 Tx1DMABuffer[256];
u8 Tx1Counter=0;
u8 count1=0; 
/***********************************/

void Usart1_Init(u32 br_num)
{  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); 
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = br_num;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure); 
	
  USART_Cmd(USART1, ENABLE);
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
	NVIC_Init(&NVIC_InitStructure);	
	
	DMA_DeInit(DMA2_Stream7);
	
	while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE){}//�ȴ�DMA������ 
	
  /* ���� DMA Stream */
  DMA_InitStructure.DMA_Channel = DMA_Channel_4;  //ͨ��ѡ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART1->DR;//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)Tx1DMABuffer;//DMA �洢��0��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;//�洢��������ģʽ
  DMA_InitStructure.DMA_BufferSize = 0;//���ݴ����� 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ����ͨģʽ 
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
  DMA_Init(DMA2_Stream7, &DMA_InitStructure);//��ʼ��DMA Stream

}




void USART1_IRQHandler(void)
{
	u8 com_data;
	if( USART_GetITStatus(USART1,USART_IT_RXNE) )					//����ǽ����ж�
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		com_data = USART1->DR;
		Usart1_DataPrepare(com_data);												//���ݽ���

	}
}


void Usart1_Send(unsigned char *DataToSend ,u8 data_num)
{
  u8 i;
	static uint16_t num=0;
	static u8 len=0;
	
	DMA_Cmd(DMA2_Stream7, DISABLE);
	DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);//���DMA2_Steam7������ɱ�־
	num = DMA_GetCurrDataCounter(DMA2_Stream7);
	
	for(i=0;i<data_num;i++)
	{
		Tx1Buffer[count1++] = *(DataToSend+i);
	}
	for (i=0;i<num;i++)
	{
		Tx1DMABuffer[i]=Tx1Buffer[((u8)(len-num+i))];
	}
	for (;i<num+data_num;i++)
	{
		Tx1DMABuffer[i]=*(DataToSend+i-num);
	}
	len=count1;
	while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE){}	//ȷ��DMA���Ա�����  
	DMA2_Stream7->NDTR = (uint16_t)(num+data_num);          //���ݴ�����  
	DMA_Cmd(DMA2_Stream7, ENABLE);      

}


