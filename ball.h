#ifndef BALL_H
#define BALL_H

#include "entity.h"

class Ball : public Entity
{
public:
    Ball();

    void applyForce(int);
    float getRadius();


protected:
    float radius;

};

#endif // BALL_H
