#include "plateform.h"

Plateform::Plateform()
{
    cout <<"Creation de la plateforme"<<endl;
    useGravity = false;
    nbPoints = 4;
    points = new QVector3D[nbPoints];
    points[0] = QVector3D(-1, -1, -1);
    points[1] = QVector3D(-1, -1, 1);
    points[2] = QVector3D(1, -1, 1);
    points[3] = QVector3D(1, -1, -1);

    centerPosition = QVector3D(0,-1,0);
    cout <<"Fin de creation de la plateforme"<<endl;
}

Plateform::Plateform(QVector3D *pts, int nbPts)
{
    useGravity = false;
    nbFaces = 1;
    nbPoints = nbPts;
    face = Face(nbFaces);
    points = pts;
}

QVector3D Plateform::getNormal()
{
    QVector3D normal = QVector3D::normal(points[0],points[1],points[2]);
    return normal.normalized();
}
