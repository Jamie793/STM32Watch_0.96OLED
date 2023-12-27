#include "joystick.h"

uint16_t ADC_VALUE[2];
Joystick_Event Joystick_GetEvent(void)
{
    if (ADC_VALUE[0] < 2800 && ADC_VALUE[1] > 2800 && ADC_VALUE[1] < 3200)
    {
        return JOYSTICK_EVENT_LEFT;
    }
    else if (ADC_VALUE[0] > 3200 && ADC_VALUE[1] > 2800 && ADC_VALUE[1] < 3200)
    {
        return JOYSTICK_EVENT_RIGHT;
    }
    else if (ADC_VALUE[1] < 2800 && ADC_VALUE[0] > 2800 && ADC_VALUE[0] < 3200)
    {
        return JOYSTICK_EVENT_UP;
    }
    else if (ADC_VALUE[1] > 3200 && ADC_VALUE[0] > 2800 && ADC_VALUE[0] < 3200)
    {
        return JOYSTICK_EVENT_DOWN;
    }
    else if (ADC_VALUE[0] < 2800 && ADC_VALUE[1] < 2800)
    {
        return JOYSTICK_EVENT_LEFT_UP;
    }
    else if (ADC_VALUE[0] > 3200 && ADC_VALUE[1] < 2800)
    {
        return JOYSTICK_EVENT_RIGHT_UP;
    }
    else if (ADC_VALUE[0] < 2800 && ADC_VALUE[1] > 3200)
    {
        return JOYSTICK_EVENT_LEFT_DOWN;
    }
    else if (ADC_VALUE[0] > 3200 && ADC_VALUE[1] > 3200)
    {
        return JOYSTICK_EVENT_RIGHT_DOWN;
    }
    else if (HAL_GPIO_ReadPin(JOYSTICK_BTN_GPIO_Port, JOYSTICK_BTN_Pin) != GPIO_PIN_SET)
    {
        HAL_Delay(20);
        if (HAL_GPIO_ReadPin(JOYSTICK_BTN_GPIO_Port, JOYSTICK_BTN_Pin) != GPIO_PIN_SET)
        {
            while (HAL_GPIO_ReadPin(JOYSTICK_BTN_GPIO_Port, JOYSTICK_BTN_Pin) != GPIO_PIN_SET)
                ;
            return JOYSTICK_EVENT_BTN_PUSH;
        }
    }
    return JOYSTICK_EVENT_NONE;
}

uint8_t Joystick_GetStrength(void)
{
    uint16_t n[2];
    n[0] = ADC_VALUE[0];
    n[1] = ADC_VALUE[1];
    if (n[0] > 3000)
        n[0] = -(n[0] - 3000);
    else
        n[0] = 3000 - n[0];

    if (n[1] > 3000)
        n[1] = -(n[1] - 3000);
    else
        n[1] = 3000 - n[1];

    return (n[0] + n[1]) % 2;
}
