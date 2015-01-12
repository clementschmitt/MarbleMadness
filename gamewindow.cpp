#include "gamewindow.h"

GameWindow::GameWindow()
{
    /*
    cam = new Camera();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(renderNow()));
    timer->start(60);
    */
}

GameWindow::GameWindow(Level* l)
{
    cout<<"Debut creation GameWindow"<<endl;
    level = l;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(renderNow()));
    timer->start(StaticConstant::timestep * 1000.0f);
    cam = new Camera();
    cout<<"Fin creation GameWindow"<<endl;
}

GameWindow::~GameWindow()
{
    delete timer;
    delete cam;
    delete level;
}

void GameWindow::initialize()
{
    cout<<"Debut Initialization"<<endl;
    const qreal retinaScale = devicePixelRatio();


    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    //glEnable(GL_NORMALIZE);
    cam->setSS(0.1);
    cam->setRotX(30);
    cam->setRotY(30);
    cout<<"End of Initialization"<<endl;
}

void GameWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glScalef(cam->getSS(), cam->getSS(),cam->getSS());
    glRotatef(cam->getRotX(),1.0f,0.0f,0.0f);
    glRotatef(cam->getRotY(),0.0f,1.0f,0.0f);

    //std::cout<<"X = "<<cam->getRotX()<<std::endl;
    //std::cout<<"Y = "<<cam->getRotY()<<std::endl;

    level->applyGravity(playerForce);
    level->collisionDetection();
    drawLevel();
    drawBall();

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
    glColor3f(0.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < level->getNbPlateformComponent(); i++)
    {
        point = level->getPlateformComponent(i).getPoint(0);
        glVertex3f(point.x(), point.y(), point.z());
        point = level->getPlateformComponent(i).getPoint(1);
        glVertex3f(point.x(), point.y(), point.z());
        point = level->getPlateformComponent(i).getPoint(3);
        glVertex3f(point.x(), point.y(), point.z());

        point = level->getPlateformComponent(i).getPoint(1);
        glVertex3f(point.x(), point.y(), point.z());
        point = level->getPlateformComponent(i).getPoint(2);
        glVertex3f(point.x(), point.y(), point.z());
        point = level->getPlateformComponent(i).getPoint(3);
        glVertex3f(point.x(), point.y(), point.z());
    }
    glEnd();
}

void GameWindow::drawBall()
{
    Ball player = level->getPlayer();

    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLES);

    for(int i = 0; i < player.getNbFaces(); i++)
    {
        Face f = player.getFace(i);
        for(int j = 0; j < f.getNbPoints(); j++)
        {
            QVector3D p = player.getPoint(f.getVertex(j));
            glVertex3f(p.x(),
                       p.y(),
                       p.z());
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
    case 'A':
        cam->setRotX(cam->getRotX()+1.0f);
        break;
    case 'E':
        cam->setRotX(cam->getRotX()-1.0f);
        break;
    case 'Q':
        cam->setRotY(cam->getRotY()+1.0f);
        break;
    case 'D':
        cam->setRotY(cam->getRotY()-1.0f);
        break;
    }
}
