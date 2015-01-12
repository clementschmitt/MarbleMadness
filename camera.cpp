#include "camera.h"

Camera::Camera(): rotX(-45.0), rotY(-45.0), ss(1.0f), turn(false){}

QVector3D Camera::getPos()const{return pos;}
float Camera::getRotX()const{return rotX;}
float Camera::getRotY()const{return rotY;}
float Camera::getSS()const{return ss;}
bool Camera::getTurn()const{return turn;}

void Camera::setPos(QVector3D p){pos = p;}
void Camera::setRotX(float f){rotX = f;}
void Camera::setRotY(float f){rotY = f;}
void Camera::setSS(float f){ss = f;}
void Camera::setTurn(bool b){turn = b;}

void Camera::autoTurnY(){rotY++;}
