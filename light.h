#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>
#include <QString>
#include <iostream>
#include <QColor>

class Light
{
public:
    Light();
    ~Light();

    float getRadius();
    QColor getColor();
    QVector3D getPosition();
    QColor computeLighting(const QVector3D, const QVector3D);

    void setRadius(float);
    void setColor(int, int, int);
    void setPosition(QVector3D);

private:
    float radius;
    QColor color;
    QVector3D position;

};

#endif // LIGHT_H
