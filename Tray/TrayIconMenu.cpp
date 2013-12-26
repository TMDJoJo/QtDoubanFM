#include "TrayIconMenu.h"
#include <QAction>
#include <QApplication>

TrayIconMenu::TrayIconMenu(QWidget *parent) :
    QMenu(parent)
{
    Init();
}

void TrayIconMenu::Init(){

    QAction* open_action = new QAction(tr("�����̨"),this);
    this->addAction(open_action);
    open_action->setEnabled(false);
    QAction* login_action = new QAction(tr("��¼"),this);
    this->addAction(login_action);
    login_action->setEnabled(false);
    QAction* set_action = new QAction(tr("����"),this);
    this->addAction(set_action);
    set_action->setEnabled(false);

    this->addSeparator();

    QAction* quit_Action = new QAction(tr("�˳�"),this);
    this->addAction(quit_Action);
    connect(quit_Action,SIGNAL(triggered()),qApp,SLOT(quit()));
}
