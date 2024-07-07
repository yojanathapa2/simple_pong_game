

#ifndef PADDLE_H
#define PADDLE_H

#include "raylib.h"

class Paddle {
protected:
    void LimitMovement();

public:
    float x, y;
    float width, height;
    int speed;

    Paddle(float posX, float posY, float w, float h, int spd);
    void Draw();
    void Update();
};

#endif // PADDLE_H



