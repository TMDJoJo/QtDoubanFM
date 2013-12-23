#ifndef ACTIONDISPATCH_H
#define ACTIONDISPATCH_H

#include <QObject>
#include <QPixmap>

#include "./Common.h"
#include "./Type/DouBanSong.h"
#include "../Scene/PlayScene.h"

class ActionDispatch : QObject
{
    Q_OBJECT
public:
    explicit ActionDispatch(QObject *parent = 0);
//    bool ActionSong(IActor* actor,ActionFactory::ActionType type);

    bool set_play_scene(PlayScene* play_scene);

    void Next();
    void Like(bool);
    void Trash();
    void SetVolume(quint8);

    void GetChannelId();
private slots:
    void OnReceivedNewList(SongList*);
    void OnReceivedAlbumPicture(QPixmap*);
    ////Music����ģ��ۺ���
    void OnEmptyList();
    void OnPlayTimeTick(qint64);
    void OnPlaySong(DouBanSong*);

private:
    PlayScene* play_scene_;

    bool is_next_;              ////��һ�ײ����Ƿ�ִ��
};

extern ActionDispatch* g_action_dispatch;
#endif // ACTIONDISPATCH_H
