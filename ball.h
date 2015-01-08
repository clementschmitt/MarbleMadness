#ifndef BALL_H
#define BALL_H

#include "entity.h"

class Ball : public Entity
{
private:

public:
    Ball();

    int CollisionBallWall(Entity);
};

#endif // BALL_H
