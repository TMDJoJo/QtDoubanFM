#include "PlayTimeSlider.h"
#include <QDebug>
#include <QMouseEvent>

PlayTimeSlider::PlayTimeSlider(QWidget *parent) :
    QSlider(parent)
{
}
PlayTimeSlider::PlayTimeSlider(
        Qt::Orientation orientation, QWidget *parent) :
    QSlider(orientation,parent)
{
}

void PlayTimeSlider::mousePressEvent(QMouseEvent*){
    ////����QSlider��������¼�
}
