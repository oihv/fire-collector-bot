#pragma once
#include "bsp.h"

void CH452_Init(void);
void CH452_Clear(void);
void CH452_SetDigit(u8 i,u8 n);
void CH452_SetRam(u8 i,u8 n);
u8 CH452_GetKey(void);

