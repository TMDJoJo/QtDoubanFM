#ifndef ACTIONDISPATCH_H
#define ACTIONDISPATCH_H

#include <QObject>

#include "./Common.h"
#include "./ActionFactory.h"
#include "./IActor.h"
#include "./Type/DouBanSong.h"

class ActionDispatch : QObject
{
    Q_OBJECT
public:
    explicit ActionDispatch(QObject *parent = 0);
    bool ActionSong(IActor* actor,ActionFactory::ActionType type);

private slots:
    void OnReceivedNewList(SongList*);
    void OnReceiveNewList();
};

extern ActionDispatch* g_action_dispatch;
#endif // ACTIONDISPATCH_H
