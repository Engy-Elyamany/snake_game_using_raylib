#include "raylib.h"
#include "snake_game.h"

int screen_width = 800;
int screen_height = 600;
static int frame_cnt = 0, length = 0;
static bool valid_food_pos = 1;

// intialize snake
static Snake snake[SNAKE_LENGTH];
Vector2 snake_prev_pos[SNAKE_LENGTH];
static Rectangle food;
State game_state = start_screen;

void execute()
{
    snake_movement();
    food_randomization();
    collision_logic();
    losing_logic();
}

void handle_game_state()
{
    switch (game_state)
    {
    case start_screen:
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            game_state = game_play;
        }
    }
    break;

    case game_play:
    {
        if (IsKeyPressed(KEY_P))
        {
            game_state = pause_screen;
        }
        else
        {
            execute();
            if (game_state == game_over)
            {
                game_state = game_over;
            }
        }
    }
    break;
    case pause_screen:
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            game_state = game_play;
        }
    }
    break;

    case game_over:
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            init_game();
            
            game_state = game_play;
        }
    }
    break;
    default:
        break;
    }
}

void init_game()
{
    length = 0;
    frame_cnt = 0;
    valid_food_pos = 1;
    // here we intialize all segments of the snake body to be able to store them in the first place
    //  Then , we use these stored positions to create the flow of the tail
    //  each 4 frames, we move the head with the stored speed and update the segments accordingly
    for (int i = 0; i < SNAKE_LENGTH; i++)
    {
        // -(i*GRID_BOX) to intialize x coordinate of each segment right behind its previous one
        snake[i].snake_rect = (Rectangle){GRID_BOX - (i * GRID_BOX), GRID_BOX, GRID_BOX, GRID_BOX};
    }
    snake[0].speed = (Vector2){GRID_BOX, 0}; // the intial speed is in +ve X-axis direction

    // intialize food
    food = (Rectangle){(GetRandomValue(2, (screen_width / GRID_BOX) - 3)) * GRID_BOX,
                (GetRandomValue(2, (screen_height / GRID_BOX) - 3)) * GRID_BOX,
                       GRID_BOX,
                       GRID_BOX};

    game_state = start_screen;
}

void snake_movement()
{
    frame_cnt++;

    // The key must be only "pressed" not "down"
    // which means that we only need to tab on the key, not keep it down all the movement duration
    // notice: here we only assign a value (which iss GRID_BOX) to the speed.x or speed.y

    // To prevent the 180-deg turn (moves left while it's moving right):
    //     we check if the key is pressed as well as if the speed is zero
    //     if KEY_DOWN is pressed and speed.y is zero => move down
    //     because speed.y is only zero if the head is moving right or left
    //     so this condition would become false if the head is moving up
    //     that way we prevent it from moving doen while it's moving up

    if (IsKeyPressed(KEY_DOWN) && (snake[0].speed.y == 0))
    {
        snake[0].speed = (Vector2){0, GRID_BOX};
    }
    if (IsKeyPressed(KEY_UP) && (snake[0].speed.y == 0))
    {
        snake[0].speed = (Vector2){0, -GRID_BOX};
    }
    if (IsKeyPressed(KEY_RIGHT) && (snake[0].speed.x == 0))
    {
        snake[0].speed = (Vector2){GRID_BOX, 0};
    }
    if (IsKeyPressed(KEY_LEFT) && (snake[0].speed.x == 0))
    {
        snake[0].speed = (Vector2){-GRID_BOX, 0};
    }

    // only move the player every 4 frames
    //  if it isn't accounted for ,the player move multiple grid boxes per frame (very fast)
    //  and not a grid box per time.
    //  why 4? just tried it and saw what's best
    // notice: here, we use the speed assigned above to actually move the snake

    // stores the previous position of the snake in an array
    for (int i = 0; i <= length; i++)
    {
        snake_prev_pos[i].x = snake[i].snake_rect.x;
        snake_prev_pos[i].y = snake[i].snake_rect.y;
    }

    // for each 4 frames, move the snake and position its body segments
    if (frame_cnt % 4 == 0)
    {
        // Actually move the snake with the previously stored speed
        snake[0].snake_rect.x += snake[0].speed.x;
        snake[0].snake_rect.y += snake[0].speed.y;
        for (int i = 1; i <= length; i++)
        {
            // each segment of the snake body will take the position of its previous one
            snake[i].snake_rect.x = snake_prev_pos[i - 1].x;
            snake[i].snake_rect.y = snake_prev_pos[i - 1].y;
        }
    }
}

