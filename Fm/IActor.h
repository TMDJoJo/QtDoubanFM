#ifndef IACTOR_H
#define IACTOR_H

class IAction;

class IActor
{
public:
    IActor();
    virtual bool Excute() = 0;
};

#endif // IACTOR_H
