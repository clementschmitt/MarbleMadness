#include "entity.h"

using namespace std;

Entity::Entity()
{

}

Entity::Entity(QVector3D *pts, int nbPts)
{
    useGravity = false;
    nbFaces = 1;
    nbPoints = nbPts;
    points = pts;
    normals = new QVector3D[nbPoints];
    faces = new Face[nbFaces];
    faces[0] = Face(nbPts);
    faces[0].setNormal(QVector3D::normal(points[0],points[1],points[2]).normalized());
    float weight = 1.0 / nbPoints;
    QVector3D center;
    for(int i = 0; i < nbPts; i++)
    {
        normals[i] = faces[0].getNormal();
        faces[0].setVertex(i,i);
        faces[0].setNormal(i,i);
        center += weight * points[i];
    }
    faces[0].setCenterPosition(center);
    setCenterPosition();
}

Entity::Entity(QString filePath)
{
    QString currentLineContent;
    QFile file(filePath);
    QFileInfo fileInfo(filePath);
    std::cout<<fileInfo.fileName().toStdString()<<std::endl;
    if(file.open(QIODevice::ReadOnly))
    {
        std::cout<<"Hello"<<std::endl;
        QTextStream flux(&file);
        while(!flux.atEnd())
        {
            currentLineContent = flux.readLine();
            if (currentLineContent.contains("element vertex"))
            {
                //On récupère le nombre de vertex
                QStringList lstLine = currentLineContent.split(" ");
                nbPoints = lstLine.at(2).toInt();

                points = new QVector3D[nbPoints];
                normals = new QVector3D[nbPoints];
            }
            if (currentLineContent.contains("element face"))
            {
                QStringList lstLine = currentLineContent.split(" ");
                nbFaces = lstLine.at(2).toInt();

                faces = new Face[nbFaces];

            }
            if (currentLineContent.contains("end_header"))
            {
                std::cout<<"Nb Points = "<<nbPoints<<" nbFaces = "<<nbFaces<<std::endl;
                //Parcours de tous les points de notre modèle 3D
                for (int i = 0; i < nbPoints; i++)
                {
                    currentLineContent = flux.readLine();
                    QStringList coordinateList = currentLineContent.split(" ");

                    points[i].setX(coordinateList.at(0).toFloat());
                    points[i].setY(coordinateList.at(1).toFloat());
                    points[i].setZ(coordinateList.at(2).toFloat());

                    normals[i].setX(coordinateList.at(3).toFloat());
                    normals[i].setY(coordinateList.at(4).toFloat());
                    normals[i].setZ(coordinateList.at(5).toFloat());
                    std::cout<<"Point n"<<i<<" "<<points[i].x()<<" "<<points[i].y()<<" "<<points[i].z()<<
                               " - "<<normals[i].x()<<" "<<normals[i].y()<<" "<<normals[i].z()<<std::endl;
                }

                //Parcour de toutes les faces de notre modèle 3D
                for (int i = 0; i < nbFaces; i++)
                {
                    currentLineContent = flux.readLine();
                    QStringList vertexIndexList = currentLineContent.split(" ");

                    faces[i] = Face(vertexIndexList.at(0).toInt());
                    float weight = 1.0 / vertexIndexList.at(0).toInt();
                    QVector3D center;
                    std::cout<<"Face n"<<i<<" ";
                    for(int j = 0; j < faces[i].getNbPoints(); j++)
                    {
                        faces[i].setVertex(vertexIndexList.at(j+1).toInt(), j);
                        faces[i].setNormal(vertexIndexList.at(j+1).toInt(), j);

                        center += weight * points[vertexIndexList.at(j+1).toInt()];
                        std::cout<<vertexIndexList.at(j+1).toInt()<<" ";
                    }
                    faces[i].setCenterPosition(center);
                    faces[i].setNormal(QVector3D::normal(points[vertexIndexList.at(0).toInt()],
                                                         points[vertexIndexList.at(2).toInt()],
                                                         points[vertexIndexList.at(1).toInt()]).normalized());

                    std::cout<<"("<<faces[i].getCenterPosition().x()<<", "<<faces[i].getCenterPosition().y()<<", "<<faces[i].getCenterPosition().z()<<")"<<
                               "("<<faces[i].getNormal().x()<<", "<<faces[i].getNormal().y()<<", "<<faces[i].getNormal().z()<<")"<<std::endl;
                }
            }
        }
        file.close();
    }
    else
        std::cout<< "Impossible d'ouvrir le fichier"<<std::endl;
}

Face Entity::getFace(int index){return faces[index];}

int Entity::getNbFaces(){return nbFaces;}

int Entity::getNbPoints(){return nbPoints;}

QVector3D Entity::getPoint(int index){return points[index];}

QVector3D Entity::getNormal(int index){return normals[index];}

QVector3D Entity::getForce(){return force;}

QVector3D Entity::getVelocity(){return velocity;}

float Entity::getMassValue(){return massValue;}

QVector3D Entity::getCenterPosition(){return centerPosition;}

void Entity::setCenterPosition()
{
    float weight = 1.0 / nbPoints;
    QVector3D center;
    for(int i = 0; i < nbPoints; i++)
    {
        center += weight * points[i];
    }
    centerPosition = center;
}

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

void Entity::reset(QVector3D pos)
{
    QVector3D d = pos - getCenterPosition();
    translate(d);
    resetVelocity();
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


void Entity::initNormal()
{
    for (int i = 0; i < nbFaces; i++)
    {
        for (int j = 0; j < nbPoints; j++)
            faces[i].setNormal(faces[i].getNormal(j) + faces[i].getNormalIndex()[j], j);
    }
}
