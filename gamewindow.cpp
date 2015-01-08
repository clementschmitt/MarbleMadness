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
    time = new QTimer(this);
    connect(time, SIGNAL(timeout()), this, SLOT(renderNow()));
    time->start(60);
}

GameWindow::GameWindow(int timestep){
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(renderNow()));
    timer->start(((double)1/timestep)*1000);
}

GameWindow::~GameWindow(){
    delete time;
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
    //applyGravity();
    //collissionDetection();


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
