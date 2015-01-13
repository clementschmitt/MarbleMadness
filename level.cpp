#include "level.h"

Level::Level()
{
    //QVector3D *pts;
    QVector3D *plateformPoints1 = new QVector3D[4];
    QVector3D *plateformPoints2 = new QVector3D[4];
    QVector3D *plateformLimit = new QVector3D[4];

    plateformPoints1[0] = QVector3D(-5, 2, -2);
    plateformPoints1[1] = QVector3D(-5, 2, 2);
    plateformPoints1[2] = QVector3D(5, 0.5, 2);
    plateformPoints1[3] = QVector3D(5, 0.5, -2);

    /*
    plateformPoints2[0] = QVector3D(1, -1, -1);
    plateformPoints2[1] = QVector3D(1, -1, 1);
    plateformPoints2[2] = QVector3D(20, -1, 1);
    plateformPoints2[3] = QVector3D(20, -1, -1);
    */

    plateformLimit[0] = QVector3D(-50, -5, -50);
    plateformLimit[1] = QVector3D(-50, -5, 50);
    plateformLimit[2] = QVector3D(50, -5, 50);
    plateformLimit[3] = QVector3D(50, -5, -50);

    std::cout <<"Creation du level"<<std::endl;
    plateformComponents = Entity(":/level.ply");
    //plateformComponents = Entity(plateformPoints1, 4);

    limit = Entity(plateformLimit, 4);

    begin = QVector3D(-4,10,0);
    player = Ball(28,28, begin);
    std::cout<<"Fin creation Level"<<std::endl;
}

Entity Level::getPlateformComponent(){return plateformComponents;}

/**
 * @brief GameWindow::collisionDetection
 * Check collision between ball and all other wall
 */
void Level::collisionDetection()
{
    QVector3D* off = new QVector3D();
    QVector3D* col = new QVector3D();

    for(int i = 0; i < getPlateformComponent().getNbFaces(); i++)
    {
        Face face = getPlateformComponent().getFace(i);
        if(sphereToPlane(face, plateformComponents , col, off))
        {
            //std::cout<<"collision at "<<col->x()<<", "<<col->y()<<", "<<col->z()<<std::endl;
            QVector3D colNorm = (player.getCenterPosition() - *col);
            colNorm.normalize();
            player.translate(*(off));

            float j = -(0.5)* QVector3D::dotProduct((player.getMassValue()*player.getVelocity()), colNorm);
            QVector3D bounce = (j * colNorm);
            QVector3D friction = (0.99) * (projectionPointPlane(player.getCenterPosition()+player.getVelocity(), face) - *col);
            reponse = bounce + friction;
        }
    }

    if(sphereToPlane(limit.getFace(0), limit, col, off)){player.reset(begin);}

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
bool Level::sphereToPlane(Face face, Entity e, QVector3D* c, QVector3D* v)
{
    QVector3D tmp = player.getCenterPosition() - face.getCenterPosition();
    qreal dist = QVector3D::dotProduct(tmp, face.getNormal());
    if(dist < player.getRadius())
    {
        *c = player.getCenterPosition() - face.getNormal()*dist;
        if(checkInsidePolygone(face, e, *c))
        {
            *v = (player.getRadius() - dist) * face.getNormal();
            return true;
        }
        else
        {
            if(sphereToEdge(face, e, c))
            {
                *v = (player.getRadius() - dist) * face.getNormal();
                return true;
            }
        }
    }
    return false;
}

bool Level::sphereToEdge(Face face, Entity e, QVector3D* c)
{
    QVector3D point;

    for(int i = 0; i < face.getNbPoints(); i++)
    {
        point = closestPointOnLine(e.getPoint(face.getVertexIndex(i)),
                                   e.getPoint(face.getVertexIndex(i + 1) % face.getNbPoints()),
                                   player.getCenterPosition());

        if(distance(point, player.getCenterPosition()) < player.getRadius())
        {
            *c = point;
            return true;
        }
    }
    return false;
}

bool Level::checkInsidePolygone(Face face, Entity e, QVector3D intersect)
{
    float angle = 0.0;
    QVector3D A, B;

    for(int i = 0; i < face.getNbPoints(); i++)
    {
        A = e.getPoint(face.getVertexIndex(i)) - intersect;
        B = e.getPoint(face.getVertexIndex((i+1)%face.getNbPoints())) - intersect;
        float a = angleBetweenVectors(A, B);
        angle += a;
    }

    if(angle >= (0.99 * (2.0 * M_PI)))
        return true;
    else
        return false;
}


QVector3D Level::projectionPointPlane(QVector3D point, Face f)
{
    QVector3D tmp = point - f.getCenterPosition();
    qreal dist = QVector3D::dotProduct(tmp, f.getNormal());
    return point - f.getNormal()*dist;
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
    float angle = acos(dotProduct/vlength);
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
/*********************************************GESTION DE LA LUMIERE****************************************************/
/**
 * @brief Entity::initLighting
 * @param ambiant
 */
void Level::initLighting(QColor ambiant)
{
    // Init pour le player
    for (int i =0; i < player.getNbFaces(); i++)
    {
        for (int j = 0; j < player.getFace(i).getNbPoints(); j++)
        {
            player.getFace(i).setColor(ambiant, j);
            std::cout<<"Init Color red: "<< player.getFace(i).getColor(j).red()<<std::endl;
        }

    }

    // Init pour les plateformes
    /*for (int i =0; i < nbPlateformComponent; i++)
    {
        for(int j = 0; j < plateformComponents[i].getFace().getNbPoints(); j++)
            plateformComponents[i].getFace().setColor(ambiant, j);
    }*/
    std::cout<<"Init Lighting"<<std::endl;
}

void Level::addLight(Light light)
{
    QColor c;

    for (int i = 0; i < player.getNbFaces(); i++)
    {
        for (int j = 0; j < player.getFace(i).getNbPoints(); j++)
        {
            std::cout<<"before compute Color red: "<< player.getFace(i).getColor(j).red()<<std::endl;
            c = light.computeLighting(player.getPoint(player.getFace(i).getVertexIndex(j)),
                                      player.getNormal(player.getFace(i).getNormalIndex(j)));

            player.getFace(i).getColor(j).setRed(player.getFace(i).getColor(j).red() + c.red());
            player.getFace(i).getColor(j).setGreen(player.getFace(i).getColor(j).green()+ c.green());
            player.getFace(i).getColor(j).setBlue(player.getFace(i).getColor(j).blue() + c.blue());
            std::cout<<"after compute Color red: "<< player.getFace(i).getColor(j).red()<<std::endl;
        }
    }

    /*for (int i =0; i < nbPlateformComponent; i++)
    {
        for (int j = 0; j < plateformComponents[i].getFace().getNbPoints(); j++)
        {
            c = light.computeLighting(plateformComponents[i].getPoint(plateformComponents[i].getFace().getVertexIndex(j)),
                    plateformComponents[i].getNormal());

            plateformComponents[i].getFace().getColor(j).setRed(plateformComponents[i].getFace().getColor(j).red() + c.red());
            plateformComponents[i].getFace().getColor(j).setGreen(plateformComponents[i].getFace().getColor(j).green() + c.green());
            plateformComponents[i].getFace().getColor(j).setBlue(plateformComponents[i].getFace().getColor(j).blue() + c.blue());
        }
    }*/

    std::cout<<"ADD Light"<<std::endl;

}
