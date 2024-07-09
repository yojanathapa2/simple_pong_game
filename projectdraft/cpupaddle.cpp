#include "CpuPaddle.h"
#include "raylib.h"

CpuPaddle::CpuPaddle(float posX, float posY, float w, float h, int spd)
    : Paddle(posX, posY, w, h, spd) {}

void CpuPaddle::Update(int ball_y)
{
    //float reaction_delay = 0.2f; // Increased delay factor for the CPU's reaction

    /*if (y + height / 2 > ball_y + ball_y * reaction_delay)
    {
        y -= speed;
    }
    if (y + height / 2 < ball_y - ball_y * reaction_delay)
    {
        y += speed;
    }*/
    if (y + height / 2 > ball_y) {
        y = y - speed;
    }
    if (y + height / 2 <= ball_y) {
        y = y + speed;
    }

    LimitMovement();
}


