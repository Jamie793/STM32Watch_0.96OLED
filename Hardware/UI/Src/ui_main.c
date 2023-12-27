#include "ui_main.h"
#include "ui_bitmap.h"

#if defined(MENU_STYLE_NORAL)

#define MENU_SIZE 9
#define SLID_STEP 18
char menu_list[MENU_SIZE][100] = {"Snake\0", "Cube\0", "Maze\0", "Test\0", "Test2\0", "Test3\0", "Test4\0", "Test5\0", "Test6\0"};
u8 slid_x = 40;
u32 slid_y = 8;
u8 str_s[100];
u8 menu_start_index = 0;
u8 item_current = 0;

void UI_Main_Initial(void)
{
    UI_Main.UI_Init = UI_Main_Init;
    UI_Main.UI_Destroy = UI_Main_Destroy;
    UI_Main.UI_Update = UI_Main_Update;
    UI_Main.UI_EventCallback = UI_Main_EventCallback;
}

void UI_Main_Init(void)
{
}

void UI_Main_Destroy(void)
{
}

void UI_Main_Update(void)
{
    u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
    u8g2_DrawCircle(&u8g2, slid_x, slid_y, 2, U8G2_DRAW_ALL);
    for (size_t i = menu_start_index; i < MENU_SIZE; i++)
    {
        u8g2_DrawStr(&u8g2, 50, 10 + (i - menu_start_index) * 20, menu_list[i]);
    }
}

void UI_Main_EventCallback(void)
{
    switch (Joystick_GetEvent())
    {
    case JOYSTICK_EVENT_UP:
        if (slid_y != 8)
        {
            slid_y -= SLID_STEP;
            item_current--;
        }
        else
        {
            if (menu_start_index > 0)
            {
                menu_start_index -= 1;
                item_current--;
            }
        }
        HAL_Delay(100);
        break;
    case JOYSTICK_EVENT_DOWN:
        if (slid_y < 20 * 2)
        {
            slid_y += SLID_STEP;
            item_current++;
        }
        else
        {
            if (MENU_SIZE - menu_start_index > 3)
            {
                menu_start_index += 1;
                item_current++;
            }
        }
        HAL_Delay(100);
        break;
    case JOYSTICK_EVENT_BTN_PUSH:
        if (item_current == 0)
        {
            UI_Current = &UI_Snake;
            UI_Current->UI_Init();
        }

        break;
    }
}

#elif defined(MENU_STYLE_IMG)

#define MENU_ITEM_MAX_COUNT 3
const uint8_t menu_list[MENU_ITEM_MAX_COUNT][25] = {"Snake Game", "Temperture", "Cube"};
uint8_t item_current = 0;

void UI_Main_Initial(void)
{
    UI_Main.UI_Init = UI_Main_Init;
    UI_Main.UI_Destroy = UI_Main_Destroy;
    UI_Main.UI_Update = UI_Main_Update;
    UI_Main.UI_EventCallback = UI_Main_EventCallback;
}

void UI_Main_Init(void)
{
}

void UI_Main_Destroy(void)
{
}

void UI_Main_Update(void)
{
    HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BCD);
    u8g2_SetFont(&u8g2, u8g2_font_6x10_mf);
    sprintf(led_str, "%.2d:%.2d:%.2d\0", RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
    u8g2_DrawStr(&u8g2, 0, 8, "Main Menu 33");
    u8g2_DrawStr(&u8g2, 80, 8, led_str);
    if (item_current == 1)
    {
        u8g2_SetBitmapMode(&u8g2, 0);
        u8g2_DrawXBMP(&u8g2, 128 / 2 - 15, 15, 30, 30, bitmap_menu_snake[item_current]);
        sprintf(led_str, "Temp: %.2f¡æ", RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
        u8g2_DrawStr(&u8g2, 128 / 2 - strlen(led_str) * 6 / 2, 60, led_str);
    }
    else
    {
        u8g2_SetBitmapMode(&u8g2, 0);
        u8g2_DrawXBMP(&u8g2, 128 / 2 - 15, 15, 30, 30, bitmap_menu_snake[item_current]);
        u8g2_DrawStr(&u8g2, 128 / 2 - strlen(menu_list[item_current]) * 6 / 2, 60, menu_list[item_current]);
    }
}

void UI_Main_EventCallback(void)
{
    switch (Joystick_GetEvent())
    {
    case JOYSTICK_EVENT_LEFT:
        if (item_current > 0)
            item_current--;
        HAL_Delay(100);
        break;
    case JOYSTICK_EVENT_RIGHT:
        if (item_current < MENU_ITEM_MAX_COUNT - 1)
            item_current++;
        HAL_Delay(100);
        break;
    case JOYSTICK_EVENT_BTN_PUSH:
        if (item_current == 0)
        {
            UI_Current = &UI_Snake;
            UI_Current->UI_Init();
        }

        break;
    }
}

#endif