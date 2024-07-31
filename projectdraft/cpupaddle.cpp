#include "CpuPaddle.h"
#include "raylib.h"

CpuPaddle::CpuPaddle(float posX, float posY, float w, float h, int spd)
    : Paddle(posX, posY, w, h, spd) {}

void CpuPaddle::Update(int ball_y)
{
    
    if (y + height / 2 > ball_y) {
        y = y - speed;
    }
    if (y + height / 2 <= ball_y) {
        y = y + speed;
    }

    LimitMovement();
}


