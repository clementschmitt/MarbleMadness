#ifndef LEVEL_H
#define LEVEL_H

#include "entity.h"
#include "plateform.h"
#include "ball.h"

class Level
{
public:
    Level();

    int getNbPlateformComponent();
    Entity* getPlateformComponent();

protected:
    Plateform* plateformComponents;
    int nbPlateformComponent;

};

#endif // LEVEL_H
