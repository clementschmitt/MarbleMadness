#include "face.h"

Face::Face()
{
}

Face::Face(int size)
{
    vertexIndex = new int[size];
    normalIndex = new int[size];
    colors = new QColor[size];
    for(int i = 0; i < size; i++)
    {
        colors[i] = QColor(125,125,65);
    }
    nbPoints = size;
}

int Face::getNbPoints(){return nbPoints;}

int Face::getVertexIndex(int i){return vertexIndex[i];}

int Face::getNormalIndex(int i){return normalIndex[i];}

QColor Face::getColor(int i){return colors[i];}

QVector3D Face::getNormal(){return normal;}

QVector3D Face::getCenterPosition(){return centerPosition;}

void Face::setVertexIndex(int *verIn){vertexIndex = verIn;}

void Face::setNormalIndex(int *normIn){normalIndex = normIn;}

void Face::setColors(QColor *cols){colors = cols;}

void Face::setNormal(QVector3D n){normal = n;}

void Face::setCenterPosition(QVector3D p){centerPosition = p;}

void Face::setVertex(int verIn, int i){vertexIndex[i] = verIn;}

void Face::setNormal(int normIn, int i){normalIndex[i] = normIn;}

void Face::setColor(QColor color, int i){colors[i] = color;}
