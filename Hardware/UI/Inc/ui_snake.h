#ifndef __SNAKE_JAMIEXU_H_
#define __SNAKE_JAMIEXU_H_
#include "stm32g0xx_hal.h"
#include "ui.h"
#include "joystick.h"
#include "game_snake.h"
#include "stdlib.h"

void UI_Snake_Initial(void);

void UI_Snake_Init(void);

void UI_Snake_Destroy(void);

void UI_Snake_Update(void);

void UI_Snake_EventCallback(void);

#endif
