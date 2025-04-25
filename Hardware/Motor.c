#include "Motor.h"
#include "sys.h" // STM header file
void Motor_Init() {
  GPIO_InitTypeDef GPIO_Motor;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1,
                      ENABLE); // TIM1 needs to be remapped

  // PB12 is used to enable Motor1
  GPIO_Motor.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Motor.GPIO_Pin = GPIO_Pin_12;
  GPIO_Motor.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_Motor);
  Motor1_Enable(); // Enable Motor1, see Motor.h

  // PB13 is used to enable Motor2
  GPIO_Motor.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Motor.GPIO_Pin = GPIO_Pin_13;
  GPIO_Motor.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_Motor);
  Motor2_Enable(); // Enable Motor2

  // PB14 is used to enable Motor3
  GPIO_Motor.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Motor.GPIO_Pin = GPIO_Pin_14;
  GPIO_Motor.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_Motor);
  Motor3_Enable(); // Enable Motor3

  // PB15 is used to enable Motor4
  GPIO_Motor.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Motor.GPIO_Pin = GPIO_Pin_15;
  GPIO_Motor.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_Motor);
  Motor4_Enable(); // Enable Motor4

  // PA6 is used for TIM3 CH1, controlling Motor1+
  GPIO_Motor.GPIO_Pin = GPIO_Pin_6;
  GPIO_Motor.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Motor.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_Motor);

  // PA7 is used for TIM3 CH2, controlling Motor1-
  GPIO_Motor.GPIO_Pin = GPIO_Pin_7;
  GPIO_Motor.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Motor.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_Motor);

  // PB0 is used for TIM3 CH3, controlling Motor2+
  GPIO_Motor.GPIO_Pin = GPIO_Pin_0;
  GPIO_Motor.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Motor.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_Motor);

  // PB1 is used for TIM3 CH4, controlling Motor2-
  GPIO_Motor.GPIO_Pin = GPIO_Pin_1;
  GPIO_Motor.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Motor.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_Motor);

  // PA8 is used for TIM1 CH1, controlling Motor3+
  GPIO_Motor.GPIO_Pin = GPIO_Pin_8;
  GPIO_Motor.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Motor.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_Motor);

  // PA9 is used for TIM1 CH2, controlling Motor3-
  GPIO_Motor.GPIO_Pin = GPIO_Pin_9;
  GPIO_Motor.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Motor.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_Motor);

  // PA10 is used for TIM1 CH3, controlling Motor4+
  GPIO_Motor.GPIO_Pin = GPIO_Pin_10;
  GPIO_Motor.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Motor.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_Motor);

  // PA11 is used for TIM1 CH4, controlling Motor4-
  GPIO_Motor.GPIO_Pin = GPIO_Pin_11;
  GPIO_Motor.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Motor.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_Motor);

  // Initialize TIM1 and TIM3 timers
  TIM_TimeBaseStructure.TIM_Period =
      (1000 - 1);                          // Set the auto-reload register value
  TIM_TimeBaseStructure.TIM_Prescaler = 0; // Set the prescaler value
  TIM_TimeBaseStructure.TIM_ClockDivision =
      0; // Set the clock division: TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode =
      TIM_CounterMode_Up;                         // TIM up counting mode
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); // Initialize TIM1
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); // Initialize TIM3

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; // Select PWM mode 2
  TIM_OCInitStructure.TIM_OutputState =
      TIM_OutputState_Enable; // Enable compare output
  TIM_OCInitStructure.TIM_OCPolarity =
      TIM_OCPolarity_High;                 // Set high output polarity
  TIM_OC1Init(TIM1, &TIM_OCInitStructure); // Initialize TIM1 OC1
  TIM_OC2Init(TIM1, &TIM_OCInitStructure); // Initialize TIM1 OC2
  TIM_OC3Init(TIM1, &TIM_OCInitStructure); // Initialize TIM1 OC3
  TIM_OC4Init(TIM1, &TIM_OCInitStructure); // Initialize TIM1 OC4
  TIM_OC1Init(TIM3, &TIM_OCInitStructure); // Initialize TIM3 OC1
  TIM_OC2Init(TIM3, &TIM_OCInitStructure); // Initialize TIM3 OC2
  TIM_OC3Init(TIM3, &TIM_OCInitStructure); // Initialize TIM3 OC3
  TIM_OC4Init(TIM3, &TIM_OCInitStructure); // Initialize TIM3 OC4

  TIM_OC1PreloadConfig(
      TIM1, TIM_OCPreload_Enable); // Enable TIM1 OC1 preload register
  TIM_OC2PreloadConfig(
      TIM1, TIM_OCPreload_Enable); // Enable TIM1 OC2 preload register
  TIM_OC3PreloadConfig(
      TIM1, TIM_OCPreload_Enable); // Enable TIM1 OC3 preload register
  TIM_OC4PreloadConfig(
      TIM1, TIM_OCPreload_Enable); // Enable TIM1 OC4 preload register
  TIM_OC1PreloadConfig(
      TIM3, TIM_OCPreload_Enable); // Enable TIM3 OC1 preload register
  TIM_OC2PreloadConfig(
      TIM3, TIM_OCPreload_Enable); // Enable TIM3 OC2 preload register
  TIM_OC3PreloadConfig(
      TIM3, TIM_OCPreload_Enable); // Enable TIM3 OC3 preload register
  TIM_OC4PreloadConfig(
      TIM3, TIM_OCPreload_Enable);  // Enable TIM3 OC4 preload register
  TIM_CtrlPWMOutputs(TIM1, ENABLE); // Enable TIM1
  TIM1->BDTR |= TIM_BDTR_MOE;
  TIM_Cmd(TIM1, ENABLE); // Enable TIM1
  TIM_Cmd(TIM3, ENABLE); // Enable TIM3
}

