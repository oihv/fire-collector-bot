#ifndef __MPU6050_H
#define __MPU6050_H
#include "Bsp.h"
//////////////////////////////////////////////////////////////////////////////////
// This program is for educational purposes only and is not authorized for any
// other use without the author's permission.
//
// ALIENTEK STM32F407 Development Board
// MPU6050 Driver Code
// Author: ALIENTEK
// Technical Forum: www.openedv.com
// Creation Date: 2014/5/9
// Version: V1.0
// All rights reserved. Unauthorized reproduction is prohibited.
// Copyright (C) GuangZhou XingYin Electronics Technology Co., Ltd. 2014-2024
//////////////////////////////////////////////////////////////////////////////////

// #define MPU_ACCEL_OFFS_REG 0X06
// // Accelerometer offset register, can read version number, not mentioned in
// the register manual #define MPU_PROD_ID_REG 0X0C
// // Product ID register, not mentioned in the register manual
#define MPU_SELF_TESTX_REG 0X0D   // Self-test register X
#define MPU_SELF_TESTY_REG 0X0E   // Self-test register Y
#define MPU_SELF_TESTZ_REG 0X0F   // Self-test register Z
#define MPU_SELF_TESTA_REG 0X10   // Self-test register A
#define MPU_SAMPLE_RATE_REG 0X19  // Sample rate divider
#define MPU_CFG_REG 0X1A          // Configuration register
#define MPU_GYRO_CFG_REG 0X1B     // Gyroscope configuration register
#define MPU_ACCEL_CFG_REG 0X1C    // Accelerometer configuration register
#define MPU_MOTION_DET_REG 0X1F   // Motion detection threshold setting register
#define MPU_FIFO_EN_REG 0X23      // FIFO enable register
#define MPU_I2CMST_CTRL_REG 0X24  // I2C master control register
#define MPU_I2CSLV0_ADDR_REG 0X25 // I2C slave 0 device address register
#define MPU_I2CSLV0_REG 0X26      // I2C slave 0 data address register
#define MPU_I2CSLV0_CTRL_REG 0X27 // I2C slave 0 control register
#define MPU_I2CSLV1_ADDR_REG 0X28 // I2C slave 1 device address register
#define MPU_I2CSLV1_REG 0X29      // I2C slave 1 data address register
#define MPU_I2CSLV1_CTRL_REG 0X2A // I2C slave 1 control register
#define MPU_I2CSLV2_ADDR_REG 0X2B // I2C slave 2 device address register
#define MPU_I2CSLV2_REG 0X2C      // I2C slave 2 data address register
#define MPU_I2CSLV2_CTRL_REG 0X2D // I2C slave 2 control register
#define MPU_I2CSLV3_ADDR_REG 0X2E // I2C slave 3 device address register
#define MPU_I2CSLV3_REG 0X2F      // I2C slave 3 data address register
#define MPU_I2CSLV3_CTRL_REG 0X30 // I2C slave 3 control register
#define MPU_I2CSLV4_ADDR_REG 0X31 // I2C slave 4 device address register
#define MPU_I2CSLV4_REG 0X32      // I2C slave 4 data address register
#define MPU_I2CSLV4_DO_REG 0X33   // I2C slave 4 write data register
#define MPU_I2CSLV4_CTRL_REG 0X34 // I2C slave 4 control register
#define MPU_I2CSLV4_DI_REG 0X35   // I2C slave 4 read data register

#define MPU_I2CMST_STA_REG 0X36 // I2C master status register
#define MPU_INTBP_CFG_REG 0X37  // Interrupt/pin configuration register
#define MPU_INT_EN_REG 0X38     // Interrupt enable register
#define MPU_INT_STA_REG 0X3A    // Interrupt status register

#define MPU_ACCEL_XOUTH_REG                                                    \
  0X3B // Accelerometer value, X-axis high 8 bits register
#define MPU_ACCEL_XOUTL_REG                                                    \
  0X3C // Accelerometer value, X-axis low 8 bits register
#define MPU_ACCEL_YOUTH_REG                                                    \
  0X3D // Accelerometer value, Y-axis high 8 bits register
