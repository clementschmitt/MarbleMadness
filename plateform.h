#ifndef PLATEFORM_H
#define PLATEFORM_H

#include "entity.h"

class Plateform : public Entity
{
public:
    Plateform();

    QVector3D getNormal();
};

#endif // PLATEFORM_H
