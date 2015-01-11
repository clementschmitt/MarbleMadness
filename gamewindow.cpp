#include "gamewindow.h"

GameWindow::GameWindow()
{
    cam = new Camera();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(renderNow()));
    timer->start(60);
}

GameWindow::GameWindow(Level l)
{
    level = l;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(renderNow()));
    timer->start(StaticConstant::timestep * 1000.0f);
    cam = new Camera();
    cout<<"Fin creation"<<endl;
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

    cam->setSS(1);
    cam->setRotX(45);
    cam->setRotY(45);
    cout<<"End of Initialization"<<endl;
}

void GameWindow::render()
{
    cout<<"Debut de frame"<<endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glScalef(cam->getSS(), cam->getSS(),cam->getSS());
    glRotatef(cam->getRotX(),1.0f,0.0f,0.0f);
    glRotatef(cam->getRotY(),0.0f,0.0f,1.0f);

    drawLevel();
    /*glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_POINT);
    glVertex3f(1.0f,1.0f,1.0f);
    glEnd();*/
    //drawBall();
    /*level.applyGravity(playerForce);
    level.collisionDetection();*/

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
    for (int i = 0; i < level.getNbPlateformComponent(); i++)
    {
        point = level.getPlateformComponent(i).getPoint(0);
        glVertex3f(point.x(), point.y(), point.z());
        point = level.getPlateformComponent(i).getPoint(1);
        glVertex3f(point.x(), point.y(), point.z());
        point = level.getPlateformComponent(i).getPoint(3);
        glVertex3f(point.x(), point.y(), point.z());

        point = level.getPlateformComponent(i).getPoint(1);
        glVertex3f(point.x(), point.y(), point.z());
        point = level.getPlateformComponent(i).getPoint(2);
        glVertex3f(point.x(), point.y(), point.z());
        point = level.getPlateformComponent(i).getPoint(3);
        glVertex3f(point.x(), point.y(), point.z());
    }
    glEnd();
    cout<<"Passage dans drawlevel"<<endl;
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
