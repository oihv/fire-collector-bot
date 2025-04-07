#include "CH452.h"

#define I2C_SCL_High() GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define I2C_SCL_Low() GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define I2C_SDA_High() GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define I2C_SDA_Low() GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define I2C_SDA_READ() (PBout(7) = 1, PBin(7))
#define I2C_Delay() delay_us(2)
static void I2C_Start() {
  I2C_SDA_High();
  I2C_SCL_High();
  I2C_Delay();
  I2C_SDA_Low();
  I2C_Delay();
  I2C_SCL_Low();
  I2C_Delay();
}
static void I2C_Stop() {
  I2C_SDA_Low();
  I2C_SCL_High();
  I2C_Delay();
  I2C_SDA_High();
  I2C_Delay();
}
static void I2C_SendByte(u8 Byte) {
  for (u8 i = 0; i < 8; i++) {
    if (Byte & 0x80)
      I2C_SDA_High();
    else
      I2C_SDA_Low();
    I2C_Delay();
    I2C_SCL_High();
    I2C_Delay();
    I2C_SCL_Low();
    I2C_Delay();
    Byte <<= 1;
  }
}
static u8 I2C_ReadByte() {
  u8 value = 0;
  I2C_SDA_READ();
  for (u8 i = 0; i < 8; i++) {
    value <<= 1;
    I2C_SCL_High();
    I2C_Delay();
    if (I2C_SDA_READ())
      value++;
    I2C_SCL_Low();
    I2C_Delay();
  }
  return value;
}
static void I2C_WaitToAck() {
  I2C_SDA_READ();
  I2C_Delay();
  I2C_SCL_High();
  I2C_Delay();
  for (u8 i = 0; i < 250; i++) {
    if (I2C_SDA_READ() == 0)
      break;
    I2C_Delay();
  }
  I2C_SCL_Low();
  I2C_Delay();
}
static void CH452_Write(u8 h, u8 b) {
  // 011  B11B10B9B8  W0R1  7-0
  // 011  0  1  0 0   0     0x03
  I2C_Start();
  I2C_SendByte(0x60 | ((h & 0x0f) << 1));
  I2C_WaitToAck();
  I2C_SendByte(b);
  I2C_WaitToAck();
  I2C_Stop();
}
// CH452键盘初始化
void CH452_Init() {
  GPIO_InitTypeDef gpio;
  gpio.GPIO_Mode = GPIO_Mode_Out_OD;
  gpio.GPIO_Speed = GPIO_Speed_50MHz;
  gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_Init(GPIOB, &gpio);
  I2C_SCL_High();
  I2C_SDA_High();
  delay_ms(1);
  CH452_Write(0x07, 0x00); // 使能IIC应答
  CH452_Write(0x04, 0x03); // 使能显示和键盘功能
}
// 清除显示
void CH452_Clear() {
  for (u8 i = 0; i < 8; i++)
    CH452_Write(0x08 + i, 0x00);
}
// 在指定位置显示一位数
// i:0~7对应最左~最右
// n:低4位为要显的十六进制数,最高位1和0表示点亮和熄灭小数点
// 示例:n为0x0B显示"b",n为0x89显示"9."
void CH452_SetDigit(u8 i, u8 n) {
  static const u8 bcd_table[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
                                   0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C,
                                   0x39, 0x5E, 0x79, 0x71};
  i = (11 - i) % 8;
  n = bcd_table[n & 0xF] + (n & 0x80);
  CH452_Write(0x08 + i, n);
}
// 在指定位置显示任意字符
// i:0~7对应最左~最右
// n:低位到高位对应数码管的A-G段和小数点
// 示例:n为0x83显示"1.",n为0x76显示"H"
void CH452_SetRam(u8 i, u8 n) {
  i = (11 - i) % 8;
  CH452_Write(0x08 + i, n);
}
// 读取键盘按下键的编号
// A,B,C,D对应10-13
//*对应14;#对应15
// 没有按键按下返回16
u8 CH452_GetKey(void) {
  I2C_Start();
  I2C_SendByte(0x6F);
  I2C_WaitToAck();
  u8 ret = I2C_ReadByte();
  I2C_Stop();
  switch (ret) {
  case 0x4A:
    return 0;
  case 0x47:
    return 1;
  case 0x46:
    return 2;
  case 0x45:
    return 3;
  case 0x43:
    return 4;
  case 0x42:
    return 5;
  case 0x41:
    return 6;
  case 0x4F:
    return 7;
  case 0x4E:
    return 8;
  case 0x4D:
    return 9;
  case 0x44:
    return 10;
  case 0x40:
    return 11;
  case 0x4C:
    return 12;
  case 0x48:
    return 13;
  case 0x4B:
    return 14;
  case 0x49:
    return 15;
  }
  return 16;
}
