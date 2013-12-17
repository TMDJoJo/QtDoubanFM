#ifndef IACTION_H
#define IACTION_H

#include "./Common.h"
#include "./IActor.h"

class IAction
{
public:
    IAction(IActor* actor);
    virtual bool Excute() = 0;      ////具体的行为处理

    inline unsigned long action_id(){ return action_id_; }
    inline unsigned long set_action_id(unsigned long id){ return action_id_ = id; }

    inline const IActor* actor(){ return actor_; }
private:
    unsigned long action_id_;       ////行为ID
    IActor* actor_;                 ////行为实施者
};

#endif // IACTION_H
