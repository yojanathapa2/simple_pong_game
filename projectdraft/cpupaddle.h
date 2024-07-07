
#ifndef CPUPADDLE_H
#define CPUPADDLE_H

#include "Paddle.h"

class CpuPaddle : public Paddle {
public:
    CpuPaddle(float posX, float posY, float w, float h, int spd);
    void Update(int ball_y);
};

#endif // CPUPADDLE_H


