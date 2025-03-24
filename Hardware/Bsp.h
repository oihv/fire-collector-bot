#ifndef __BSP_H
#define __BSP_H	 
#include "sys.h" //STMͷ�ļ�
#include "stdio.h"

#define SCL PBout(6)
#define SDAout PBout(7)
#define SDAin PBin(7)

#define AHB_INPUT  72  //�밴RCC�����õ�AHBʱ��Ƶ����д�������λMHz��

#define Read_IO1  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)
#define Read_IO2  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15)
#define Read_IO3  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)
#define Read_IO4  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)
#define Read_IO5  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)
#define Read_IO6  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)
#define Read_IO7  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)
#define Read_IO8  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)
#define Read_IO9  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14)
#define Read_IO10 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15)
#define Read_IO11 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)
#define Read_IO12 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)
#define TT_MotorCD_Enable()  GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define TT_MotorCD_Disable() GPIO_ResetBits(GPIOA, GPIO_Pin_4)

void BSP_Init(void);
void Digital_Input_Init(void);
void Analog_Input_Init(void);
void TT_Motor_Init(void);
void TT_MotorAB_Set_Duty(int rpm);

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�


void delay_us(u32 uS);
void delay_ms(u16 ms);
void delay_s(u16 s);

#endif


