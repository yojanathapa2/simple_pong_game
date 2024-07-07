
#ifndef BALL_H
#define BALL_H

#include "raylib.h"

// Declaration of extern variables
extern int player_score;
extern int computer_score;
extern Color Yellow;


class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    Ball(float posX, float posY, int spdX, int spdY, int rad);
    void Draw();
    void Update();
    void ResetBall();
};

#endif // BALL_H




