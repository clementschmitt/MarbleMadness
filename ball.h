#ifndef BALL_H
#define BALL_H

#include "entity.h"

class Ball : public Entity
{
private:

public:
    Ball();

    void applyForce(int);
};

#endif // BALL_H
