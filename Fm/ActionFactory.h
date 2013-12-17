#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "IAction.h"

class ActionFactory
{
public:
    enum ActionType{
        SONG_NEXT       = 0,
        SONG_TRASH         ,
        SONG_LIKE          ,
        SONG_PAUSE         ,

        COUNT
    };
public:
    static IAction* CreateAction(IActor* actor,ActionType type);
private:
    ActionFactory(){}
};

#endif // ACTIONFACTORY_H
