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

    model->getCamera()->setSS(1);
    model->getCamera()->setRotX(45);
    model->getCamera()->setRotY(45);
    //loadMap(":/heightmap-1.png");

}

void GameWindow::render()
{

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glScalef(model->getCamera()->getSS(),model->getCamera()->getSS(),model->getCamera()->getSS());
    glRotatef(model->getCamera()->getRotX(),1.0f,0.0f,0.0f);
    glRotatef(model->getCamera()->getRotY(),0.0f,0.0f,1.0f);
    switch(model->getEtat())
    {
    case 0:
        displayPoints();
        break;
    case 1:
        displayLines();
        break;
    case 2:
        displayTriangles();
        break;
    case 3:
        displayTrianglesC();
        break;
    case 4:
        displayTrianglesTexture();
        break;
    case 5:
        displayTrianglesTexture();
        displayLines();
        break;
    default:
        displayPoints();
        break;
    }


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
    case 'Z':
        model->getCamera()->setSS(model->getCamera()->getSS()+0.10f);
        break;
    case 'S':
        model->getCamera()->setSS(model->getCamera()->getSS()-0.10f);
        break;
    case 'A':
        model->getCamera()->setRotX(model->getCamera()->getRotX()+1.0f);
        break;
    case 'E':
        model->getCamera()->setRotX(model->getCamera()->getRotX()-1.0f);
        break;
    case 'Q':
        model->getCamera()->setRotY(model->getCamera()->getRotY()+1.0f);
        break;
    case 'D':
        model->getCamera()->setRotY(model->getCamera()->getRotY()-1.0f);
        break;
    case 'W':
        model->setEtat(model->getEtat()+1);
        if(model->getEtat() > 5)
            model->setEtat(0);
        break;
    case 'C':
        if(model->getCamera()->getTurn()){
            model->getCamera()->setTurn(false);
            disconnect(time, SIGNAL(timeout()), model->getCamera(), SLOT(autoTurnY()));
        }
        else{
            model->getCamera()->setTurn(true);
            connect(time, SIGNAL(timeout()), model->getCamera(), SLOT(autoTurnY()));
        }
        break;
    case 'M':
        time->setInterval(time->interval()/2);
        break;
    case 'P':
        time->setInterval(time->interval()*2);
        break;
    case 'X':
        model->setCarte(model->getCarte()+1);
        break;
    }
}

void GameWindow::displayPoints()
{

    Objet3D* ptr;
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    ptr = model->getMap();
    for(int i = 0; i < ptr->getNbPoints(); i++)
    {
            glVertex3f(
                        ptr->getPoint(i).x,
                        ptr->getPoint(i).y,
                        ptr->getPoint(i).z);
    }
    for(int j = 0; j < model->getNbObj();j++){
        ptr = model->getObj(j);
        for(int i = 0; i < ptr->getNbPoints(); i++)
        {
                glVertex3f(
                            ptr->getPoint(i).x,
                            ptr->getPoint(i).y,
                            ptr->getPoint(i).z);
        }
    }
    glEnd();
}


