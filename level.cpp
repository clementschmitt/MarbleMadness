#include "level.h"

Level::Level()
{
    QVector3D *plateformPoints1 = new QVector3D[4];
    QVector3D *plateformPoints2 = new QVector3D[4];

    plateformPoints1[0] = QVector3D(-1, -1, -1);
    plateformPoints1[1] = QVector3D(-1, -1, 1);
    plateformPoints1[2] = QVector3D(1, -1, 1);
    plateformPoints1[3] = QVector3D(1, -1, -1);

    plateformPoints2[0] = QVector3D(-2, -1.5, -2);
    plateformPoints2[1] = QVector3D(-1, -1, -1);
    plateformPoints2[2] = QVector3D(1, -1, -1);
    plateformPoints2[3] = QVector3D(1, -1.5, -2);

    std::cout <<"Creation du level"<<std::endl;
    plateformComponents = new Plateform[1];
    nbPlateformComponent = 1;

    //plateformComponents[0] = Plateform(plateformPoints1);
    //plateformComponents[1] = Plateform(plateformPoints2);

    player = Ball(28,28, QVector3D(0,1,0));
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
    std::cout<<"Test collision"<<std::endl;
    QVector3D* off = new QVector3D();
    for(int i = 0; i < getNbPlateformComponent(); i++)
    {
        Plateform p = getPlateformComponent(i);
        if(sphereToPlane(p, off))
        {
            std::cout<<"Collision = ("<<off->x()<<", "<<off->y()<<", "<<off->z()<<")"<<std::endl;
            player.translate(*(off));
            std::cout<<"Ball_Position = ("<<player.getCenterPosition().x()<<", "<<player.getCenterPosition().y()<<", "<<player.getCenterPosition().z()<<")"<<std::endl;
        }
        else
            std::cout<<"No Collision"<<std::endl;
    }
    std::cout<<"Fin test collision"<<std::endl;
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
bool Level::sphereToPlane(Plateform p, QVector3D* v)
{
    QVector3D tmp = player.getCenterPosition() - p.getCenterPosition();
    qreal dist = QVector3D::dotProduct(tmp, p.getNormal());

    v->setX((player.getRadius() - dist) * p.getNormal().x());
    v->setY((player.getRadius() - dist) * p.getNormal().y());
    v->setZ((player.getRadius() - dist) * p.getNormal().z());

    std::cout<<"Distance = "<<dist<<std::endl;
    std::cout<<"Plateform_Normal = ("<<p.getNormal().x()<<", "<<p.getNormal().y()<<", "<<p.getNormal().z()<<")"<<std::endl;
    std::cout<<"Plateform_Position = ("<<p.getCenterPosition().x()<<", "<<p.getCenterPosition().y()<<", "<<p.getCenterPosition().z()<<")"<<std::endl;
    std::cout<<"Ball_Position = ("<<player.getCenterPosition().x()<<", "<<player.getCenterPosition().y()<<", "<<player.getCenterPosition().z()<<")"<<std::endl;
    if(dist > player.getRadius())
        return false;
    else
        return true;
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

    player.applyForce();
}
