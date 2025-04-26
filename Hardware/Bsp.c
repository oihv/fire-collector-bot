#include "Bsp.h"
#include "math.h"
#include "Motor.h"
#include "CH452.h"
#include "mpu6050.h"

/********************************************* ����ʼ�� *********************************************/
/******/
void BSP_Init()
{
	// ��ʼ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
							   RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
							   RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM1,
						   ENABLE); // APB2����ʱ��ʹ��
	Motor_Init();
	Digital_Input_Init();
	Analog_Input_Init();
	TT_Motor_Init();
	CH452_Init();
	MPU_Init();
}
/********************************************* ---------- *********************************************/
/***************************************** �����������ʼ�� ****************************************/
/******/
void Digital_Input_Init()
{
	/*********************************************
	 ***2x12 pin header, next to Reset button, from top to bottom:***
	 ** PA12   5V							    ** ANALOG
	 ** PA15   5V								**
	 ** PB3    5V								**
	 ** PB4    5V								**
	 ** PB5    Open, stop the small 5V to 3.3V circuit	**
	 ** PB8    3.3V								**
	 ** PB9    3.3V								**
	 ** PC13   3.3V								**
	 ** PC14   Open, stop the small 3.3V to GND circuit	**
	 ** PC15   GND								**
	 ** PB11   GND								**
	 ** PB10   GND								**
	 **********************************************/
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	GPIO_InitTypeDef GPIO_Input;
	// PA12 set as analog
	/* GPIO_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Input.GPIO_Pin = GPIO_Pin_12;
	GPIO_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Input); */
	// PA15
	GPIO_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Input.GPIO_Pin = GPIO_Pin_15;
	GPIO_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Input);
	// PB3
	GPIO_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Input.GPIO_Pin = GPIO_Pin_3;
	GPIO_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Input);
	// PB4
	GPIO_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Input.GPIO_Pin = GPIO_Pin_4;
	GPIO_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Input);
	// PB5
	GPIO_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Input.GPIO_Pin = GPIO_Pin_5;
	GPIO_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Input);
	// PB8
	GPIO_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Input.GPIO_Pin = GPIO_Pin_8;
	GPIO_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Input);
	// PB9
	GPIO_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Input.GPIO_Pin = GPIO_Pin_9;
	GPIO_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Input);
	// PC13
	GPIO_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Input.GPIO_Pin = GPIO_Pin_13;
	GPIO_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_Input);
	// PC14
	GPIO_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Input.GPIO_Pin = GPIO_Pin_14;
	GPIO_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_Input);
	// PC15
	GPIO_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Input.GPIO_Pin = GPIO_Pin_15;
	GPIO_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_Input);
	// PB11
	GPIO_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Input.GPIO_Pin = GPIO_Pin_11;
	GPIO_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Input);
	// PB10
	GPIO_Input.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Input.GPIO_Pin = GPIO_Pin_10;
	GPIO_Input.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Input);
}

void Analog_Input_Init()
{
	// Configure PA12 as an analog input
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Configure the ADC
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &ADC_InitStructure);

	// Configure the ADC channel
    ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_55Cycles5);

	// Start the ADC
	ADC_Cmd(ADC1, ENABLE);
}

void TT_Motor_Init()
{
	GPIO_InitTypeDef GPIO_TTMotor;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	// PA3 controls A and B motors, set as alternate function push-pull
	GPIO_TTMotor.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_TTMotor.GPIO_Pin = GPIO_Pin_3;
	GPIO_TTMotor.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_TTMotor);

	// PA4 controls C and D motors, set as push-pull output
	GPIO_TTMotor.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_TTMotor.GPIO_Pin = GPIO_Pin_4;
	GPIO_TTMotor.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_TTMotor);
	TT_MotorCD_Disable(); // Disable C and D motors

	// Configure TIM2 timer
	TIM_TimeBaseStructure.TIM_Period = (1000 - 1);				// Set auto-reload value
	TIM_TimeBaseStructure.TIM_Prescaler = 720;					// Set prescaler value
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;				// Set clock division: TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM up counter mode
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);				// Initialize TIM2

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			  // Select PWM mode 2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // Enable compare output
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	  // Set output polarity high
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);					  // Initialize TIM2 OC4
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);			  // Enable TIM2 OC4 preload register
	TIM_Cmd(TIM2, ENABLE);										  // Enable TIM2
	TIM_SetCompare4(TIM2, 1000);								  // Set initial duty cycle for A and B motors to 0
}

