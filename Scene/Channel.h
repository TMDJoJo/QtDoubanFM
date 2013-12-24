#ifndef CHANNEL_H
#define CHANNEL_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class Channel;
}

class Channel : public QWidget
{
    Q_OBJECT
    
public:
    explicit Channel(QWidget *parent = 0);
    ~Channel();
    void set_channel_name(const QString name);
    void set_song_num(quint32 num);
    inline void set_channel_id(quint32 id){ channel_id_ = id; }
signals:
    void clicked(quint32);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
private:
    Ui::Channel *ui;

    quint32 channel_id_;
};

#endif // CHANNEL_H
