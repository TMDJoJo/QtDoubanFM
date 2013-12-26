#include "Tray.h"
#include <QApplication>

Tray::Tray(QObject *parent) :
    QSystemTrayIcon(parent)
{
    Init();
}

void Tray::Init(){

    setIcon(QIcon(":/Img/Resource/Img/tray_icon.png"));
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void Tray::iconActivated(QSystemTrayIcon::ActivationReason reason){
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        emit Show();
    default:
        ;
    }
}
