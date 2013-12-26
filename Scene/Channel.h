#ifndef CHANNEL_H
#define CHANNEL_H

#include <QWidget>
#include <QMouseEvent>

#include "../Fm/Type/DouBanChannel.h"
#include "../Fm/Common.h"

namespace Ui {
class Channel;
}

class Channel : public QWidget
{
    Q_OBJECT
    
public:
    explicit Channel(DouBanChannel* channel,QWidget *parent = 0);
    ~Channel();

protected:
    void paintEvent(QPaintEvent* event);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void leaveEvent(QEvent*);
signals:
    void clicked(quint32);
private:
    Ui::Channel *ui;
    DouBanChannel* channel_;

    bool is_pressed_;
};

#endif // CHANNEL_H
