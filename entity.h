#ifndef ENTITY_H
#define ENTITY_H

#include <QVector3D>

class Entity
{
public:
    Entity();
    Entity(QString); //Récupère les données d'un modèle 3D avec son localPath

    ~Entity();

    QVector3D getPoint(int);
    int* getFaces(int);
    int getPpf(int);
    int getNbFaces();
    int getNbPoints();

    void LoadModel(QString);

private:
    QVector3D *point; // ensemble des points de notre objet
    int** faces; //ensemble des faces de notre objet
    int* ppf; //nombre points par face (ppf)
    int nbFaces; //nombre de face dans notre objet
    int nbPoints; //nombre de points dans notre objet

    QVector3D position; // position du modèle 3D dans la scène
    QVector3D force; // total des forces appliqués à notre entité

    float velocity;
    float massValue;

    bool useGravity;
};

#endif // ENTITY_H
