#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "raylib.h"

#define GRID_BOX 40
#define SNAKE_LENGTH 210

typedef struct
{
    Rectangle snake_rect;
    Vector2 speed;

} Snake;


typedef enum State
{
    start_screen = 0,
    pause_screen,
    game_over,
} State;


extern int screen_width;
extern int screen_height;

void init_game();
void snake_movement();
void food_randomization();
void collision_logic();
void draw_game();

#endif