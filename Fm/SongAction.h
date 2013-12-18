#ifndef SONGACTION_H
#define SONGACTION_H

#include <QChar>

#include "./IAction.h"
#include "./ActionFactory.h"

class SongAction : public IAction
{

public:
    SongAction(IActor* actor);
    virtual bool Excute();

    inline ActionFactory::ActionType type(){ return type_; }
    inline ActionFactory::ActionType set_type(ActionFactory::ActionType type){
        return type_ = type;
    }
private:
    bool NextSong();
    bool LikeSong();
    bool TrashSong();
private:
    ActionFactory::ActionType type_;
    quint32 song_id_;
    double play_time_;
    quint32 channel_id_;
    quint32 pb_;
};
#endif // SONGACTION_H
