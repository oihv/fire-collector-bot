#include "Bsp.h"
#include "CH452.h"
#include "Motor.h"
#include "misc.h"
#include "stdio.h"

int RPM = 0;
// ADC value
uint16_t adc_value;

// Distance measured in cm
int distance;

// int num = -1;
int main(void) { // Initialize the system
  BSP_Init();
  ServoMotor_Config();
  uint8_t switch_state;
	
  while (1) {
    // num = CH452_GetKey();
    // u16 pwm =200;

    /* switch(num){
            case 0:
                    CH452_SetDigit(3, 0);
                    break;
            case 1:
                    CH452_SetDigit(3, 1);
                    Set_Motor1_RPM(200);
                    break;
            case 2:
                    CH452_SetDigit(3, 2);
                    Set_Motor1_RPM(0);
                    break;
            case 3:
                    CH452_SetDigit(3, 3);
                    Set_Motor1_RPM(-200);
                    break;
            case 4:
                    CH452_SetDigit(3, 4);
                    delay_ms(195);
                    TIM_SetCompare2(TIM2, 195);//0
                    break;
            case 5:
                    CH452_SetDigit(3, 5);
                    delay_ms(190);
                    TIM_SetCompare2(TIM2, 185);//90��
                    break;
            case 6:
                    CH452_SetDigit(3, 6);
                    delay_ms(190);
                    TIM_SetCompare2(TIM2, 175);//180�ȣ���
                    break;
            case 7:
                    CH452_SetDigit(3, 7);
                    break;
            case 8:
                    CH452_SetDigit(3, 8);
                    break;
            case 9:
                    CH452_SetDigit(3, 9);
                    break;
            case 10:
                    CH452_SetDigit(3, 10);
                    break;
            case 11:
                    CH452_SetDigit(3, 11);
                    break;
            case 12:
                    CH452_SetDigit(3, 12);
                    break;
            case 13:
                    CH452_SetDigit(3, 13);
                    break;
            case 14:
                    CH452_SetDigit(3, 14);
                    break;
            case 15:
                    CH452_SetDigit(3, 15);
                    break;
            default:
                    break;
    } */
    // Move motor
    /* Set_Motor1_RPM(20);
    delay_ms(2000);
    Set_Motor1_RPM(-20);
    delay_ms(2000); */

    // Move servo
    /* TIM_SetCompare2(TIM2, 184); // Move servo 1 counter clockwise
    TIM_SetCompare1(TIM2, 184); // Move servo 2
    delay_ms(2000);
    TIM_SetCompare2(TIM2, 185); // Stop
    TIM_SetCompare1(TIM2, 185);
    delay_ms(2000);
    TIM_SetCompare2(TIM2, 186); // Move clockwise
    TIM_SetCompare1(TIM2, 186);
    delay_ms(2000); */

    // Photo electric switch
    /* switch_state = Read_IO2;
    if (switch_state == 0) // If the switch detects an object
    {
            Set_Motor1_RPM(20);
    }
    else
    {
    } */
    // Start an ADC conversion
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    // IR test
    adc_value = ADC_GetConversionValue(ADC1);
    if (adc_value != 0)
      distance = 1735 / adc_value - 6;
  }
}
