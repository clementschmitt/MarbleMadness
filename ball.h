#ifndef BALL_H
#define BALL_H

#include <iostream>
#include "entity.h"
#include <math.h>

class Ball : public Entity
{
public:
    Ball();
    Ball(int, int, QVector3D);
    float getRadius();

protected:
    float radius;

};

#endif // BALL_H
