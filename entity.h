#ifndef ENTITY_H
#define ENTITY_H

#include <QVector3D>
#include <QString>
#include <iostream>

#include "StaticConstant.h"

using namespace std;

class Entity
{
public:
    Entity();
    Entity(QString); //Récupère les données d'un modèle 3D avec son localPath


    QVector3D getPoint(int);
    int* getFaces(int);
    int getPpf(int);
    int getNbFaces();
    int getNbPoints();

    QVector3D getForce();
    QVector3D getVelocity();
    float getMassValue();
    QVector3D getCenterPosition();

    void setCenterPosition(QVector3D);

    void LoadModel(QString);

    void initialize();
    void translate(QVector3D);
    void resetVelocity();

    void applyForce();
    void addForce(QVector3D);

protected:
    QVector3D *points; // ensemble des points de notre objet
    QVector3D *normals;
    int** faces; //ensemble des faces de notre objet
    int* ppf; //nombre points par face (ppf)
    int nbFaces; //nombre de face dans notre objet
    int nbPoints; //nombre de points dans notre objet

    QVector3D centerPosition; // position du modèle 3D dans la scène
    QVector3D force; // total des forces appliqués à notre entité

    QVector3D velocity;
    float massValue;

    bool useGravity;
};

#endif // ENTITY_H