#define MPU_ACCEL_YOUTL_REG                                                    \
  0X3E // Accelerometer value, Y-axis low 8 bits register
#define MPU_ACCEL_ZOUTH_REG                                                    \
  0X3F // Accelerometer value, Z-axis high 8 bits register
#define MPU_ACCEL_ZOUTL_REG                                                    \
  0X40 // Accelerometer value, Z-axis low 8 bits register

#define MPU_TEMP_OUTH_REG 0X41 // Temperature value high 8 bits register
#define MPU_TEMP_OUTL_REG 0X42 // Temperature value low 8 bits register

#define MPU_GYRO_XOUTH_REG 0X43 // Gyroscope value, X-axis high 8 bits register
#define MPU_GYRO_XOUTL_REG 0X44 // Gyroscope value, X-axis low 8 bits register
#define MPU_GYRO_YOUTH_REG 0X45 // Gyroscope value, Y-axis high 8 bits register
#define MPU_GYRO_YOUTL_REG 0X46 // Gyroscope value, Y-axis low 8 bits register
#define MPU_GYRO_ZOUTH_REG 0X47 // Gyroscope value, Z-axis high 8 bits register
#define MPU_GYRO_ZOUTL_REG 0X48 // Gyroscope value, Z-axis low 8 bits register

#define MPU_I2CSLV0_DO_REG 0X63 // I2C slave 0 data register
#define MPU_I2CSLV1_DO_REG 0X64 // I2C slave 1 data register
#define MPU_I2CSLV2_DO_REG 0X65 // I2C slave 2 data register
#define MPU_I2CSLV3_DO_REG 0X66 // I2C slave 3 data register

#define MPU_I2CMST_DELAY_REG 0X67 // I2C master delay management register
#define MPU_SIGPATH_RST_REG 0X68  // Signal path reset register
#define MPU_MDETECT_CTRL_REG 0X69 // Motion detection control register
#define MPU_USER_CTRL_REG 0X6A    // User control register
#define MPU_PWR_MGMT1_REG 0X6B    // Power management register 1
#define MPU_PWR_MGMT2_REG 0X6C    // Power management register 2
#define MPU_FIFO_CNTH_REG 0X72    // FIFO counter high 8 bits register
#define MPU_FIFO_CNTL_REG 0X73    // FIFO counter low 8 bits register
#define MPU_FIFO_RW_REG 0X74      // FIFO read/write register
#define MPU_DEVICE_ID_REG 0X75    // Device ID register

// If AD0 pin (pin 9) is connected to GND, I2C address is 0X68 (excluding the
// lowest bit). If connected to V3.3, I2C address is 0X69 (excluding the lowest
// bit).
#define MPU_ADDR 0X68

//// Since the development board connects AD0 to GND, the read/write address
/// becomes 0XD1 and 0XD0 / (If connected to GND, it becomes 0XD3 and 0XD2)
// #define MPU_READ    0XD1
// #define MPU_WRITE   0XD0

u8 MPU_Init(void);                                  // Initialize MPU6050
u8 MPU_Write_Len(u8 addr, u8 reg, u8 len, u8 *buf); // I2C continuous write
u8 MPU_Read_Len(u8 addr, u8 reg, u8 len, u8 *buf);  // I2C continuous read
u8 MPU_Write_Byte(u8 reg, u8 data);                 // I2C write a single byte
u8 MPU_Read_Byte(u8 reg);                           // I2C read a single byte

u8 MPU_Set_Gyro_Fsr(u8 fsr);  // Set gyroscope full-scale range
u8 MPU_Set_Accel_Fsr(u8 fsr); // Set accelerometer full-scale range
u8 MPU_Set_LPF(u16 lpf);      // Set digital low-pass filter
u8 MPU_Set_Rate(u16 rate);    // Set sampling rate
u8 MPU_Set_Fifo(u8 sens);     // Set FIFO

float MPU_Get_Temperature(void);                       // Get temperature value
u8 MPU_Get_Gyroscope(short *gx, short *gy, short *gz); // Get gyroscope values
u8 MPU_Get_Accelerometer(short *ax, short *ay,
                         short *az); // Get accelerometer values

#endif
