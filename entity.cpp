#include "entity.h"

using namespace std;

Entity::Entity()
{
}

Entity::Entity(QString s)
{
}

QVector3D Entity::getPoint(int i){return point[i];}

int* Entity::getFaces(int i){return faces[i];}

int Entity::getPpf(int i){return ppf[i];}

int Entity::getNbFaces(){return nbFaces;}

int Entity::getNbPoints(){return nbPoints;}

void Entity::LoadModel(QString s)
{

}
