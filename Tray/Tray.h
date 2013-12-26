#ifndef TRAY_H
#define TRAY_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMainWindow>
#include <qDebug>

class Tray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit Tray(QObject *parent = 0);
    ~Tray(){}

private:
    void Init();
private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
signals:
    void Show();
public slots:
    
private:

};

#endif // TRAY_H
