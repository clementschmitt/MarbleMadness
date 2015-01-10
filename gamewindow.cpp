#include "gamewindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <time.h>
#include <sys/time.h>
#include <iostream>

#include <QtCore>
#include <QtGui>
using namespace std;


GameWindow::GameWindow()
{
    cam = new Camera();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(renderNow()));
    timer->start(60);
}

GameWindow::GameWindow(int ts, Level level)
{
    timestep = ((double)1/ts)*1000;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(renderNow()));
    timer->start(((double)1/ts)*1000);
}

GameWindow::~GameWindow()
{
    delete timer;
}

void GameWindow::initialize()
{
    const qreal retinaScale = devicePixelRatio();


    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -100.0, 100.0);

    //model->getCamera()->setSS(1);
    //model->getCamera()->setRotX(45);
    //model->getCamera()->setRotY(45);
}

void GameWindow::render()
{

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glScalef(cam->getSS(), cam->getSS(),cam->getSS());
    glRotatef(cam->getRotX(),1.0f,0.0f,0.0f);
    glRotatef(cam->getRotY(),0.0f,0.0f,1.0f);

    //drawLevel();
    //drawBall();
    applyGravity();
    collisionDetection();


    ++m_frame;
}

bool GameWindow::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::UpdateRequest:

        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::UpArrow :
        playerForce->setY(playerForce->y()+10);
        break;
    case Qt::DownArrow :
        playerForce->setY(playerForce->y()-10);
        break;
    case Qt::LeftArrow :
        playerForce->setX(playerForce->x()+10);
        break;
    case Qt::RightArrow :
        playerForce->setX(playerForce->x()-10);
        break;
    }
}

/**
 * @brief GameWindow::collisionDetection
 * Check collision between ball and all other wall
 */
void GameWindow::collisionDetection()
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
bool GameWindow::sphereToPlane(Plateform p)
{

    QVector3D tmp = player.getCenterPosition() - p.getCenterPosition();

    qreal dist = QVector3D.dotProduct(tmp, p.getNormal());

    if(dist > player.getRadius)
        return false;
    else
        return true;
}

/**
 * @brief GameWindow::applyGravity
 * Apply Gravity + Force on our ball
 */
void GameWindow::applyGravity()
{
    player.initialize();

    player.addForce(gravity * player.getMass());
    player.addForce(playerForce * player.getMass());

    player.applyForce(timestep);
}
