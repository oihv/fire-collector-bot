#include "pid.h"
#include "Bsp.h"

// TODO: look up how this function can be implemented and utilized
int balance_UP(float Angle, float Mechanical_balance, float Gyro) {}

// The sensors we are using is from IO1-IO7
void readGreyscale() {
  sensor[0] = Read_IO1;
  sensor[1] = Read_IO2;
  sensor[2] = Read_IO3;
  sensor[3] = Read_IO4;
  sensor[4] = Read_IO5;
  sensor[5] = Read_IO6;
  sensor[6] = Read_IO7;
}

// TODO: check the algorithm
// TODO: implement fuzzy PID ???
int PID(int EEROR) {
  int sensor_average = 0;
  int sensor_sum = 0;
  static int p = 0;
  int i = 0;
  static int d = 0;
  static int lp = 0;
  int Kp = 5;
  int Ki = 0;
  int Kd = 40; // (Kp-1) * 10
  int pos = 0;
  int error = 0;
  int sp = 0;
  int correction = 0;

  readGreyscale();
  for (int i = -3; i <= 3; i++) {
    sensor_average = sensor[i + 3] * i * 1000; // weighted mean
    sensor_sum += sensor[i + 3];
  }

  pos = (int)(sensor_average / sensor_sum);

  error = pos - sp;

  p = error;
  i += p;
  d = p - lp;

  lp = p;

  return correction = (int)(Kp * p + Ki * i + Kd * d);
}