void food_randomization()
{

    // Randomize food
    if (!valid_food_pos)
    {

        // For a screen of size 600 x 600:
        // we need the food to be exactly on a grid box,not any random position
        // so, we randomly choose a row and a column :
        //  int random_col = GetRandomValue(0, (screen_width / GRID_BOX) - 1);
        // int random_row = GetRandomValue(0, (screen_height / GRID_BOX) - 1);
        // the screen width = 600 , the grid box width = 40 , so we have 15 lines
        // so we randomly choose from (0,14)
        // After we have randomly choosen a row and a col , turn these value into pixels
        // hence , we multiply by the grid dimension

       food.x = (GetRandomValue(2, (screen_width / GRID_BOX) - 3)) * GRID_BOX;
                food.y = (GetRandomValue(2, (screen_height / GRID_BOX) - 3)) * GRID_BOX;

        // here we checks if the food.x equals the head's x (snake[0]):
        // if true, generate new coordinates and recheck with the head's x (snake[0])
        // if false, then check with the next segment of the snake (snake[1])
        // and so on for the whole length of the snake
        int i = 0;
        while (i < length)
        {
            if ((food.x == snake[i].snake_rect.x) && (food.y == snake[i].snake_rect.y))
            {
                food.x = (GetRandomValue(2, (screen_width / GRID_BOX) - 3)) * GRID_BOX;
                food.y = (GetRandomValue(2, (screen_height / GRID_BOX) - 3)) * GRID_BOX;
                i = 0;
            }
            else
            {
                i++;
            }
        }

        // This became true, because at where we are now,
        //  we have a good position for food where no intersection with the body occurs
        valid_food_pos = 1;
    }
}

void collision_logic()
{
    // collision with food
    bool collision = CheckCollisionRecs(snake[0].snake_rect, food);
    if (collision)
    {
        // false, because we want to check first for a good food position
        valid_food_pos = 0;
        length++;
    }
}

void losing_logic()
{
    // The snake eats itself
    for (int i = 1; i <= length; i++)
    {
        if ((snake[0].snake_rect.x == snake[i].snake_rect.x) && (snake[0].snake_rect.y == snake[i].snake_rect.y))
        {
            game_state = game_over;
        }
    }

    // snake hit the border of the play field
    if (
        (snake[0].snake_rect.x + snake[0].snake_rect.width > screen_width - GRID_BOX) ||
        (snake[0].snake_rect.x < GRID_BOX) ||
        (snake[0].snake_rect.y + snake[0].snake_rect.height > screen_height - GRID_BOX) ||
        (snake[0].snake_rect.y < GRID_BOX))
    {
        game_state = game_over;
    }
}

void draw_game()
{
    BeginDrawing();
    ClearBackground(BG_COLOR);

    switch (game_state)
    {
    case start_screen:
    {
        DrawText("SNAKE GAME",(screen_width - MeasureText("Game Paused", 40)) / 2, 200, 40, START_TITLE_TEXT);
        DrawText("Press ENTER To Start",  (screen_width - MeasureText("Press ENTER To Start", 20)) / 2, 270, 20, SEC_TEXT);
    }
    break;

    case game_play:
    {
        // Draw Grid - here we are iterating using i as cols and rows not pixels
        // vertical lines
        for (int i = 1; i < screen_height / GRID_BOX; i++)
        {

            DrawLineV((Vector2){1 * GRID_BOX, i * GRID_BOX}, (Vector2){(screen_width - GRID_BOX), i * GRID_BOX}, GRID_COLOR);
        }
        // Horizontal
        for (int i = 1; i < screen_width / GRID_BOX; i++)
        {

            DrawLineV((Vector2){i * GRID_BOX, 1 * GRID_BOX}, (Vector2){i * GRID_BOX, (screen_height - GRID_BOX)}, GRID_COLOR);
        }

        // Draw Player
        DrawRectangleRec(snake[0].snake_rect, SNAKE_HEAD_COLOR);
        for (int i = 1; i <= length; i++)
        {
            DrawRectangleRec(snake[i].snake_rect, SNAKE_BODY_COLOR);
        }

        // Draw food
        DrawRectangleRec(food, FOOD_COLOR);
        DrawText(TextFormat("SCORE %i", length), 10, 10, 25, SCORE_TEXT);
    }
    break;
    case pause_screen:
    {
        DrawRectangle(200, 150, 400, 200, BG_COLOR);
        DrawText("Game Paused", (screen_width - MeasureText("Game Paused", 40)) / 2, 200, 40, GAME_PAUSED_TEXT);
        DrawText("Press ENTER To Resume", (screen_width - MeasureText("Press ENTER To Resume", 20)) / 2, 270, 20, SEC_TEXT);
    }
    break;

    case game_over:
    {
        DrawRectangle(200, 150, 400, 300, BG_COLOR);
        DrawText("GAME OVER", (screen_width - MeasureText("GAME OVER", 40)) / 2, 200, 40, GAME_OVER_TEXT);
        DrawText("Press ENTER to Play Again", (screen_width - MeasureText("Press ENTER to Play Again", 20)) / 2, 270, 20, SEC_TEXT);
        DrawText("Press ESC to Exit", (screen_width - MeasureText("Press ESC to Exit", 20)) / 2, 310, 20, SEC_TEXT);
    }
    break;
    default:
        break;
    }

    EndDrawing();
}