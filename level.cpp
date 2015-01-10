#include "level.h"

Level::Level()
{
}

int Level::getNbComponents(){return nbComponents;}

Entity* Level::getLevelComponents(){return levelComponents;}

/**
 * @brief GameWindow::collisionDetection
 * Check collision between ball and all other wall
 */
void Level::collisionDetection()
{
    for(int i; i < level.getNbWalls(); i++)
    {
        Plateform p = level.getWall(i);
        if(sphereToPlane(p))
        {
            player.setPosition();
        }
    }
}

/**
 * @brief sphereToPlane
 * @param p
 * @return True if collision between the ball and plateform p
 */
bool Level::sphereToPlane(Plateform p)
{

    QVector3D tmp = player.getCenterPosition() - p.getCenterPosition();

    qreal dist = QVector3D.dotProduct(tmp, p.getNormal());

    if(dist > player.getRadius())
        return false;
    else
        return true;
}

/**
 * @brief GameWindow::applyGravity
 * Apply Gravity + Force on our ball
 */
void Level::applyGravity()
{
    player.initialize();

    player.addForce(gravity * player.getMass());
    player.addForce(playerForce * player.getMass());

    player.applyForce(timestep);
}
