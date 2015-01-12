#include "level.h"

Level::Level()
{
    //QVector3D *pts;
    QVector3D *plateformPoints1 = new QVector3D[4];
    QVector3D *plateformPoints2 = new QVector3D[4];

    plateformPoints1[0] = QVector3D(-1, -0.5, -1);
    plateformPoints1[1] = QVector3D(-1, -0.5, 1);
    plateformPoints1[2] = QVector3D(1, -1, 1);
    plateformPoints1[3] = QVector3D(1, -1, -1);

    plateformPoints2[0] = QVector3D(1, -1, -1);
    plateformPoints2[1] = QVector3D(1, -1, 1);
    plateformPoints2[2] = QVector3D(20, -1, 1);
    plateformPoints2[3] = QVector3D(20, -1, -1);

    std::cout <<"Creation du level"<<std::endl;
    plateformComponents = new Plateform[2];
    nbPlateformComponent = 2;

    /*pts = new QVector3D[1];
    pts[0] = plateformPoints1;
    pts[1] = plateformPoints2;*/

    plateformComponents[0] = Plateform(plateformPoints1, 4);

    plateformComponents[1] = Plateform(plateformPoints2, 4);

    player = Ball(28,28, QVector3D(0,2,0));
    std::cout<<"Fin creation Level"<<std::endl;
}

int Level::getNbPlateformComponent(){return nbPlateformComponent;}

Plateform Level::getPlateformComponent(int index){return plateformComponents[index];}

/**
 * @brief GameWindow::collisionDetection
 * Check collision between ball and all other wall
 */
void Level::collisionDetection()
{
    QVector3D* off = new QVector3D();
    QVector3D* col = new QVector3D();
    for(int i = 0; i < getNbPlateformComponent(); i++)
    {
        Plateform p = getPlateformComponent(i);
        if(sphereToPlane(p, col, off))
        {
            QVector3D colNorm = (player.getCenterPosition() - *col);
            colNorm.normalize();
            player.translate(*(off));
            float j = -(0.5)* QVector3D::dotProduct((player.getMassValue()*player.getVelocity()), colNorm);
            QVector3D bounce = (j * colNorm);
            QVector3D friction = (0.99) * (projectionPointPlane(player.getCenterPosition()+player.getVelocity(), p) - *col);

            std::cout<<"("<<friction.x()<<", "<<friction.y()<<", "<<friction.z()<<")"<<std::endl;
            reponse = bounce + friction;
        }
    }
    if(!reponse.isNull())
    {
        player.resetVelocity();
        reponse /= StaticConstant::timestep;
    }
}

/**
 * @brief getPlayer
 * @return return ball controlling by player
 */
Ball Level::getPlayer(){return player;}

/**
 * @brief sphereToPlane
 * @param p
 * @return True if collision between the ball and plateform p
 */
bool Level::sphereToPlane(Plateform p, QVector3D* c, QVector3D* v)
{
    QVector3D tmp = player.getCenterPosition() - p.getCenterPosition();
    qreal dist = QVector3D::dotProduct(tmp, p.getNormal());
    if(dist < player.getRadius())
    {
        *c = player.getCenterPosition() - p.getNormal()*dist;
        if(checkInsidePolygone(p, *c))
        {
            v->setX((player.getRadius() - dist) * p.getNormal().x());
            v->setY((player.getRadius() - dist) * p.getNormal().y());
            v->setZ((player.getRadius() - dist) * p.getNormal().z());
            return true;
        }
        else
        {
            if(sphereToEdge(p, c))
            {
                v->setX((player.getRadius() - dist) * p.getNormal().x());
                v->setY((player.getRadius() - dist) * p.getNormal().y());
                v->setZ((player.getRadius() - dist) * p.getNormal().z());
                return true;
            }
        }
    }
    return false;
}

bool Level::sphereToEdge(Plateform p, QVector3D* c)
{
    QVector3D point;

    for(int i = 0; i < p.getNbPoints(); i++)
    {
        point = closestPointOnLine(p.getPoint(i), p.getPoint((i + 1) % p.getNbPoints()), player.getCenterPosition());

        if(distance(point, player.getCenterPosition()) < player.getRadius())
        {
            *c = point;
            return true;
        }
    }
    return false;
}

bool Level::checkInsidePolygone(Plateform p, QVector3D intersect)
{
    float angle = 0.0;
    QVector3D A, B;

    for(int i = 0; i < p.getNbPoints(); i++)
    {
        A = p.getPoint(i) - intersect;
        B = p.getPoint((i+1)%p.getNbPoints()) - intersect;
        angle += angleBetweenVectors(A, B);
    }
    if(angle >= (0.99 * (2.0 * M_PI)))
        return true;
    else
        return false;
}

QVector3D Level::closestPointOnLine(QVector3D A, QVector3D B, QVector3D point)
{
    QVector3D v1 = point - A;
    QVector3D v2 = (B - A).normalized();

    float t = QVector3D::dotProduct(v1, v2);

    if (t <= 0)
        return A;
    if (t >= distance(A, B))
        return B;

    return A + v2 * t;
}

float Level::angleBetweenVectors(QVector3D v1, QVector3D v2)
{
    float dotProduct = QVector3D::dotProduct(v1, v2);
    float vlength = v1.length() * v2.length();
    float angle = acosf(dotProduct/vlength);
    if(angle != angle)
        return 0;
    else
        return angle;
}

float Level::distance(QVector3D v1, QVector3D v2)
{
    return sqrt( (v2.x() - v1.x()) * (v2.x() - v1.x()) +
                 (v2.y() - v1.y()) * (v2.y() - v1.y()) +
                 (v2.z() - v1.z()) * (v2.z() - v1.z()) );
}

QVector3D Level::projectionPointPlane(QVector3D point, Plateform p)
{
    QVector3D tmp = point - p.getCenterPosition();
    qreal dist = QVector3D::dotProduct(tmp, p.getNormal());
    return point - p.getNormal()*dist;
}

/**
 * @brief GameWindow::applyGravity
 * Apply Gravity + Force on our ball
 */
void Level::applyGravity(QVector3D playerForce)
{
    player.initialize();

    player.addForce(StaticConstant::gravity * player.getMassValue());
    player.addForce(playerForce * player.getMassValue());
    player.addForce(reponse * player.getMassValue());

    reponse.setX(0);
    reponse.setY(0);
    reponse.setZ(0);

    player.applyForce();
}
