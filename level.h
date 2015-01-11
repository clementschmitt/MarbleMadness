#ifndef LEVEL_H
#define LEVEL_H

#include "entity.h"
#include "plateform.h"
#include "ball.h"
#include "StaticConstant.h"

class Level
{
public:
    Level();

    int getNbPlateformComponent();
    Plateform getPlateformComponent(int);
    Ball getPlayer();

    void applyGravity(QVector3D);
    void collisionDetection();
    bool sphereToPlane(Plateform, QVector3D*);

protected:
    Plateform* plateformComponents;
    int nbPlateformComponent;
    Ball player;

};

#endif // LEVEL_H
