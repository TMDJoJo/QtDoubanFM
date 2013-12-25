#ifndef CHANNELSCENE_H
#define CHANNELSCENE_H

#include <QWidget>
#include <QPropertyAnimation>

#include "../Fm/Type/DouBanChannel.h"

namespace Ui {
class ChannelScene;
}

class ChannelScene : public QWidget
{
    Q_OBJECT
    
public:
    explicit ChannelScene(QWidget *parent = 0);
    ~ChannelScene();
    void AddHotChannel(DouBanChannel*);
    void AddFastChannel(DouBanChannel*);

    inline quint32 current_channel_id(){ return current_channel_id_; }
protected:
    void paintEvent(QPaintEvent* event);
private slots:
    void OnSidebarClicked();
    void OnSiderbarAnimationFinished();
    void OnChannelClicked(quint32);
private:
    Ui::ChannelScene *ui;

    quint32 current_channel_id_;

    ChannelList* hot_channel_list_;
    ChannelList* fast_channel_list_;

    QPropertyAnimation* siderbar_animation_;
    bool is_spread_;
};

#endif // CHANNELSCENE_H
