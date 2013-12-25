#ifndef ALBUMSCENE_H
#define ALBUMSCENE_H

#include <QWidget>
#include <QMouseEvent>
#include <QEvent>

namespace Ui {
class AlbumScene;
}

class AlbumScene : public QWidget
{
    Q_OBJECT
public:
    explicit AlbumScene(QWidget *parent = 0);
    ~AlbumScene();
protected:
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void enterEvent(QEvent*);
    virtual void leaveEvent(QEvent*);
signals:
    void clicked();
public slots:
private:
    Ui::AlbumScene *ui;
    bool is_pressed_;
};

#endif // ALBUMSCENE_H
