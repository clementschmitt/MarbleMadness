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
    light = Light(1000.0f, QColor(200 , 200, 200), QVector3D(10.0, 10.0, 10.0));
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
    glOrtho(-10.0, 50.0, -10.0, 10.0, -10.0, 10.0);

    //level->initLighting(QColor(200 , 200, 200));
    //level->addLight(light);
    //level->addLight(light);

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

    playerForce.setX(0);
    playerForce.setY(0);
    playerForce.setZ(0);
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
    QVector3D p, n;
    QColor c;
    Face f;

    //glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLES);

    for(int i = 0; i < player.getNbFaces(); i++)
    {
        f = player.getFace(i);
        for(int j = 0; j < f.getNbPoints(); j++)
        {
            p = player.getPoint(f.getVertexIndex(j));
            n = player.getNormal(f.getNormalIndex(j));
            c = f.getColor(j);
            //light.computeLighting(p, n);

            //std::cout<<"Color red: "<< c.redF()<<std::endl;

            glVertex3f(p.x(), p.y(), p.z());
            //glColor3f(c.red()/255, c.green()/255, c.blue()/255);

            //std::cout<<"Color red: "<< c.red()/255<<std::endl;
            //std::cout<<"Color green: "<< c.green() <<std::endl;
            //std::cout<<"Color blue: "<< c.blue() <<std::endl;
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
    case Qt::Key_Up :
        playerForce.setZ(playerForce.z()+10);
        break;
    case Qt::Key_Down :
        playerForce.setZ(playerForce.z()-10);
        break;
    case Qt::Key_Left :
        playerForce.setX(playerForce.x()-10);
        break;
    case Qt::Key_Right :
        playerForce.setX(playerForce.x()+10);
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
