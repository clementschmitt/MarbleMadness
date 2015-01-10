#include "plateform.h"

Plateform::Plateform()
{
}

QVector3D Plateform::getNormal()
{
    QVector3D AB = point[1] - point[0];
    QVector3D AC = point[2] - point[0];

    return QVector3D::crossProduct(AB, AC);
}