// ���õ��1��ת��
void Set_Motor1_RPM(int RPM) {
  RPM = -RPM;
	if (RPM > 400) RPM = 400;
	if (RPM < -400) RPM = -400;
  if (RPM == 0) {
    TIM_SetCompare1(TIM3, 1000 - RPM);
    TIM_SetCompare2(TIM3, 1000);
  } else if (RPM > 0) {
    //RPM = RPM * 0.8 + 200;
    TIM_SetCompare1(TIM3, 1000 - RPM);
    TIM_SetCompare2(TIM3, 1000);
  } else {
    //RPM = RPM * 0.8 - 200;
    TIM_SetCompare1(TIM3, 1000);
    TIM_SetCompare2(TIM3, 1000 + RPM);
  }
}
void Set_Motor2_RPM(int RPM) {
  //solder kebalik
	if (RPM > 400) RPM = 400;
	if (RPM < -400) RPM = -400;
  if (RPM == 0) {
    TIM_SetCompare3(TIM3, 1000 - RPM);
    TIM_SetCompare4(TIM3, 1000);
  } else if (RPM > 0) {
    //RPM = RPM * 0.8 + 200;
    TIM_SetCompare3(TIM3, 1000 - RPM);
    TIM_SetCompare4(TIM3, 1000);
  } else {
    //RPM = RPM * 0.8 - 200;
    TIM_SetCompare3(TIM3, 1000);
    TIM_SetCompare4(TIM3, 1000 + RPM);
  }
}
void Set_Motor3_RPM(int RPM) {
	if (RPM > 400) RPM = 400;
	if (RPM < -400) RPM = -400;
  if (RPM == 0) {
    TIM_SetCompare1(TIM1, 1000 - RPM);
    TIM_SetCompare2(TIM1, 1000);
  } else if (RPM > 0) {
    //RPM = RPM * 0.8 + 200;
    TIM_SetCompare1(TIM1, 1000 - RPM);
    TIM_SetCompare2(TIM1, 1000);
  } else {
    //RPM = RPM * 0.8 - 200;
    TIM_SetCompare1(TIM1, 1000);
    TIM_SetCompare2(TIM1, 1000 + RPM);
  }
}
void Set_Motor4_RPM(int RPM) {
	if (RPM > 400) RPM = 400;
	if (RPM < -400) RPM = -400;
  if (RPM == 0) {
    TIM_SetCompare3(TIM1, 1000 - RPM);
    TIM_SetCompare4(TIM1, 1000);
  } else if (RPM > 0) {
    //RPM = RPM * 0.8 + 200;
    TIM_SetCompare3(TIM1, 1000 - RPM);
    TIM_SetCompare4(TIM1, 1000);
  } else {
    //RPM = RPM * 0.8 - 200;
    TIM_SetCompare3(TIM1, 1000);
    TIM_SetCompare4(TIM1, 1000 + RPM);
  }
}

void SetServoPosition(uint16_t position) {
  if (position > 195)
    position = 195; // Ensure position is within valid range
  if (position < 175)
    position = 175;
  TIM_SetCompare2(TIM2, position);
}

void ServoMotor_Config(void) {
  GPIO_InitTypeDef GPIO_MOTORInitStructure;
  TIM_TimeBaseInitTypeDef Tim_MOTORInitStructure;
  TIM_OCInitTypeDef Time_PWMInitStructure;

  // Enable clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  // Configure GPIO structure for PA0 and PA1
  GPIO_MOTORInitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_MOTORInitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // PA0 and PA1
  GPIO_MOTORInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_MOTORInitStructure);

  // Configure timer structure
  Tim_MOTORInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  Tim_MOTORInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  Tim_MOTORInitStructure.TIM_Period = 200 - 1;
  Tim_MOTORInitStructure.TIM_Prescaler = 7200 - 1;
  TIM_TimeBaseInit(TIM2, &Tim_MOTORInitStructure);

  // Configure timer for PWM structure for Channel 1 (PA0)
  Time_PWMInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  Time_PWMInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  Time_PWMInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIM2, &Time_PWMInitStructure); // Use TIM_OC1Init for Channel 1

  // Configure timer for PWM structure for Channel 2 (PA1)
  Time_PWMInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  Time_PWMInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  Time_PWMInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM2, &Time_PWMInitStructure); // Use TIM_OC2Init for Channel 2

  // Enable preload register for Channel 1 and Channel 2
  TIM_OC1PreloadConfig(
      TIM2, TIM_OCPreload_Enable); // Use TIM_OC1PreloadConfig for Channel 1
  TIM_OC2PreloadConfig(
      TIM2, TIM_OCPreload_Enable); // Use TIM_OC2PreloadConfig for Channel 2

  // Enable timer
  TIM_Cmd(TIM2, ENABLE);
}
