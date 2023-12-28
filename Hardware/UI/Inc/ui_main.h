#ifndef __UI_MAIN_JAMIEXU_H_
#define __UI_MAIN_JAMIEXU_H_
#include "stm32g0xx_hal.h"
#include "ui.h"
#include "joystick.h"
#include "time.h"
#include "oled.h"
#include "stdlib.h"
#include "main.h"
#include "rtc.h"
#include "string.h"
#include "ds18b20.h"
#include "dht11.h"

// #define MENU_STYLE_NORAL
#define MENU_STYLE_IMG

void UI_Main_Initial(void);

void UI_Main_Init(void);

void UI_Main_Destroy(void);

void UI_Main_Update(void);

void UI_Main_EventCallback(void);


#endif