void GameWindow::displayTriangles()
{
    Objet3D* ptr;
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    ptr = model->getMap();

    for(int i = 0; i < ptr->getNbFaces(); i++)
    {
        if(ptr->getPPF(i) == 3)
        {
            for(int j = 0; j < ptr->getPPF(i); j++)
            {
                if(i%2 == 0)
                    glColor3f(0.0f, 1.0f, 0.0f);
                else
                    glColor3f(1.0f, 1.0f, 1.0f);
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[j]).x,
                            ptr->getPoint(ptr->getFaces(i)[j]).y,
                            ptr->getPoint(ptr->getFaces(i)[j]).z);
            }
        }else if(ptr->getPPF(i) == 4)
        {
            glColor3f(0.0f, 1.0f, 0.0f);
            for(int j = 0; j < 3; j++)
            {
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[j]).x,
                            ptr->getPoint(ptr->getFaces(i)[j]).y,
                            ptr->getPoint(ptr->getFaces(i)[j]).z);
            }

            glColor3f(1.0f, 1.0f, 1.0f);
            for(int j = 2; j < 4; j++)
            {
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[j]).x,
                            ptr->getPoint(ptr->getFaces(i)[j]).y,
                            ptr->getPoint(ptr->getFaces(i)[j]).z);
            }
            glVertex3f(
                        ptr->getPoint(ptr->getFaces(i)[0]).x,
                        ptr->getPoint(ptr->getFaces(i)[0]).y,
                        ptr->getPoint(ptr->getFaces(i)[0]).z);
        }
    }

    for(int k = 0; k < model->getNbObj();k++){
        ptr = model->getObj(k);
        for(int i = 0; i < ptr->getNbFaces(); i++)
        {
            if(ptr->getPPF(i) == 3)
            {
                for(int j = 0; j < ptr->getPPF(i); j++)
                {
                    if(i%2 == 0)
                        glColor3f(0.0f, 1.0f, 0.0f);
                    else
                        glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex3f(
                                ptr->getPoint(ptr->getFaces(i)[j]).x,
                                ptr->getPoint(ptr->getFaces(i)[j]).y,
                                ptr->getPoint(ptr->getFaces(i)[j]).z);
                }
            }else if(ptr->getPPF(i) == 4)
            {
                glColor3f(0.0f, 1.0f, 0.0f);
                for(int j = 0; j < 3; j++)
                {
                    glVertex3f(
                                ptr->getPoint(ptr->getFaces(i)[j]).x,
                                ptr->getPoint(ptr->getFaces(i)[j]).y,
                                ptr->getPoint(ptr->getFaces(i)[j]).z);
                }

                glColor3f(1.0f, 1.0f, 1.0f);
                for(int j = 2; j < 4; j++)
                {
                    glVertex3f(
                                ptr->getPoint(ptr->getFaces(i)[j]).x,
                                ptr->getPoint(ptr->getFaces(i)[j]).y,
                                ptr->getPoint(ptr->getFaces(i)[j]).z);
                }
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[0]).x,
                            ptr->getPoint(ptr->getFaces(i)[0]).y,
                            ptr->getPoint(ptr->getFaces(i)[0]).z);
            }
        }
    }
    glEnd();
}

void GameWindow::displayTrianglesC()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    Objet3D* ptr = model->getMap();

    for(int i = 0; i < ptr->getNbFaces(); i++)
    {
        if(ptr->getPPF(i) == 3)
        {
            for(int j = 0; j < ptr->getPPF(i); j++)
            {
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[j]).x,
                            ptr->getPoint(ptr->getFaces(i)[j]).y,
                            ptr->getPoint(ptr->getFaces(i)[j]).z);
            }
        }
        else if(ptr->getPPF(i) == 4)
        {
            for(int j = 0; j < 3; j++)
            {
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[j]).x,
                            ptr->getPoint(ptr->getFaces(i)[j]).y,
                            ptr->getPoint(ptr->getFaces(i)[j]).z);
            }

            for(int j = 2; j < 4; j++)
            {
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[j]).x,
                            ptr->getPoint(ptr->getFaces(i)[j]).y,
                            ptr->getPoint(ptr->getFaces(i)[j]).z);
            }
            glVertex3f(
                        ptr->getPoint(ptr->getFaces(i)[0]).x,
                        ptr->getPoint(ptr->getFaces(i)[0]).y,
                        ptr->getPoint(ptr->getFaces(i)[0]).z);
        }
    }

    for(int k = 0; k < model->getNbObj();k++){
        ptr = model->getObj(k);
        for(int i = 0; i < ptr->getNbFaces(); i++)
        {
            if(ptr->getPPF(i) == 3)
            {
                for(int j = 0; j < ptr->getPPF(i); j++)
                {
                    glVertex3f(
                                ptr->getPoint(ptr->getFaces(i)[j]).x,
                                ptr->getPoint(ptr->getFaces(i)[j]).y,
                                ptr->getPoint(ptr->getFaces(i)[j]).z);
                }
            }
            else if(ptr->getPPF(i) == 4)
            {
                for(int j = 0; j < 3; j++)
                {
                    glVertex3f(
                                ptr->getPoint(ptr->getFaces(i)[j]).x,
                                ptr->getPoint(ptr->getFaces(i)[j]).y,
                                ptr->getPoint(ptr->getFaces(i)[j]).z);
                }

                for(int j = 2; j < 4; j++)
                {
                    glVertex3f(
                                ptr->getPoint(ptr->getFaces(i)[j]).x,
                                ptr->getPoint(ptr->getFaces(i)[j]).y,
                                ptr->getPoint(ptr->getFaces(i)[j]).z);
                }
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[0]).x,
                            ptr->getPoint(ptr->getFaces(i)[0]).y,
                            ptr->getPoint(ptr->getFaces(i)[0]).z);
            }
        }
    }
    glEnd();
}

void GameWindow::displayLines()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    Objet3D* ptr = model->getMap();

    for(int i = 0; i < ptr->getNbFaces(); i++)
    {
        glBegin(GL_LINE_LOOP);
        for(int j = 0; j < ptr->getPPF(i); j++)
        {
            glVertex3f(
                        ptr->getPoint(ptr->getFaces(i)[j]).x,
                        ptr->getPoint(ptr->getFaces(i)[j]).y,
                        ptr->getPoint(ptr->getFaces(i)[j]).z);
        }
        glEnd();
    }
