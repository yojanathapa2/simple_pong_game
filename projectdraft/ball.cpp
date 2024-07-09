
#include "Ball.h"
#include "raylib.h"

// Definition of extern variables
extern int player_score;
extern int computer_score;
extern Color Yellow;

Ball::Ball(float posX, float posY, int spdX, int spdY, int rad)
    : x(posX), y(posY), speed_x(spdX), speed_y(spdY), radius(rad) {}

void Ball::Draw()
{
    DrawCircle(x, y, radius, Yellow);
}

void Ball::Update()
{
    x += speed_x;
    y += speed_y;

    if (y + radius >= GetScreenHeight() || y - radius <= 0)
    {
        speed_y *= -1;
    }

    if (x + radius >= GetScreenWidth())
    {
        computer_score++;
        ResetBall();
    }

    if (x - radius <= 0)
    {
        player_score++;
        ResetBall();
    }
}

void Ball::ResetBall()
{
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    int speed_choices[2] = { 1, -1 };
    speed_x = 7 * speed_choices[GetRandomValue(0, 1)]; // Adjusted ball speed
    speed_y = 7 * speed_choices[GetRandomValue(0, 1)]; // Adjusted ball speed
}


