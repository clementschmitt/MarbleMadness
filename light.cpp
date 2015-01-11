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

/**
 * @brief Light::computeLighting
 * @param p du vecteur à illuminer
 * @param normal du vecteur à illuminer
 * @return
 */
QColor Light::computeLighting(QVector3D p, QVector3D normal)
{
    //On calcul le vecteur entre le point et la lumière
    QVector3D vertexToLight = this->position - p;
    //Calcul de l'aténuation de la lumière d'un vertex (linéaire)
    float attenuation = std::max<float>(0.0f, 1.0f - (vertexToLight.length() / radius));


}
