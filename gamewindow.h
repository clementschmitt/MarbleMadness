#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QTimer>
#include "openglwindow.h"
#include "ball.h"
#include "entity.h"

class GameWindow : public OpenGLWindow
{
public:
    GameWindow();
    GameWindow(int);

    ~GameWindow();

    void initialize();
    void render();
    bool event(QEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void displayTriangles();
    void displayLines();
    void displayTrianglesC();
    void displayPoints();
    void displayTrianglesTexture();

    void displayColor(float);

private:

    int m_frame;
    QTimer* timer;
    Ball player;
    QVector<Entity> walls;

};


#endif // GAMEWINDOW_H
