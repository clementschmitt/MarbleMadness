#include "entity.h"

using namespace std;

Entity::Entity()
{

}

Entity::Entity(QString s)
{
}

Face Entity::getFace(int index){return faces[index];}

int Entity::getNbFaces(){return nbFaces;}

int Entity::getNbPoints(){return nbPoints;}

QVector3D Entity::getPoint(int index){return points[index];}

QVector3D Entity::getNormal(int index){return normals[index];}

QVector3D* Entity::getPoints(){return points;}

QVector3D* Entity::getNormals(){return normals;}

QVector3D Entity::getForce(){return force;}

QVector3D Entity::getVelocity(){return velocity;}

float Entity::getMassValue(){return massValue;}

QVector3D Entity::getCenterPosition(){return centerPosition;}

void Entity::setCenterPosition(QVector3D position){centerPosition = position;}

void Entity::LoadModel(QString s)
{

}

void Entity::initialize(){
    force.setX(0);
    force.setY(0);
    force.setZ(0);
}


void Entity::translate(QVector3D movement)
{
    centerPosition += movement;
    for(int i = 0; i < nbPoints; i++)
        points[i] += movement;
}


void Entity::resetVelocity()
{
    velocity.setX(0);
    velocity.setY(0);
    velocity.setZ(0);
}

void Entity::applyForce()
{
    //std::cout<<"Velocity = ("<<velocity.x()<<", "<<velocity.y()<<", "<<velocity.z()<<")"<<std::endl;
    //std::cout<<"Force = ("<<force.x()<<", "<<force.y()<<", "<<force.z()<<")"<<std::endl;
    velocity += (force / massValue) * StaticConstant::timestep;
    translate(velocity * StaticConstant::timestep);
}

void Entity::addForce(QVector3D f){force += f;}

/*void Entity::initLighting(QColor ambiant)
{
    for (int i =0; i < nbFaces; i++)
    {
      //  faces[i].
    }
}

void Entity::addLight(Light l)
{

}*/
