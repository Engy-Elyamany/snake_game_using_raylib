#include "raylib.h"

#define GRID_BOX 40
#define SPD 200
#define SNAKE_LENGTH 210

int screen_width = 600;
int screen_height = 600;

int main()
{
    InitWindow(screen_width, screen_height, "Snake");
    SetTargetFPS(60);
    int frame_cnt = 0, collision = 0, length = 0, i = 1;

    // intialize snake
    Rectangle snake[SNAKE_LENGTH];
    snake[0].x = 0;
    snake[0].y = 0;
    snake[0].width = 40;
    snake[0].height = 40;

    // intialize food
    Rectangle food = {
        200,200,
        GRID_BOX,
        GRID_BOX};


    while (!WindowShouldClose())
    {
        
// ---------------------------------------------------------------------------------------------------------
// Update
// ---------------------------------------------------------------------------------------------------------

        frame_cnt++;

        // check is the desired key pressed and only move the player every 4 frames
        // if the second condition isn't accounted for ,
        //  the player move multiple grid boxes per frame (very fast) and not a grid box per time.
        // why 4? just tried it and saw what's best
        if (IsKeyDown(KEY_DOWN) && (frame_cnt % 4 == 0))
        {
            snake[0].y += GRID_BOX;
        }
        if (IsKeyDown(KEY_UP) && (frame_cnt % 4 == 0))
        {
            snake[0].y -= GRID_BOX;
        }

        if (IsKeyDown(KEY_RIGHT) && (frame_cnt % 4 == 0))
        {
            snake[0].x += GRID_BOX;
        }

        if (IsKeyDown(KEY_LEFT) && (frame_cnt % 4 == 0))
        {
            snake[0].x -= GRID_BOX;
        }

        
        // For a screen of size 600 x 600:
        // we need the food to be exactly on a grid box,not any random GetMousePosition
        // so, we randomly choose a row and a column
        // the screen width = 600 , the grid box width = 40 , so we have 15 lines 
        // so we randomly choose from (0,14)
        int random_col = GetRandomValue(0, (screen_width / GRID_BOX) - 1);
        int random_row = GetRandomValue(0, (screen_height / GRID_BOX) - 1);

        // collision with food
        collision = CheckCollisionRecs(snake[0], food);
        if (collision)
        {
            length++;

            //After we have random;y choosen a row and a col , turn these value into pixels
            //hence , we multiply by yhe grid dimension
            food.x = (random_col + 1) * GRID_BOX;
            food.y = (random_row + 1) * GRID_BOX;
            collision = 0;
        }

// ---------------------------------------------------------------------------------------------------------
// Drawing
// ---------------------------------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        // Draw Grid
        for (int i = 0; i < screen_height; i += GRID_BOX)
        {

            DrawLineV((Vector2){0, i}, (Vector2){screen_width, i}, GRAY);
        }
        for (int i = 0; i < screen_width; i += GRID_BOX)
        {

            DrawLineV((Vector2){i, 0}, (Vector2){i, screen_height}, GRAY);
        }

        // Draw Player
        DrawRectangleRec(snake[0], BLACK);

        // Draw food
        DrawRectangleRec(food, BLUE);
        DrawText(TextFormat("length %i",length),5,5,20,BLACK);
        EndDrawing();
    }

    CloseWindow();
}