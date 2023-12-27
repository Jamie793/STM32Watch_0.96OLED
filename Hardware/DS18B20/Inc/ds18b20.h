#ifndef __DS18B20_JAMIEXU_H_
#define __DS18B20_JAMIEXU_H_
#include "stm32g0xx_hal.h"
#include "stdlib.h"
#include "rtc.h"
#include "main.h"



extern uint8_t Ds18b20_Temp_m;

extern uint8_t Ds18b20_Temp_l;

void Ds18b20_Init(void);

void Ds18b20_Rest(void);

void Ds18b20_WriteByte(uint8_t data);

uint8_t Ds18b20_ReadByte(void);

void Ds18b20_Configure(void);

void Ds18b20_ReadBytes(uint8_t size);

uint8_t Ds18b20_Crc(uint8_t size);

void Ds18b20_GetTemperture(void);

#endif