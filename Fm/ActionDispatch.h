#ifndef ACTIONDISPATCH_H
#define ACTIONDISPATCH_H

#include <QObject>
#include <QPixmap>

#include "./Common.h"
#include "./ActionFactory.h"
#include "./IActor.h"
#include "./Type/DouBanSong.h"
#include "../Scene/PlayScene.h"

class ActionDispatch : QObject
{
    Q_OBJECT
public:
    explicit ActionDispatch(QObject *parent = 0);
    bool ActionSong(IActor* actor,ActionFactory::ActionType type);

    bool set_play_scene(PlayScene* play_scene);

private slots:
    void OnReceivedNewList(SongList*);
    void OnReceivedAlbumPicture(QPixmap*);
    ////Music²¥·ÅÄ£¿é²Ûº¯Êý
    void OnReceiveNewList();
    void OnPlayTimeTick(qint64);
    void OnPlaySong(DouBanSong*);

private:
    PlayScene* play_scene_;
};

extern ActionDispatch* g_action_dispatch;
#endif // ACTIONDISPATCH_H
