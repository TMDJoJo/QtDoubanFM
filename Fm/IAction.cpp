#include "IAction.h"
#include <time.h>

IAction::IAction(IActor* actor) :
    actor_(actor),
    action_id_(0)
{
    ////用时间做ID
    action_id_ = (unsigned long)time(NULL);
}

