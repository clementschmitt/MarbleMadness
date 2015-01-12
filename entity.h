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

    void setCenterPosition();

    void LoadModel(QString);

    void initialize();
    void translate(QVector3D);
    void resetVelocity();

    void applyForce();
    void addForce(QVector3D);

protected:

    Face* faces; //ensemble des faces de notre objet
    int nbFaces; //nombre de face dans notre objet
    int nbPoints;

    QVector3D *points; //ensemble des points de notre entité
    QVector3D *normals; //sensemble des normales des sommets

    QVector3D centerPosition; // position du modèle 3D dans la scène
    QVector3D force; // total des forces appliqués à notre entité

    QVector3D velocity;
    float massValue;

    bool useGravity;

private:
    //QFile file;
};

#endif // ENTITY_H
