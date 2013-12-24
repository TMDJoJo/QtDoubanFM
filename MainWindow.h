#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QToolButton>
#include <QPushButton>

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
private:
    void InitUi();
private:
    Ui::MainWindow *ui;

    bool		moveing_;           ////鼠标按下
    QPoint	    move_position_;     ////移动的距离

    QToolButton* close_button_;     ////关闭按钮
    QToolButton* pause_button_;     ////暂停按钮
    QPushButton* play_button_;      ////播放按钮
};

#endif // MAINWINDOW_H
