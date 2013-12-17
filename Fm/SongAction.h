#ifndef SONGACTION_H
#define SONGACTION_H

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
};
#endif // SONGACTION_H
