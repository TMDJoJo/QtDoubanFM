#ifndef IACTION_H
#define IACTION_H

#include "./Common.h"
#include "./IActor.h"

class IAction
{
public:
    IAction(IActor* actor);
    virtual bool Excute() = 0;      ////�������Ϊ����

    inline unsigned long action_id(){ return action_id_; }
    inline unsigned long set_action_id(unsigned long id){ return action_id_ = id; }

    inline const IActor* actor(){ return actor_; }
private:
    unsigned long action_id_;       ////��ΪID
    IActor* actor_;                 ////��Ϊʵʩ��
};

#endif // IACTION_H
