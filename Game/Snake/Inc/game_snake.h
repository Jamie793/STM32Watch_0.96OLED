#ifndef __GAME_SNAKE_JAMIEXU_H_
#define __GAME_SNAKE_JAMIEXU_H_
#include "stm32g0xx_hal.h"
#include "stdlib.h"
#include "rtc.h"
#include "main.h"

#define SNAKE_STEP 6
#define SNAKE_MAX_LENGTH 100

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t last_x;
    int16_t last_y;
} Point;

typedef struct
{
    Point *points;
    uint8_t length;

    uint8_t current_direction;
    Point snack;

    uint8_t game_status;
    uint8_t game_score;

} Game_Snake;

void Game_Snake_Init(Game_Snake *snake);

void Game_Snake_Update(Game_Snake *snake);

void Game_Snake_Eaten(Game_Snake *snake);

uint8_t Game_Snake_Colliding(Point p1, Point p2);

void Game_Snake_Append(Game_Snake *snake, uint8_t x, uint8_t y);

void Game_Snake_Generate(Game_Snake *snake);

#endif
