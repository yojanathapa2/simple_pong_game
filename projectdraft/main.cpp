#include <iostream>
#include "raylib.h"
#include "Ball.h"
#include "Paddle.h"
#include "CpuPaddle.h"
#include "Menu.h"

using namespace std;

// Global variables
int player_score = 0;
int computer_score = 0;
bool Paused = false;

Color Blue = Color{ 38, 154, 185, 255 };
Color Dark_Blue = Color{ 20, 133, 160, 255 };
Color Light_Blue = Color{ 129, 184, 204, 255 };
Color Yellow = Color{ 204, 204, 0, 255 };

int main()
{
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Ping Pong Game!!");
    SetTargetFPS(60);

    Ball ball(screen_width / 2, screen_height / 2, 5, 5, 20);
    Paddle player(screen_width - 35, screen_height / 2 - 60, 25, 120, 6);
    CpuPaddle cpu(10, screen_height / 2 - 60, 25, 120, 6);

    Menu menu({
        static_cast<float>(GetScreenWidth() / 2 - 100),
        static_cast<float>(GetScreenHeight() / 2 - 25),
        200,
        50
        });

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            Paused = !Paused;
        }

        if (!Paused)
        {
            ball.Update();
            player.Update();
            cpu.Update(ball.y);

            if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height }))
            {
                ball.speed_x *= -1;
            }

            if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
            {
                ball.speed_x *= -1;
            }
        }

        BeginDrawing();
        ClearBackground(Dark_Blue);

        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Blue);
        DrawCircle(screen_width / 2, screen_height / 2, 120, Light_Blue);
        DrawRectangle(screen_width / 2 - 3, 0, 6, screen_height, WHITE);
        DrawRectangle(0, 0, screen_width, 5, WHITE);
        DrawRectangle(0, screen_height - 5, screen_width, 5, WHITE);
        DrawRectangle(0, 0, 5, screen_height, WHITE);
        DrawRectangle(screen_width - 5, 0, 5, screen_height, WHITE);

        ball.Draw();
        cpu.Draw();
        player.Draw();

        DrawText(TextFormat("%i", computer_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        if (Paused)
        {
            menu.Draw();
            if (menu.CheckResumeButtonClick())
            {
                Paused = false;
            }
            else if (menu.CheckExitButtonClick())
            {
                CloseWindow(); // Close the game window
                break;         // Exit the main loop
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}


