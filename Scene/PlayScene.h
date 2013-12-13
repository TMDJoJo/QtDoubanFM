#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QWidget>

namespace Ui {
class PlayScene;
}

class PlayScene : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlayScene(QWidget *parent = 0);
    ~PlayScene();

protected:
    void paintEvent(QPaintEvent* event);
private slots:
    void OnLikeButtonClicked();
    void OnNextButtonClicked();

private:
    void InitUi();
private:
    Ui::PlayScene *ui;

    bool is_liked_;     ////¸èÇúÊÇ·ñ±»Ï²»¶
};

#endif // PLAYSCENE_H
