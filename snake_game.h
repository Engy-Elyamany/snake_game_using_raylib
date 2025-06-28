#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "raylib.h"

#define GRID_BOX 40
#define SNAKE_LENGTH 210

#define BG_COLOR BLACK
#define START_TITLE_TEXT GREEN
#define GAME_PAUSED_TEXT YELLOW
#define SCORE_TEXT GREEN
#define GAME_OVER_TEXT RED
#define SEC_TEXT RAYWHITE
#define GRID_COLOR LIGHTGRAY
#define SNAKE_HEAD_COLOR GREEN
#define SNAKE_BODY_COLOR LIME
#define FOOD_COLOR RED

typedef struct
{
    Rectangle snake_rect;
    Vector2 speed;

} Snake;


typedef enum State
{
    start_screen = 0,
    game_play,
    pause_screen,
    game_over,
} State;


extern int screen_width;
extern int screen_height;

void execute();
void handle_game_state();
void init_game();
void snake_movement();
void food_randomization();
void collision_logic();
void draw_game();
void losing_logic();
#endif