#include "raylib.h"

#define GRID_BOX 40
#define SNAKE_LENGTH 210

int screen_width = 600;
int screen_height = 600;

typedef struct
{
    Rectangle snake_rect;

    // Why Vector2? because we need speed in x axis and in y axis separately
    Vector2 speed;

} Snake;

Vector2 snake_prev_pos[SNAKE_LENGTH] ;

// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------
int main()
{
    InitWindow(screen_width, screen_height, "Snake");
    SetTargetFPS(60);
    int frame_cnt = 0, length = 0;
   

    // intialize snake
    Snake snake[SNAKE_LENGTH];
    snake[0].snake_rect = (Rectangle){0, 0, GRID_BOX, GRID_BOX}; // intial position of the snake rect
    snake[0].speed = (Vector2){GRID_BOX, 0};                     // the intial speed is in +ve X-axis direction

    // intialize food
    Rectangle food = {200, 200, GRID_BOX, GRID_BOX};

    while (!WindowShouldClose())
    {
        // ---------------------------------------------------------------------------------------------------------
        // Update
        // ---------------------------------------------------------------------------------------------------------
        bool collision = 0;
        frame_cnt++;

        // The key must be only "pressed" not "down"
        // which means that we only need to tab on the key, not keep it down all the movement duration
        // notice: here we only assign a value (which iss GRID_BOX) to the speed.x or speed.y
        if (IsKeyPressed(KEY_DOWN))
        {
            snake[0].speed = (Vector2){0, GRID_BOX};
        }
        if (IsKeyPressed(KEY_UP))
        {
            snake[0].speed = (Vector2){0, -GRID_BOX};
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            snake[0].speed = (Vector2){GRID_BOX, 0};
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            snake[0].speed = (Vector2){-GRID_BOX, 0};
        }

        // only move the player every 4 frames
        //  if it isn't accounted for ,the player move multiple grid boxes per frame (very fast)
        //  and not a grid box per time.
        //  why 4? just tried it and saw what's best
        // notice: here, we use the speed assigned above to actually move the snake

        //stores the previous position of the snake in an array
        for (int i = 0; i <= length; i++)
        {
            snake_prev_pos[i].x = snake[i].snake_rect.x;
            snake_prev_pos[i].y = snake[i].snake_rect.y;
        }

        //for each 4 frames, make the head move
        if (frame_cnt % 4 == 0)
        {
            // Actually move the snake with the previously stored speed
                snake[0].snake_rect.x += snake[0].speed.x;
                snake[0].snake_rect.y += snake[0].speed.y;
            for (int i = 1; i <= length; i++)
            {
                //each segment of the snake body will take the position of its previous one 
                snake[i].snake_rect.x = snake_prev_pos[i - 1].x;
                snake[i].snake_rect.y = snake_prev_pos[i - 1].y;
            }
        }

        // For a screen of size 600 x 600:
        // we need the food to be exactly on a grid box,not any random position
        // so, we randomly choose a row and a column
        // the screen width = 600 , the grid box width = 40 , so we have 15 lines
        // so we randomly choose from (0,14)
        int random_col = GetRandomValue(0, (screen_width / GRID_BOX) - 1);
        int random_row = GetRandomValue(0, (screen_height / GRID_BOX) - 1);

        // collision with food
        collision= CheckCollisionRecs(snake[0].snake_rect,food);
        if (collision)
        {
            // After we have randomly choosen a row and a col , turn these value into pixels
            // hence , we multiply by the grid dimension
            food.x = random_col * GRID_BOX;
            food.y = random_row * GRID_BOX;
            collision = 1;
            length++;
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

        
        if (collision) DrawText("COLLISION",250,0,20,BLACK);

        // Draw Player
        DrawRectangleRec(snake[0].snake_rect, BLACK);
        for (int i = 1; i <= length; i++)
        {
                DrawRectangleRec(snake[i].snake_rect, DARKBLUE);
        }

        // Draw food
        DrawRectangleRec(food, BLUE);
        DrawText(TextFormat("length %i", length), 5, 5, 20, BLACK);
       
        
        EndDrawing();
    }

    CloseWindow();
}