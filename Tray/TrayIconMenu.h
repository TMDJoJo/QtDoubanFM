#ifndef TRAYICONMENU_H
#define TRAYICONMENU_H

#include <QMenu>

class TrayIconMenu : public QMenu
{
    Q_OBJECT
public:
    explicit TrayIconMenu(QWidget *parent = 0);
    
private:
    void Init();

signals:
    
public slots:
    
};

#endif // TRAYICONMENU_H
