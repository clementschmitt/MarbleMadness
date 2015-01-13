#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <math.h>
#include <QMatrix4x4>

#include "entity.h"

class Ball : public Entity
{
public:
    Ball();
    Ball(int, int, QVector3D);
    float getRadius();

    void applyRotation();

    QMatrix4x4 rotation;

protected:
    float radius;
};

#endif // BALL_H
