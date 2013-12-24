#ifndef ACTIONDISPATCH_H
#define ACTIONDISPATCH_H

#include <QObject>
#include <QPixmap>

#include "./Common.h"
#include "./Type/DouBanSong.h"
#include "../Scene/PlayScene.h"
#include "../Scene/ChannelScene.h"
#include "./Type/DouBanChannel.h"

class ActionDispatch : QObject
{
    Q_OBJECT
public:
    explicit ActionDispatch(QObject *parent = 0);
//    bool ActionSong(IActor* actor,ActionFactory::ActionType type);

    bool set_play_scene(PlayScene* play_scene);
    bool set_channel_scene(ChannelScene* channel_scene);

    void Next();
    void Like(bool);
    void Trash();
    void SetVolume(quint8);

    void GetChannelId();

    void Pause();
    void Play();

    void ChangeChannel(quint32 from_channel_id,quint32 to_channel_id);
private slots:
    void OnReceivedNewList(SongList*);
    void OnReceivedAlbumPicture(QPixmap*);
    ////Music����ģ��ۺ���
    void OnEmptyList();
    void OnPlayTimeTick(qint64);
    void OnPlaySong(DouBanSong*);
    ////
    void OnReceivedHotChannels(ChannelList*);
    void OnReceivedFastChannels(ChannelList*);
private:
    PlayScene* play_scene_;
    ChannelScene* channel_scene_;
    bool is_next_;              ////��һ�ײ����Ƿ�ִ��
};

extern ActionDispatch* g_action_dispatch;
#endif // ACTIONDISPATCH_H
