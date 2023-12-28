#ifndef __DHT11_JAMIEXU_H_
#define __DHT11_JAMIEXU_H_
#include "main.h"
#include "stm32g0xx_hal.h"

extern uint8_t DHT11_Integral;

extern uint8_t DHT11_Decimal;

void DHT11_Start(void);

uint8_t DHT11_Crc(void);

uint8_t DHT11_Read(void);

void DHT11_GetHumidity(void);

#endif