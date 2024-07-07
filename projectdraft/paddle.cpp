#include "Paddle.h"
#include "raylib.h" // Ensure to include raylib.h for raylib functions

Paddle::Paddle(float posX, float posY, float w, float h, int spd)
    : x(posX), y(posY), width(w), height(h), speed(spd) {}

void Paddle::Draw()
{
    DrawRectangleRounded(Rectangle{ x,y,width,height }, 0.8, 0, WHITE);
}

void Paddle::Update()
{
    if (IsKeyDown(KEY_UP))
    {
        y -= speed;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        y += speed;
    }

    LimitMovement();
}

void Paddle::LimitMovement()
{
    if (y <= 0)
    {
        y = 0;
    }

    if (y + height >= GetScreenHeight())
    {
        y = GetScreenHeight() - height;
    }
}


