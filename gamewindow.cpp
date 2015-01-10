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

GameWindow::GameWindow(int ts, Level l)
{
    level = l;
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
    level.applyGravity(playerForce);
    level.collisionDetection();


    ++m_frame;
}

/**
 * @brief GameWindow::drawLevel
 * @param width: largeur de notre plateforme
 * @param level: la scène à afficher
 */
void GameWindow::drawLevel()
{
    QVector3D point;

    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < level.getNbPlateformComponent() - 1; i++)
    {
        point = level.getPlateformComponent(i).getPoint(0);
        glVertex3f(point.x(), point.y(), point.z());
        point = level.getPlateformComponent(i).getPoint(1);
        glVertex3f(point.x(), point.y(), point.z());
        point = level.getPlateformComponent(i).getPoint(4);
        glVertex3f(point.x(), point.y(), point.z());

        point = level.getPlateformComponent(i).getPoint(1);
        glVertex3f(point.x(), point.y(), point.z());
        point = level.getPlateformComponent(i).getPoint(3);
        glVertex3f(point.x(), point.y(), point.z());
        point = level.getPlateformComponent(i).getPoint(4);
        glVertex3f(point.x(), point.y(), point.z());
    }
    glEnd();
}

void GameWindow::drawBall()
{
    Ball player = level.getPlayer();

    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < player.getNbFaces(); i++)
    {
        for(int j = 0; j < player.getPpf(i); j++)
        {
            glVertex3f(player.getPoint(player.getFaces(i)[j]).x(),
                       player.getPoint(player.getFaces(i)[j]).y(),
                       player.getPoint(player.getFaces(i)[j]).z());
        }
    }
    glEnd();
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
        playerForce.setY(playerForce.y()+10);
        break;
    case Qt::DownArrow :
        playerForce.setY(playerForce.y()-10);
        break;
    case Qt::LeftArrow :
        playerForce.setX(playerForce.x()+10);
        break;
    case Qt::RightArrow :
        playerForce.setX(playerForce.x()-10);
        break;
    }
}
