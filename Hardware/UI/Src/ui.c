#include "ui.h"

UI_InitType *UI_Current;
UI_InitType UI_Main, UI_Snake;
uint32_t counter = 0;

void UI_Init(void)
{
    UI_Main_Initial();
    UI_Snake_Initial();
    UI_Current = &UI_Main;
    UI_Current->UI_Init();
}

void UI_Update(void)
{
    u8g2_ClearBuffer(&u8g2);
    UI_Current->UI_Update();
    u8g2_SendBuffer(&u8g2);
}

void UI_EventCallback(void)
{
    UI_Current->UI_EventCallback();
}