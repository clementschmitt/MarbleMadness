#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera();

    float getRotX()const;
    float getRotY()const;
    float getSS()const;
    bool getTurn()const;

    void setRotX(float);
    void setRotY(float);
    void setSS(float);
    void setTurn(bool);

public slots:
    void autoTurnY();

private:
    float rotX;
    float rotY;
    float ss;
    bool turn;
};

#endif // CAMERA_H
