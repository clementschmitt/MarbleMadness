#include "ball.h"

Ball::Ball()
{
}

void Ball::applyForce(int timestep)
{
    velocity += (force / massValue) * timestep;
    centerPosition += velocity * timestep;
    translate(velocity * timestep);
}
