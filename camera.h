#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QVector3D>

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera();

    QVector3D getPos()const;
    float getRotX()const;
    float getRotY()const;
    float getSS()const;
    bool getTurn()const;

    void setPos(QVector3D);
    void setRotX(float);
    void setRotY(float);
    void setSS(float);
    void setTurn(bool);

public slots:
    void autoTurnY();

private:
    QVector3D pos;
    float rotX;
    float rotY;
    float ss;
    bool turn;
};

#endif // CAMERA_H
