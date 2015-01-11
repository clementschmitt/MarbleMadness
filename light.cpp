#include "light.h"

Light::Light()
{
}

float Light::getRadius(){return radius;}
QColor Light::getColor(){return color;}
QVector3D Light::getPosition(){return position;}

void Light::setRadius(float r){radius = r;}
void Light::setColor(int r, int g, int b){color = QColor(r, g, b);}
void Light::setPosition(QVector3D p){position = p;}

QColor Light::computeLighting(QVector3D p, QVector3D normal)
{

}
