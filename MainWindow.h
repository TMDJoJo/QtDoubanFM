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

    bool		moveing_;           ////��갴��
    QPoint	    move_position_;     ////�ƶ��ľ���

    QToolButton* close_button_;     ////�رհ�ť
    QToolButton* pause_button_;     ////��ͣ��ť
    QPushButton* play_button_;      ////���Ű�ť
};

#endif // MAINWINDOW_H
