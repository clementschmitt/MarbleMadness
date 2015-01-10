#include "ball.h"

Ball::Ball()
{
}

void Ball::applyVelocity(int timestep)
{
    velocity += (force / massValue) * timestep;
    center += velocity * timestep;
    movePoints(velocity * timestep);
}
