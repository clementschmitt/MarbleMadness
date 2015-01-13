#include "ball.h"
Ball::Ball(){}

Ball::Ball(int horizontalBands, int verticalBands, QVector3D center)
{
    nbPoints = (horizontalBands+1) * (verticalBands+1);
    points = new QVector3D[nbPoints];
    normals = new QVector3D[nbPoints];
    nbFaces = (horizontalBands * verticalBands) * 2;
    faces = new Face[nbFaces];

    radius = 0.5;
    useGravity = true;
    massValue = 1;
    centerPosition = center;

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

            normals[horizontalNumber * (verticalBands+1) + verticalNumber] = QVector3D(x, y, z);
            points[horizontalNumber * (verticalBands+1) + verticalNumber] = QVector3D(radius * x + center.x(), radius * y + center.y(), radius * z + center.z());
        }
    }

    int currentFace = 0;

    for (int horizontalNumber = 0; horizontalNumber < horizontalBands; horizontalNumber++)
    {
        for (int verticalNumber = 0; verticalNumber < verticalBands; verticalNumber++)
        {
            int first = horizontalNumber * (verticalBands+1) + verticalNumber;
            int second = first + verticalBands;

            faces[currentFace] = Face(3);

            faces[currentFace].setVertex(first, 0);
            faces[currentFace].setVertex(second, 1);
            faces[currentFace].setVertex(first+1, 2);

            faces[currentFace].setNormal(first, 0);
            faces[currentFace].setNormal(second, 1);
            faces[currentFace].setNormal(first+1, 2);

            faces[currentFace].setColor(QColor(180, 180, 180), 0);
            faces[currentFace].setColor(QColor(180, 180, 180), 1);
            faces[currentFace].setColor(QColor(180, 180, 180), 2);

            currentFace++;

            faces[currentFace] = Face(3);
            faces[currentFace].setVertex(second, 0);
            faces[currentFace].setVertex(second+1, 1);
            faces[currentFace].setVertex(first+1, 2);

            faces[currentFace].setNormal(second, 0);
            faces[currentFace].setNormal(second+1, 1);
            faces[currentFace].setNormal(first+1, 2);

            faces[currentFace].setColor(QColor(180, 180, 180), 0);
            faces[currentFace].setColor(QColor(180, 180, 180), 1);
            faces[currentFace].setColor(QColor(180, 180, 180), 2);

            currentFace++;
        }
    }
}

float Ball::getRadius(){return radius;}
