#ifndef PLATEFORM_H
#define PLATEFORM_H

#include "entity.h"


class Plateform : public Entity
{
public:
    Plateform();
    Plateform(QVector3D*, int);

    Face getFace();

    QVector3D getNormal();

private:
    Face face;

};

#endif // PLATEFORM_H
