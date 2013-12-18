#ifndef ACTIONDISPATCH_H
#define ACTIONDISPATCH_H
#include "./Common.h"

class ActionDispatch
{
public:
    ActionDispatch();
    bool Disptch();
};

extern ActionDispatch* g_action_dispatch;
#endif // ACTIONDISPATCH_H
