#ifndef __PID_H
#define __PID_H

#include "Bsp.h"
#include <stdint.h>

uint8_t sensor[7];

int balance_UP(float Angle, float Mechanical_balance, float Gyro);
void readGreyscale();
int PID(int EEROR);

#endif
