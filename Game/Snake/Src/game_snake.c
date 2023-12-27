#include "game_snake.h"

int8_t direction[4][2] = {{-SNAKE_STEP, 0}, {0, -SNAKE_STEP}, {SNAKE_STEP, 0}, {0, SNAKE_STEP}};

void Game_Snake_Init(Game_Snake *snake)
{
    snake->points = (Point *)malloc(snake->length * sizeof(Point));
    snake->length = 0;
    snake->game_status = 0;
    snake->game_score = 0;
    snake->current_direction = 0;
}

void Game_Snake_Update(Game_Snake *snake)
{

    snake->points[0].last_x = snake->points[0].x;
    snake->points[0].last_y = snake->points[0].y;
    
    snake->points[0].x += direction[snake->current_direction][0];
    snake->points[0].y += direction[snake->current_direction][1];

    if (snake->points[0].x <= 0)
        snake->points[0].x = 128;
    else if (snake->points[0].x >= 128)
        snake->points[0].x = 0;

    if (snake->points[0].y <= 12)
        snake->points[0].y = 64;
    else if (snake->points[0].y >= 64)
        snake->points[0].y = 13;

    for (uint8_t i = 1; i < snake->length; i++)
    {
        snake->points[i].last_x = snake->points[i].x;
        snake->points[i].last_y = snake->points[i].y;

        snake->points[i].x = snake->points[i - 1].last_x;
        snake->points[i].y = snake->points[i - 1].last_y;
    }

    for (uint8_t i = 0; i < snake->length; i++)
    {
        if (i < 5)
            continue;
        if (Game_Snake_Colliding(snake->points[0], snake->points[i]))
        {
            snake->game_status = 2;
        }
    }

    Game_Snake_Eaten(snake);
    HAL_Delay(80);
}

void Game_Snake_Eaten(Game_Snake *snake)
{
    if (Game_Snake_Colliding(snake->points[0], snake->snack))
    {
        snake->game_score++;
        Game_Snake_Append(snake, 200, 200);
        Game_Snake_Generate(snake);
    }
}

uint8_t Game_Snake_Colliding(Point p1, Point p2)
{
    uint8_t left1 = p1.x;
    uint8_t right1 = p1.x + 6;
    uint8_t top1 = p1.y;
    uint8_t bottom1 = p1.y + 6;

    uint8_t left2 = p2.x;
    uint8_t right2 = p2.x + 6;
    uint8_t top2 = p2.y;
    uint8_t bottom2 = p2.y + 6;

    uint8_t horizontalCollision = (right1 >= left2) && (left1 <= right2);

    uint8_t verticalCollision = (bottom1 >= top2) && (top1 <= bottom2);

    return horizontalCollision && verticalCollision;
}

void Game_Snake_Append(Game_Snake *snake, uint8_t x, uint8_t y)
{
    if (snake->length >= SNAKE_MAX_LENGTH)
        return;
    snake->points[snake->length].x = x;
    snake->points[snake->length].y = y;
    snake->length++;
}

void Game_Snake_Generate(Game_Snake *snake)
{
    srand(HAL_GetTick());
    snake->snack.x = (rand() % (120 - 15) + 15);
    snake->snack.y = (rand() % (60 - 20) + 20);
}