// Set the duty cycle for Motor AB using TT. The duty cycle range is [0,1] for RPM.
void TT_MotorAB_Set_Duty(int rpm)
{
	if (rpm > 800)
		rpm = 800;
	if (rpm < 0)
	{
		rpm = 0;
	}
	if (rpm == 0)
		TIM_SetCompare4(TIM2, 1000);
	else
	{
		TIM_SetCompare4(TIM2, 1000 - rpm);
	}
}
/************************************* ---------- *************************************/
/************************************* ��ʱ���� *************************************/
/******/
void delay_us(u32 uS)
{									// uS΢�뼶��ʱ���򣨲ο�ֵ������ʱ����72MHzʱ���ֵ233015��
	SysTick->LOAD = AHB_INPUT * uS; // ��װ������ֵ������Ƶ��72MHz��72��Ϊ1΢�룩
	SysTick->VAL = 0x00;			// ��ն�ʱ���ļ�����
	SysTick->CTRL = 0x00000005;		// ʱ��ԴHCLK���򿪶�ʱ��
	while (!(SysTick->CTRL & 0x00010000))
		;						// �ȴ�������0
	SysTick->VAL = 0x00;		// ��ն�ʱ���ļ�����
	SysTick->CTRL = 0x00000004; // �رն�ʱ��
}

void delay_ms(u16 ms)
{ // mS���뼶��ʱ���򣨲ο�ֵ������ʱ�������ֵ65535=2^16��
	while (ms-- != 0)
	{
		delay_us(1000); // ����1000΢�����ʱ
	}
}

void delay_s(u16 s)
{ // S�뼶��ʱ���򣨲ο�ֵ������ʱ�������ֵ65535��
	while (s-- != 0)
	{
		delay_ms(1000); // ����1000�������ʱ
	}
}
/************************************* ---------- *************************************/
/*************************************  IIC���� *************************************/
/******/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_IIC;
	GPIO_IIC.GPIO_Pin = GPIO_Pin_6;
	GPIO_IIC.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_IIC.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_IIC);

	GPIO_IIC.GPIO_Pin = GPIO_Pin_7;
	GPIO_IIC.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_IIC.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_IIC);
	SCL = 1;
	SDAout = 1;
}
// ���� IIC ��ʼ�ź�
void IIC_Start(void)
{
	SDAout = 1;
	SCL = 1;
	delay_us(2);
	SDAout = 0; // START:when CLK is high,DATA change form high to low
	delay_us(2);
	SCL = 0; // ǯס I2C ���ߣ�׼�����ͻ��������
}
// ���� IIC ֹͣ�ź�
void IIC_Stop(void)
{
	SCL = 0;
	SDAout = 0; // STOP:when CLK is high DATA change form low to high
	delay_us(2);
	SCL = 1;
	SDAout = 1; // ���� I2C ���߽����ź�
	delay_us(2);
}
// �ȴ�Ӧ���źŵ���
// ����ֵ��1������Ӧ��ʧ��
// 0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	SDAout = 1;
	delay_us(1);
	SCL = 1;
	delay_us(1);
	while (SDAin)
	{
		ucErrTime++;
		if (ucErrTime > 250)
		{
			IIC_Stop();
			return 1;
		}
	}
	SCL = 0; // ʱ����� 0
	return 0;
}
// ���� ACK Ӧ��
void IIC_Ack(void)
{
	SCL = 0;
	SDAout = 0;
	delay_us(2);
	SCL = 1;
	delay_us(2);
	SCL = 0;
}
// ������ ACK Ӧ��
void IIC_NAck(void)
{
	SCL = 0;
	SDAout = 1;
	delay_us(2);
	SCL = 1;
	delay_us(2);
	SCL = 0;
}
// IIC ����һ���ֽ�
// ���شӻ�����Ӧ��
// 1����Ӧ��
// 0����Ӧ��
void IIC_Send_Byte(u8 txd)
{
	u8 t;
	SCL = 0; // ����ʱ�ӿ�ʼ���ݴ���
	for (t = 0; t < 8; t++)
	{
		SDAout = (txd & 0x80) >> 7;
		txd <<= 1;
		delay_us(2); // ��ʱ�Ǳ����
		SCL = 1;
		delay_us(2);
		SCL = 0;
		delay_us(2);
	}
}

// Read 1 byte, send ACK when ack=1, send NACK when ack=0
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	for (i = 0; i < 8; i++)
	{
		SCL = 0;
		delay_us(2);   // Pull clock line low
		SCL = 1;	   // Pull clock line high
		receive <<= 1; // Shift received byte left
		if (SDAin)	   // If data line is high
			receive++; // Increment received byte
		delay_us(1);   // Short delay
	}
	if (!ack)
		IIC_NAck(); // Send NACK
	else
		IIC_Ack();	// Send ACK
	return receive; // Return received byte
}

/*************************************   Note   *************************************/
/*
	GPIO_Mode_AIN: Analog input mode
	GPIO_Mode_IN_FLOATING: Floating input mode
	GPIO_Mode_IPD: Pull-down input mode
	GPIO_Mode_IPU: Pull-up input mode
	GPIO_Mode_Out_OD: Open-drain output mode
	GPIO_Mode_Out_PP: Push-pull output mode
	GPIO_Mode_AF_OD: Alternate function open-drain mode
	GPIO_Mode_AF_PP: Alternate function push-pull mode
*/
/************************************* --------- *************************************/
