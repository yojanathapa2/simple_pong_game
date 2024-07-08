#include <iostream>
#include <string>
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
string player_name = ""; // Global variable to store player's name
string cpu_name = "CPU"; // Default name for CPU
bool game_over = false;


Color Blue = Color{ 38, 154, 185, 255 };
Color Dark_Blue = Color{ 20, 133, 160, 255 };
Color Light_Blue = Color{ 129, 184, 204, 255 };
Color Yellow = Color{ 204, 204, 0, 255 };

enum GameState { HOME, GAME, EXIT, ENTER_PLAYER_NAME, ENTER_CPU_NAME, GAME_OVER }; // Added GAME_OVER state
GameState current_state = HOME;

void ResetGame()
{
    player_score = 0;
    computer_score = 0;
    Paused = false;
    game_over = false;
}

int main()
{
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Ping Pong Game!!");
    SetTargetFPS(60);

    // Load sound effect
    InitAudioDevice();  // Initialize audio device
    Sound hitSound = LoadSound("assets/sound.ogg");

    Ball ball(screen_width / 2, screen_height / 2, 5, 5, 20);
    Paddle player(screen_width - 35, screen_height / 2 - 60, 25, 120, 6);
    CpuPaddle cpu(10, screen_height / 2 - 60, 25, 120, 6);

    Menu menu({
        static_cast<float>(GetScreenWidth() / 2 - 100),
        static_cast<float>(GetScreenHeight() / 2 - 25),
        200,
        50
        });

    // Load home screen background image
    Image backgroundImage = LoadImage("abc.png");
    Texture2D background = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage); // Unload image from RAM, it is now in VRAM

    while (!WindowShouldClose())
    {
        switch (current_state)
        {
        case HOME:
            BeginDrawing();
            ClearBackground(Light_Blue);

            // Draw background image
            DrawTexture(background, 0, 0, Dark_Blue);

            // Draw Play and Exit buttons
            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ screen_width / 2 - 100, screen_height / 2 - 50, 200, 50 }))
            {
                DrawRectangle(screen_width / 2 - 100, screen_height / 2 - 50, 200, 50, Light_Blue);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    current_state = ENTER_PLAYER_NAME; // Move to enter player name state
                }
            }
            else
            {
                DrawRectangle(screen_width / 2 - 100, screen_height / 2 - 50, 200, 50, WHITE);
            }
            DrawText("Play", screen_width / 2 - 30, screen_height / 2 - 30, 20, BLACK);

            if (CheckCollisionPointRec(GetMousePosition(), Rectangle{ screen_width / 2 - 100, screen_height / 2 + 20, 200, 50 }))
            {
                DrawRectangle(screen_width / 2 - 100, screen_height / 2 + 20, 200, 50, Light_Blue);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    current_state = EXIT;
                }
            }
            else
            {
                DrawRectangle(screen_width / 2 - 100, screen_height / 2 + 20, 200, 50, WHITE);
            }
            DrawText("Exit", screen_width / 2 - 30, screen_height / 2 + 40, 20, BLACK);

            EndDrawing();
            break;

        case ENTER_PLAYER_NAME:
            BeginDrawing();
            ClearBackground(Light_Blue);
            DrawTexture(background, 0, 0, Dark_Blue);


            // Prompt for player name input
            DrawText("Enter Your Name:", screen_width / 2 - 100, screen_height / 2 - 100, 20, WHITE);
            DrawRectangle(screen_width / 2 - 150, screen_height / 2 - 50, 300, 40, Dark_Blue);
            DrawText(player_name.c_str(), screen_width / 2 - 140, screen_height / 2 - 40, 20, WHITE);

            // Input box for player name
            if (IsKeyPressed(KEY_ENTER) && !player_name.empty())
            {
                current_state = ENTER_CPU_NAME; // Move to enter CPU name state
            }
            else if (IsKeyPressed(KEY_BACKSPACE) && player_name.length() > 0)
            {
                player_name.pop_back();
            }
            else
            {
                int key = GetCharPressed();
                if (key >= 32 && key <= 125)
                {
                    player_name += static_cast<char>(key);
                }
            }

            EndDrawing();
            break;

        case ENTER_CPU_NAME:
            BeginDrawing();
            ClearBackground(Light_Blue);
            DrawTexture(background, 0, 0, Dark_Blue);


            // Prompt for CPU name input
            DrawText("Enter CPU Name (optional):", screen_width / 2 - 180, screen_height / 2 - 100, 20, WHITE);
            DrawRectangle(screen_width / 2 - 150, screen_height / 2 - 50, 300, 40, Dark_Blue);
            DrawText(cpu_name.c_str(), screen_width / 2 - 140, screen_height / 2 - 40, 20, WHITE);

            // Input box for CPU name
            if (IsKeyPressed(KEY_ENTER))
            {
                current_state = GAME; // Move to game state after CPU name input
            }
            else if (IsKeyPressed(KEY_BACKSPACE) && cpu_name.length() > 0)
            {
                cpu_name.pop_back();
            }
            else
            {
                int key = GetCharPressed();
                if (key >= 32 && key <= 125)
                {
                    cpu_name += static_cast<char>(key);
                }
            }

            EndDrawing();
            break;

        case GAME:
            if (IsKeyPressed(KEY_SPACE))
            {
                Paused = !Paused;
            }

            if (!Paused && !game_over)
            {
                ball.Update();
                player.Update();
                cpu.Update(ball.y);

                if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height }))
                {
                    ball.speed_x *= -1;
                    PlaySound(hitSound);

                }

                if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
                {
                    ball.speed_x *= -1;
                    PlaySound(hitSound);

                }

                // check wall collision for sound
                if (ball.x + ball.radius >= GetScreenWidth() - 5 || ball.x - ball.radius <= 5) {
                    PlaySound(hitSound);
                }

                // Check win conditions
                if (player_score >= 10)
                {
                    game_over = true;
                }
                else if (computer_score >= 10)
                {
                    game_over = true;
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

            // Display player and CPU names along with their respective scores
            DrawText(player_name.c_str(), screen_width - 230, 20, 30, WHITE);
            DrawText(cpu_name.c_str(), 20, 20, 30, WHITE);

            DrawText(TextFormat("%i", computer_score), screen_width / 4 - 20, 20, 60, WHITE);
            DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 60, WHITE);

            if (Paused)
            {
                menu.Draw();
                if (menu.CheckResumeButtonClick())
                {
                    Paused = false;
                }
                else if (menu.CheckExitButtonClick())
                {
                    current_state = EXIT; // QUIT THE GAME
                }
            }

            // Display game over message and options
            if (game_over)
            {
                /*DrawText("GAME OVER", screen_width / 2 - 150, screen_height / 2 - 50, 40, WHITE);
                DrawText(TextFormat("%s WON!", (player_score >= 10) ? player_name.c_str() : cpu_name.c_str()), screen_width / 2 - 150, screen_height / 2, 30, WHITE);

                DrawText("Press Enter to Play Again", screen_width / 2 - 200, screen_height / 2 + 50, 20, WHITE);
                DrawText("Press Esc to Exit", screen_width / 2 - 150, screen_height / 2 + 100, 20, WHITE);*/
                const char* gameOverText = "GAME OVER";
                const char* winnerText = TextFormat("%s WON!", (player_score >= 10) ? player_name.c_str() : cpu_name.c_str());
                const char* playAgainText = "Press Enter to Play Again";
                const char* exitText = "Press Esc to Exit";

                int gameOverTextWidth = MeasureText(gameOverText, 40);
                int winnerTextWidth = MeasureText(winnerText, 30);
                int playAgainTextWidth = MeasureText(playAgainText, 20);
                int exitTextWidth = MeasureText(exitText, 20);

                DrawText(gameOverText, screen_width / 2 - gameOverTextWidth / 2, screen_height / 2 - 50, 40, BLACK);
                DrawText(winnerText, screen_width / 2 - winnerTextWidth / 2, screen_height / 2, 30, BLACK);
                DrawText(playAgainText, screen_width / 2 - playAgainTextWidth / 2, screen_height / 2 + 50, 20, BLACK);
                DrawText(exitText, screen_width / 2 - exitTextWidth / 2, screen_height / 2 + 100, 20, BLACK);

                if (IsKeyPressed(KEY_ENTER))
                {
                    ResetGame();
                    current_state = GAME; // Return to game state to start over
                }
                else if (IsKeyPressed(KEY_ESCAPE))
                {
                    current_state = EXIT;
                }
            }

            EndDrawing();
            break;

        case EXIT:
            CloseWindow(); // Close the game window
            return 0;       // Exit the main loop
        }
    }

    // Unload texture
    UnloadTexture(background);
    // Unload sound effect
    UnloadSound(hitSound);
    CloseAudioDevice(); // closed audio device
    CloseWindow();
    return 0;

}
