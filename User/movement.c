#include "movement.h"
#include "Motor.h"

void moveForward(int rpm) {
  Set_Motor1_RPM(rpm);
  Set_Motor2_RPM(rpm);
  Set_Motor3_RPM(-rpm);
  Set_Motor4_RPM(rpm);
}

void moveBackward(int rpm) {

  Set_Motor1_RPM(-rpm);
  Set_Motor2_RPM(-rpm);
  Set_Motor3_RPM(rpm);
  Set_Motor4_RPM(-rpm);
}

void moveLeft(int rpm) {

  Set_Motor1_RPM(-rpm);
  Set_Motor2_RPM(rpm);
  Set_Motor3_RPM(-rpm);
  Set_Motor4_RPM(-rpm);
}

void moveRight(int rpm) {

  Set_Motor1_RPM(rpm);
  Set_Motor2_RPM(-rpm);
  Set_Motor3_RPM(rpm);
  Set_Motor4_RPM(rpm);
  
}

void rotateCW(int rpm) {
  Set_Motor1_RPM(rpm);
  Set_Motor2_RPM(-rpm);
  Set_Motor3_RPM(-rpm);
  Set_Motor4_RPM(-rpm);
}

void rotateCCW(int rpm) {
  Set_Motor1_RPM(-rpm);
  Set_Motor2_RPM(rpm);
  Set_Motor3_RPM(rpm);
  Set_Motor4_RPM(rpm);
}
