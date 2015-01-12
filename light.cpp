#include "light.h"

Light::Light()
{

}

Light::Light(float r, QColor c, QVector3D pos)
{
    radius = r;
    color = c;
    position = pos;
}


Light::~Light()
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
    QColor col = this->color;
    //On calcul le vecteur entre le point et la lumière
    QVector3D vertexToLight = this->position - p;
    //Calcul de l'aténuation de la lumière d'un vertex (linéaire)
    float attenuation = 1.0f - (vertexToLight.length() / radius);

    //Normalisation du vecteur
    vertexToLight.normalize();
    //Calcul du produit scalaire NdotL avec N la normal et L le vertexToLight

    attenuation *= QVector3D::dotProduct(vertexToLight, normal);
    std::cout<<"Attenuation "<<attenuation<<std::endl;
    attenuation = std::max<float>(0.0f, attenuation);

    std::cout<<"Color red before attenuation: "<<col.red()<<std::endl;
    std::cout<<"Atenuation "<<attenuation<<" red = "<<col.red() * attenuation<<std::endl;
    col.setRed(col.red() * attenuation);
    col.setGreen(col.green() * attenuation);
    col.setBlue(col.blue() * attenuation);

    std::cout<<"Color red after attenuation: "<<col.red()<<std::endl;

    return col;
}
