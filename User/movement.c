#include "movement.h"
#include "Motor.h"

/*
 * Motor map
 *              HEAD
 *               ===
 * front left <= 1 4 => front right
 *  rear left <= 2 3 => rear right
 */
int pidcorrection;

void moveForward(int rpm) {
  while(1){
    if(FourLineCross()){
      break;
    }
    else{
      pidcorrection = PID();
      Set_Motor1_RPM(-rpm);
      Set_Motor2_RPM(-rpm);
      Set_Motor3_RPM(rpm);
      Set_Motor4_RPM(rpm);
    }
  }
}

void moveBackward(int rpm) {
  Set_Motor1_RPM(rpm);
  Set_Motor2_RPM(rpm);
  Set_Motor3_RPM(-rpm);
  Set_Motor4_RPM(-rpm);
}

void moveLeft(int rpm) {
  while(1){
    if(VerticalLineCentered()){
      break;
    }
    else{
      Set_Motor1_RPM(rpm);
      Set_Motor2_RPM(-rpm);
      Set_Motor3_RPM(-rpm);
      Set_Motor4_RPM(rpm);
    }
  }
}

void moveRight(int rpm) {
<<<<<<< HEAD
  Set_Motor1_RPM(-rpm);
  Set_Motor2_RPM(rpm);
  Set_Motor3_RPM(rpm);
  Set_Motor4_RPM(-rpm);
=======
  Set_Motor1_RPM(rpm);
  Set_Motor2_RPM(-rpm);
  Set_Motor3_RPM(-rpm);
  Set_Motor4_RPM(rpm);
>>>>>>> 9c4a068916033363d9ef95e8122479643cc21b97
}

void rotateCW(int rpm) {
  Set_Motor1_RPM(rpm);
  Set_Motor2_RPM(rpm);
  Set_Motor3_RPM(rpm);
  Set_Motor4_RPM(rpm);
}

// Rotate counter clockwise
void rotateCCW(int rpm) {
  Set_Motor1_RPM(-rpm);
  Set_Motor2_RPM(-rpm);
  Set_Motor3_RPM(-rpm);
  Set_Motor4_RPM(-rpm);
}

void stopMotor() {
  Set_Motor1_RPM(0);
  Set_Motor2_RPM(0);
  Set_Motor3_RPM(0);
  Set_Motor4_RPM(0);
}

// TODO: implement movement based on PID output
