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

    glMatrixMode(GL_PROJECTION);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);

    //level->initLighting(QColor(200 , 200, 200));
    //level->addLight(light);
    //level->addLight(light);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    cam->setSS(0.1);
    cam->setRotX(-45);
    cam->setRotY(-45);
    cout<<"End of Initialization"<<endl;
}

void GameWindow::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glScalef(cam->getSS(), cam->getSS(),cam->getSS());
    glRotatef(cam->getRotX(),1.0f,0.0f,0.0f);
    glRotatef(cam->getRotY(),0.0f,1.0f,0.0f);
    glTranslatef(-cam->getPos().x(), -cam->getPos().y(), -cam->getPos().z());

    //cout<<cam->getRotX()<<" "<<cam->getRotY()<<endl;

    //Add ambient light
    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    //Add positioned light
    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    //std::cout<<"X = "<<cam->getRotX()<<std::endl;
    //std::cout<<"Y = "<<cam->getRotY()<<std::endl;
    QVector3D oldPos = level->getPlayer().getCenterPosition();
    level->applyGravity(playerForce);
    level->collisionDetection();
    QVector3D newPos = level->getPlayer().getCenterPosition();
    drawLevel();
    drawBall();

    playerForce.setX(0);
    playerForce.setY(0);
    playerForce.setZ(0);
    cam->setPos(cam->getPos() + newPos - oldPos);
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
            glNormal3f(n.x(), n.y(), n.z());
            glColor3f(c.redF(), c.greenF(), c.blueF());
            //std::cout<<(float)c.red()/255<<" "<<c.green()/255<<" "<<c.blue()/255<<std::endl;
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
