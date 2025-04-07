#include "Bsp.h"
#include "pid.h"

void moveForward(int rpm);
void moveBackward(int rpm);
void moveLeft(int rpm);
void moveRight(int rpm);
void rotateCW(int rpm);
void rotateCCW(int rpm);
void stopMotor(int rpm);