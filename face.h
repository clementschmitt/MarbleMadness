#ifndef FACE_H
#define FACE_H

#include <QVector3D>
#include <QColor>

class Face
{
public:
    Face();
    Face(int);

    int getNbPoints();
    int getVertex(int);
    int getNormal(int);
    QColor getColor(int);
    QVector3D getNormal();
    QVector3D getCenterPosition();

    int* getVertexIndex();
    int* getNormalIndex();

    void setVertexIndex(int*);
    void setNormalIndex(int*);
    void setColors(QColor*);
    void setNormal(QVector3D);
    void setCenterPosition(QVector3D);

    void setVertex(int, int);
    void setNormal(int, int);
    void setColor(QColor, int);

private:
    int *vertexIndex; // ensemble des index des points de notre face
    int *normalIndex; // ensemble des index des normals des points de notre face
    int nbPoints; //nombre de points dans notre face
    QColor *colors; // ensemble des couleurs des points de notre face
    QVector3D normal;
    QVector3D centerPosition;
};

#endif // FACE_H
