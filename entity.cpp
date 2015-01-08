#include "entity.h"

using namespace std;

Entity::Entity()
{
}

Entity::Entity(QString s)
{
}

Entity::getPoint(int i){return point[i];}

Entity::getFaces(int i){return faces[i];}

Entity::getPpf(int i){return ppf[i];}

Entity::getNbFaces(){return nbFaces;}

Entity::getNbPoints(){return nbPoints;}

Entity::LoadModel(Qstring s)
{

}
