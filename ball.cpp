#include "ball.h"
Ball::Ball(){}

Ball::Ball(int horizontalBands, int verticalBands)
{
    nbPoints = (horizontalBands+1) * (verticalBands+1);
    points = new QVector3D[nbPoints];
    nbFaces = (horizontalBands * verticalBands) * 2;
    faces = new int*[nbFaces];
    ppf = new int[nbFaces];
    radius = 0.5;
    for (int horizontalNumber = 0; horizontalNumber < horizontalBands+1; horizontalNumber++)
    {
        float theta = horizontalNumber * M_PI / horizontalBands;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for (int verticalNumber = 0; verticalNumber < verticalBands+1; verticalNumber++)
        {
            float phi = verticalNumber * 2 * M_PI / verticalBands;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;

            /*
            normalData.push(x);
            normalData.push(y);
            normalData.push(z);
            */

            points[horizontalNumber * (verticalBands+1) + verticalNumber] = QVector3D(radius * x, radius * y, radius * z);
            std::cout<<"Point n°"<<horizontalNumber * (verticalBands+1) + verticalNumber<<" = ("<<
                       radius * x<<", "<<radius * y<<", "<<radius * z<<")"<<std::endl;
        }
    }

    std::cout<<nbFaces<<std::endl;
    int currentFace = 0;
    for (int horizontalNumber = 0; horizontalNumber < horizontalBands; horizontalNumber++)
    {
        for (int verticalNumber = 0; verticalNumber < verticalBands; verticalNumber++)
        {
            std::cout<<currentFace<<std::endl;
            faces[currentFace] = new int[3];
            ppf[currentFace] = 3;

            int first = horizontalNumber * (verticalBands+1) + verticalNumber;
            int second = first + verticalBands;

            faces[currentFace][0] = first;
            faces[currentFace][1] = second;
            faces[currentFace][2] = first + 1;
            currentFace++;

            std::cout<<currentFace<<std::endl;
            faces[currentFace] = new int[3];
            ppf[currentFace] = 3;

            faces[currentFace][0] = second;
            faces[currentFace][1] = second + 1;
            faces[currentFace][2] = first + 1;
            currentFace++;
        }
    }

}

float Ball::getRadius(){return radius;}

