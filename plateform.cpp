#include "plateform.h"

Plateform::Plateform()
{
    nbPoints = 4;
    points = new QVector3D[nbPoints];
    cout <<"Creation de la plateforme"<<endl;
    points[0] = QVector3D(-1.0f, -1.0f, -1.0f);
    points[1] = QVector3D(1.0f, -1.0f, -1.0f);
    points[2] = QVector3D(1.0f, -1.0f, 1.0f);
    points[3] = QVector3D(-1.0f, -1.0f, 1.0f);
}

QVector3D Plateform::getNormal()
{
    QVector3D AB = points[1] - points[0];
    QVector3D AC = points[2] - points[0];

    return QVector3D::crossProduct(AB, AC);
}
