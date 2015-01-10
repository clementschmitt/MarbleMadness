#include "plateform.h"

Plateform::Plateform()
{
}

Plateform::Plateform(QVector3D * point)
{
    point[0] = QVector3D(-3.0f, -3.0f, -3.0f);
    point[1] = QVector3D(3.0f, -3.0f, -3.0f);
    point[2] = QVector3D(3.0f, -3.0f, 3.0f);
    point[3] = QVector3D(-3.0f, -3.0f, 3.0f);
}

QVector3D Plateform::getNormal()
{
    QVector3D AB = points[1] - points[0];
    QVector3D AC = points[2] - points[0];

    return QVector3D::crossProduct(AB, AC);
}
