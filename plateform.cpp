#include "plateform.h"

Plateform::Plateform()
{
    point[0] = QVector3D(-3.0f, -3.0f, -3.0f);
    point[1] = QVector3D(3.0f, -3.0f, -3.0f);
    point[2] = QVector3D(3.0f, -3.0f, 3.0f);
    point[3] = QVector3D(-3.0f, -3.0f, 3.0f);

}

QVector3D Plateform::getNormal()
{
    QVector3D AB = point[1] - point[0];
    QVector3D AC = point[2] - point[0];

    return QVector3D::crossProduct(AB, AC);
}
