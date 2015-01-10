#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

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

#include <QTimer>
#include "openglwindow.h"
#include "camera.h"
#include "ball.h"
#include "entity.h"
#include "plateform.h"
#include "level.h"
#include "staticConstant.h"

using namespace std;

class GameWindow : public OpenGLWindow
{
public:
    GameWindow();
    GameWindow(Level);

    ~GameWindow();

    void initialize();
    void render();
    void drawLevel();
    bool event(QEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    int m_frame;
    QTimer* timer;
    int timestep;
    Camera* cam;
    Ball player;
    Level level;
    QVector3D playerForce;
    QVector3D gravity;
};


#endif // GAMEWINDOW_H
