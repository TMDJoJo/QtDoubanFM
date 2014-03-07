#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QToolButton>
#include <QPushButton>

#include "./Tray/Tray.h"
#include "./Tray/TrayIconMenu.h"
#include "./Fm/Music/Music.h"
#include "./Fm/Web/DouBanWeb.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent* event);

private slots:
    void OnPause();
    void OnPlay();

    void OnCloseButtonClicked();
    void OnShow();

    void OnMusicStateChange(Music::Music_State,Music::Music_State);
    void OnPlayTimeTick(qint64 play_time,qint64 remaining_time);
private:
    void InitUi();
    void InitTray();
    void InitWeb();
    void InitMusic();

private:
    Ui::MainWindow *ui;

    bool		moveing_;           ////鼠标按下
    QPoint	    move_position_;     ////移动的距离

    QToolButton* close_button_;     ////关闭按钮
    QToolButton* pause_button_;     ////暂停按钮
    QPushButton* play_button_;      ////播放按钮

    Tray* tray_;                    ////托盘
    TrayIconMenu* tray_menu_;       ////托盘菜单栏

    Music* music_;                  ////音乐播放单元
    DouBanWeb* douban_web_;         ////web连接单元
};

#endif // MAINWINDOW_H
