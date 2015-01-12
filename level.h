#ifndef LEVEL_H
#define LEVEL_H

//#include <float.h>
#include <algorithm>

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
    bool sphereToPlane(Plateform, QVector3D*, QVector3D*);
    bool sphereToEdge(Plateform, QVector3D*);
    bool checkInsidePolygone(Plateform, QVector3D);
    QVector3D projectionPointPlane(QVector3D ,Plateform);
    QVector3D closestPointOnLine(QVector3D, QVector3D, QVector3D);
    float angleBetweenVectors(QVector3D, QVector3D);
    float distance(QVector3D, QVector3D);

protected:
    Plateform* plateformComponents;
    int nbPlateformComponent;
    Ball player;
    QVector3D reponse;

};

#endif // LEVEL_H
