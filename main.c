#include "snake_game.h"
int main()
{
    InitWindow(screen_width, screen_height, "Snake");
    SetTargetFPS(60);

    init_game();

    while (!WindowShouldClose())
    {
        handle_game_state();
        draw_game();
    }

    CloseWindow();
}
