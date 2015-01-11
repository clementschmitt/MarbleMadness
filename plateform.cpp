#include "plateform.h"

Plateform::Plateform()
{
    cout <<"Creation de la plateforme"<<endl;
    useGravity = false;
    nbPoints = 4;
    points = new QVector3D[nbPoints];
    points[0] = QVector3D(-1, -1, -1);
    points[1] = QVector3D(1, -1, -1);
    points[2] = QVector3D(1, -1, 1);
    points[3] = QVector3D(-1, -1, 1);

    centerPosition = QVector3D(0,-1,0);
    cout <<"Fin de creation de la plateforme"<<endl;
}

Plateform::Plateform(QVector3D *pts)
{
    useGravity = false;
    nbPoints = (int)points->length();
    points = new QVector3D[nbPoints];
    points = pts;
}

QVector3D Plateform::getNormal()
{
    QVector3D AB = points[1] - points[0];
    QVector3D AC = points[2] - points[0];

    return QVector3D::crossProduct(AB, AC);
}
