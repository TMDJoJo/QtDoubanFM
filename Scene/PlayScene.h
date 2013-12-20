#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QWidget>
#include <QPixmap>

#include "../Fm/IActor.h"
#include <QNetworkReply>
#include "../Fm/Type/DouBanSong.h"

namespace Ui {
class PlayScene;
}

class PlayScene : public QWidget ,public IActor
{
    Q_OBJECT
    
public:
    explicit PlayScene(QWidget *parent = 0);
    ~PlayScene();

    virtual bool Excute();
    void set_play_time(qint64 play_time);
    void SetSongInfo(DouBanSong*);
    void SetAlbumPicture(QPixmap*);

protected:
    void paintEvent(QPaintEvent* event);

private slots:
    void OnLikeButtonClicked();
    void OnNextButtonClicked();
    void OnTrashButtonClicked();
private:
    void InitUi();
private:
    Ui::PlayScene *ui;

    bool is_liked_;     ////¸èÇúÊÇ·ñ±»Ï²»¶
};

#endif // PLAYSCENE_H
