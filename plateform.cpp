#include "plateform.h"

Plateform::Plateform()
{
    cout <<"Creation de la plateforme"<<endl;
    nbPoints = 4;
    points = new QVector3D[nbPoints];
    points[0] = QVector3D(-1, -1, 0);
    points[1] = QVector3D(-1, 1, 0);
    points[2] = QVector3D(1, 1, 0);
    points[3] = QVector3D(1, -1, 0);
    cout <<"Fin de creation de la plateforme"<<endl;
}

QVector3D Plateform::getNormal()
{
    QVector3D AB = points[1] - points[0];
    QVector3D AC = points[2] - points[0];

    return QVector3D::crossProduct(AB, AC);
}