/*
    for(int k = 0; k < model->getNbObj(); k++){
        ptr = model->getObj(k);
        for(int i = 0; i < ptr->getNbFaces(); i++)
        {
            glBegin(GL_LINE_LOOP);
            for(int j = 0; j < ptr->getPPF(i); j++)
            {
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[j]).x,
                            ptr->getPoint(ptr->getFaces(i)[j]).y,
                            ptr->getPoint(ptr->getFaces(i)[j]).z);
            }
            glEnd();
        }
    }
*/

}

void GameWindow::displayTrianglesTexture()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    Objet3D* ptr = model->getMap();

    for(int i = 0; i < ptr->getNbFaces(); i++)
    {
        if(ptr->getPPF(i) == 3)
        {
            for(int j = 0; j < ptr->getPPF(i); j++)
            {
                displayColor(ptr->getPoint(ptr->getFaces(i)[j]).z);
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[j]).x,
                            ptr->getPoint(ptr->getFaces(i)[j]).y,
                            ptr->getPoint(ptr->getFaces(i)[j]).z);
            }
        }
        else if(ptr->getPPF(i) == 4)
        {
            for(int j = 0; j < 3; j++)
            {
                displayColor(ptr->getPoint(ptr->getFaces(i)[j]).z);
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[j]).x,
                            ptr->getPoint(ptr->getFaces(i)[j]).y,
                            ptr->getPoint(ptr->getFaces(i)[j]).z);
            }

            for(int j = 2; j < 4; j++)
            {
                displayColor(ptr->getPoint(ptr->getFaces(i)[j]).z);
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[j]).x,
                            ptr->getPoint(ptr->getFaces(i)[j]).y,
                            ptr->getPoint(ptr->getFaces(i)[j]).z);
            }
            displayColor(ptr->getPoint(ptr->getFaces(i)[0]).z);
            glVertex3f(
                        ptr->getPoint(ptr->getFaces(i)[0]).x,
                        ptr->getPoint(ptr->getFaces(i)[0]).y,
                        ptr->getPoint(ptr->getFaces(i)[0]).z);
        }
    }

    for(int k = 0; k < model->getNbObj();k++){
        ptr = model->getObj(k);
        for(int i = 0; i < ptr->getNbFaces(); i++)
        {
            if(ptr->getPPF(i) == 3)
            {
                for(int j = 0; j < ptr->getPPF(i); j++)
                {
                    displayColor(ptr->getPoint(ptr->getFaces(i)[j]).z);
                    glVertex3f(
                                ptr->getPoint(ptr->getFaces(i)[j]).x,
                                ptr->getPoint(ptr->getFaces(i)[j]).y,
                                ptr->getPoint(ptr->getFaces(i)[j]).z);
                }
            }
            else if(ptr->getPPF(i) == 4)
            {
                for(int j = 0; j < 3; j++)
                {
                    displayColor(ptr->getPoint(ptr->getFaces(i)[j]).z);
                    glVertex3f(
                                ptr->getPoint(ptr->getFaces(i)[j]).x,
                                ptr->getPoint(ptr->getFaces(i)[j]).y,
                                ptr->getPoint(ptr->getFaces(i)[j]).z);
                }

                for(int j = 2; j < 4; j++)
                {
                    displayColor(ptr->getPoint(ptr->getFaces(i)[j]).z);
                    glVertex3f(
                                ptr->getPoint(ptr->getFaces(i)[j]).x,
                                ptr->getPoint(ptr->getFaces(i)[j]).y,
                                ptr->getPoint(ptr->getFaces(i)[j]).z);
                }
                displayColor(ptr->getPoint(ptr->getFaces(i)[0]).z);
                glVertex3f(
                            ptr->getPoint(ptr->getFaces(i)[0]).x,
                            ptr->getPoint(ptr->getFaces(i)[0]).y,
                            ptr->getPoint(ptr->getFaces(i)[0]).z);
            }
        }
    }
    glEnd();
}

void GameWindow::displayColor(float alt)
{
    if (alt > 0.2)
    {
        glColor3f(01.0f, 1.0f, 1.0f);
    }
    else     if (alt > 0.1)
    {
        glColor3f(alt, 1.0f, 1.0f);
    }
    else     if (alt > 0.05f)
    {
        glColor3f(01.0f, alt, alt);
    }
    else
    {
        glColor3f(0.0f, 0.0f, 1.0f);
    }

}

