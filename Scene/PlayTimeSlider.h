#ifndef PLAYTIMESLIDER_H
#define PLAYTIMESLIDER_H

#include <QSlider>

class PlayTimeSlider : public QSlider
{
public:
    explicit PlayTimeSlider(QWidget *parent = 0);
    explicit PlayTimeSlider(Qt::Orientation orientation, QWidget *parent = 0);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // PLAYTIMESLIDER_H
