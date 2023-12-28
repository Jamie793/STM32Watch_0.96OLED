#ifndef __UI_JAMIEXU_H_
#define __UI_JAMIEXU_H_
#include "stm32g0xx_hal.h"
#include "stdlib.h"
#include "u8g2.h"
#include "joystick.h"



typedef struct{
    void (*UI_Init)(void);
    void (*UI_Destroy)(void);
    void (*UI_Update)(void);
    void (*UI_EventCallback)(void);
}UI_InitType;

extern u8g2_t u8g2;
extern UI_InitType *UI_Current;
extern UI_InitType UI_Main, UI_Snake;

void UI_Init(void);

void UI_Update(void);

void UI_EventCallback(void);

#endif
