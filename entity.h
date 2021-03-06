#ifndef ENTITY_H
#define ENTITY_H

#include <QVector3D>
#include <QString>
#include <iostream>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "staticConstant.h"
#include "face.h"

using namespace std;

class Entity
{
public:
    Entity();
    Entity(QVector3D*, int);
    Entity(const QString); //Récupère les données d'un modèle 3D avec son localPath

    Face getFace(int);
    int getNbFaces();
    int getNbPoints();

    QVector3D getPoint(int);
    QVector3D getNormal(int);

    QVector3D getForce();
    QVector3D getVelocity();
    float getMassValue();
    QVector3D getCenterPosition();
    QVector3D getOldCenterPoint();

    void setCenterPosition();

    void LoadModel(QString);

    void initialize();
    void translate(QVector3D);
    void reset(QVector3D);
    void resetVelocity();
    void applyForce();
    void addForce(QVector3D);

    void initNormal();

protected:

    Face* faces; //ensemble des faces de notre objet
    int nbFaces; //nombre de face dans notre objet
    int nbPoints;

    QVector3D *points; //ensemble des points de notre entité
    QVector3D *normals; //ensemble des normales des sommets

    QVector3D centerPosition; // position du modèle 3D dans la scène
    QVector3D force; // total des forces appliqués à notre entité
    QVector3D oldcenterPosition; //ensemble des points de notre entité au temps t-1

    QVector3D velocity;
    float massValue;

    bool useGravity;

};

#endif // ENTITY_H
