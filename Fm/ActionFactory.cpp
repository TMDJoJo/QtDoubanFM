#include "ActionFactory.h"
#include "./SongAction.h"

IAction* ActionFactory::CreateAction(IActor* actor,ActionType type){
    if(NULL == actor)
        return NULL;
    IAction* action = NULL;
    switch(type){
    ////¸èÇú²Ù×÷
    case SONG_NEXT:
    case SONG_LIKE:
    case SONG_PAUSE:
    case SONG_TRASH:
        action = new SongAction(actor);
        dynamic_cast<SongAction*>(action)->set_type(type);
        break;
    ////....


    default:
        break;
    }

    return action;
}
