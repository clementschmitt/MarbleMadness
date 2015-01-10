#include "entity.h"

using namespace std;

Entity::Entity()
{

}

Entity::Entity(QString s)
{
}

QVector3D Entity::getPoint(int i){return points[i];}

int* Entity::getFaces(int i){return faces[i];}

int Entity::getPpf(int i){return ppf[i];}

int Entity::getNbFaces(){return nbFaces;}

int Entity::getNbPoints(){return nbPoints;}

float Entity::getMassValue(){return massValue;}

QVector3D Entity::getCenterPosition(){return centerPosition;}

void Entity::setCenterPosition(QVector3D position){centerPosition = position;}

void Entity::LoadModel(QString s)
{

}

void Entity::initialize(){}


void Entity::translate(QVector3D movement)
{
    for(int i = 0; i < nbPoints; i++)
        points[i] += movement;
}

void Entity::applyForce(int timestep)
{
    velocity += (force / massValue) * timestep;
    centerPosition += velocity * timestep;
    translate(velocity * timestep);
}

void Entity::addForce(QVector3D force){}
