#include "ui_snake.h"

Game_Snake game_snake;
char snake_str[100];
void UI_Snake_Initial(void)
{
    UI_Snake.UI_Init = UI_Snake_Init;
    UI_Snake.UI_Destroy = UI_Snake_Destroy;
    UI_Snake.UI_Update = UI_Snake_Update;
    UI_Snake.UI_EventCallback = UI_Snake_EventCallback;
}

void UI_Snake_Init(void)
{
    Game_Snake_Init(&game_snake);
}

void UI_Snake_Destroy(void)
{
    // free(&game_snake->points);
}

void UI_Snake_Update(void)
{
    if (game_snake.game_status == 0)
    {
        u8g2_SetFont(&u8g2, u8g2_font_8x13_tr);
        u8g2_DrawStr(&u8g2, 20, 20, "Press any key");
        u8g2_DrawStr(&u8g2, 20, 40, "to start!");
    }
    else if (game_snake.game_status == 1)
    {
        Game_Snake_Update(&game_snake);
        for (size_t i = 0; i < game_snake.length; i++)
        {
            u8g2_DrawBox(&u8g2, game_snake.points[i].x, game_snake.points[i].y, 6, 6);
        }
        u8g2_DrawBox(&u8g2, game_snake.snack.x, game_snake.snack.y, 6, 6);
        u8g2_SetFont(&u8g2, u8g2_font_6x10_mf);
        sprintf(snake_str, "score: %d\0", game_snake.game_score);
        u8g2_DrawStr(&u8g2, 6, 10, snake_str);
    }
    else if (game_snake.game_status == 2)
    {
        u8g2_SetFont(&u8g2, u8g2_font_8x13_tr);
        u8g2_DrawStr(&u8g2, 30, 30, "Game Over!");
        sprintf(snake_str, "your score: %d\0", game_snake.game_score);
        u8g2_DrawStr(&u8g2, 10, 50, snake_str);
        HAL_Delay(1000);
    }
}

void UI_Snake_EventCallback(void)
{
    if (game_snake.game_status == 0)
    {
        if (Joystick_GetEvent() != JOYSTICK_EVENT_NONE)
        {
            game_snake.game_status = 1;
            game_snake.game_score = 0;
            game_snake.length = 0;
            Game_Snake_Generate(&game_snake);
            Game_Snake_Append(&game_snake, 60, 60);
            Game_Snake_Append(&game_snake, 200, 200);
        }
    }
    else if (game_snake.game_status == 1)
    {
        if (Joystick_GetEvent() == JOYSTICK_EVENT_LEFT)
        {
            if (game_snake.current_direction != 2)
                game_snake.current_direction = 0;
        }
        else if (Joystick_GetEvent() == JOYSTICK_EVENT_UP)
        {
            if (game_snake.current_direction != 3)
                game_snake.current_direction = 1;
        }
        else if (Joystick_GetEvent() == JOYSTICK_EVENT_RIGHT)
        {
            if (game_snake.current_direction != 0)
                game_snake.current_direction = 2;
        }
        else if (Joystick_GetEvent() == JOYSTICK_EVENT_DOWN)
        {
            if (game_snake.current_direction != 1)
                game_snake.current_direction = 3;
        }
    }
    else if (game_snake.game_status == 2)
    {
        if (Joystick_GetEvent() != JOYSTICK_EVENT_NONE)
        {
            game_snake.game_status = 1;
            game_snake.game_score = 0;
            game_snake.length = 0;
            Game_Snake_Generate(&game_snake);
            Game_Snake_Append(&game_snake, 60, 60);
            Game_Snake_Append(&game_snake, 200, 200);
        }
    }
}
