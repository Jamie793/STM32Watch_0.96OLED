#ifndef __JOYSTICK_JAMIEXU_H_
#define __JOYSTICK_JAMIEXU_H_
#define JOYSTICK_STRENGTH_THRESHOLD 3000
#include "stm32g0xx_hal.h"
#include "gpio.h"
extern uint16_t ADC_VALUE[2];

typedef enum
{
    JOYSTICK_EVENT_NONE = 0,
    JOYSTICK_EVENT_LEFT,
    JOYSTICK_EVENT_UP,
    JOYSTICK_EVENT_RIGHT,
    JOYSTICK_EVENT_DOWN,
    JOYSTICK_EVENT_LEFT_UP,
    JOYSTICK_EVENT_RIGHT_UP,
    JOYSTICK_EVENT_LEFT_DOWN,
    JOYSTICK_EVENT_RIGHT_DOWN,
    JOYSTICK_EVENT_BTN_PUSH
} Joystick_Event;

Joystick_Event Joystick_GetEvent(void);

uint8_t Joystick_GetStrength(void);

#endif
