#include "TrayIconMenu.h"
#include <QAction>
#include <QApplication>

TrayIconMenu::TrayIconMenu(QWidget *parent) :
    QMenu(parent)
{
    Init();
}

void TrayIconMenu::Init(){

    QAction* open_action = new QAction(tr("豆瓣电台"),this);
    this->addAction(open_action);
    open_action->setEnabled(false);
    QAction* login_action = new QAction(tr("登录"),this);
    this->addAction(login_action);
    login_action->setEnabled(false);
    QAction* set_action = new QAction(tr("设置"),this);
    this->addAction(set_action);
    set_action->setEnabled(false);

    this->addSeparator();

    QAction* quit_Action = new QAction(tr("退出"),this);
    this->addAction(quit_Action);
    connect(quit_Action,SIGNAL(triggered()),qApp,SLOT(quit()));
}
