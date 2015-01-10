#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QTimer>
#include "openglwindow.h"
#include "camera.h"
#include "ball.h"
#include "entity.h"
#include "level.h"

class GameWindow : public OpenGLWindow
{
public:
    GameWindow();
    GameWindow(int, Level);

    ~GameWindow();

    void initialize();
    void render();
    bool event(QEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void applyGravity();
    void collisionDetection();
    bool sphereToPlane(Plateform);

private:
    int m_frame;
    QTimer* timer;
    int timestep;
    Camera* cam;
    Ball player;
    Level level;
    QVector3D* playerForce;
    QVector3D gravity;
};


#endif // GAMEWINDOW_H
