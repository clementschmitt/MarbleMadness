#include "face.h"

Face::Face()
{
}

Face::Face(int size)
{
    vertexIndex = new int[size];
    normalIndex = new int[size];
    colors = new QColor[size];
    nbPoints = size;
}

int Face::getNbPoints(){return nbPoints;}

int Face::getVertex(int i){return vertexIndex[i];}

int Face::getNormal(int i){return normalIndex[i];}

QColor Face::getColor(int i){return colors[i];}


int* Face::getVertexIndex(){return vertexIndex;}

int* Face::getNormalIndex(){return normalIndex;}


void Face::setVertexIndex(int *verIn){vertexIndex = verIn;}

void Face::setNormalIndex(int *normIn){normalIndex = normIn;}

void Face::setColors(QColor *cols){colors = cols;}


void Face::setVertex(int verIn, int i){vertexIndex[i] = verIn;}

void Face::setNormal(int normIn, int i){normalIndex[i] = normIn;}

void Face::setColor(QColor color, int i){colors[i] = color;}
