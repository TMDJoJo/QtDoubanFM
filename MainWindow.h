#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QToolButton>
#include <QPushButton>

#include "./Tray/Tray.h"
#include "./Tray/TrayIconMenu.h"

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
    void OnStateChangePlaying();
    void OnStateChangePaused();
    void OnCloseButtonClicked();
    void OnShow();
private:
    void InitUi();
    void InitTray();
private:
    Ui::MainWindow *ui;

    bool		moveing_;           ////��갴��
    QPoint	    move_position_;     ////�ƶ��ľ���

    QToolButton* close_button_;     ////�رհ�ť
    QToolButton* pause_button_;     ////��ͣ��ť
    QPushButton* play_button_;      ////���Ű�ť

    Tray* tray_;                    ////����
    TrayIconMenu* tray_menu_;       ////���̲˵���
};

#endif // MAINWINDOW_H
