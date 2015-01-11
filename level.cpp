#include "level.h"

Level::Level()
{
    std::cout <<"Creation du level"<<std::endl;
    plateformComponents = new Plateform[1];
    nbPlateformComponent = 1;
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
    v->setX(fabs((tmp*p.getNormal()).x()));
    v->setY(fabs((tmp*p.getNormal()).y()));
    v->setZ(fabs((tmp*p.getNormal()).z()));
    qreal dist = QVector3D::dotProduct(tmp, p.getNormal());
    std::cout<<"Distance = "<<dist<<std::endl;
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
