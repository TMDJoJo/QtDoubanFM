#include "PlayScene.h"
#include "ui_PlayScene.h"
#include <QDebug>
#include <QFile>
#include <QPainter>
#include <QBrush>

#include "../Fm/ActionDispatch.h"

PlayScene::PlayScene(QWidget *parent) :
    QWidget(parent),
    is_liked_(false),
    ui(new Ui::PlayScene)
{
    ui->setupUi(this);
    InitUi();

    g_action_dispatch->set_play_scene(this);

}

PlayScene::~PlayScene()
{
    delete ui;
}

void PlayScene::InitUi(){

    ////设置QSS样式表
    QFile file(":/Qss/Resource/Qss/PlayScene.css");
    if (file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
    }
    file.close();

    ui->tbtn_like->setObjectName("tbtn_like_normal");

    ui->volume->setRange(0,100);
    ui->volume->setSliderPosition(100);

    connect(ui->tbtn_like,SIGNAL(clicked()),this,SLOT(OnLikeButtonClicked()));
    connect(ui->tbtn_trash,SIGNAL(clicked()),this,SLOT(OnTrashButtonClicked()));
    connect(ui->tbtn_next,SIGNAL(clicked()),this,SLOT(OnNextButtonClicked()));
    connect(ui->volume,SIGNAL(valueChanged(int)),this,SLOT(OnValueChanged (int)));
}

void PlayScene::set_play_time(qint64 play_time){
    QString minutes = QString::number(play_time/60000);
    QString secends = QString::number((play_time/1000)%60);
    ui->lbe_time_remaining->setText(minutes + ":" + secends);
    ui->play_time->setSliderPosition(play_time/1000);
}

void PlayScene::SetSongInfo(DouBanSong* song){
    if(NULL == song)
        return;
    ui->lbe_singer_name->setText(song->artist_.toStdString().c_str());
    ui->lbe_album_name->setText(("<" + song->albumtitle_ + "> " + song->public_time_));
    ui->lbe_song_name->setText(song->title_);
    ui->play_time->setRange(0,song->length_);
    if(!song->like_){
        ui->tbtn_like->setObjectName("tbtn_like_normal");
        is_liked_ = false;
    }
    else{
        ui->tbtn_like->setObjectName("tbtn_like_liked");
        is_liked_ = true;
    }
    ////设置QSS样式表
    QFile file(":/Qss/Resource/Qss/PlayScene.css");
    if (file.open(QIODevice::ReadOnly)){
        ui->tbtn_like->setStyleSheet(file.readAll());
    }
    file.close();

}

void PlayScene::SetAlbumPicture(QPixmap* picture){
    if(NULL == picture)
        return;
    ui->album_image->setAutoFillBackground(true);
    QPalette palette = ui->album_image->palette();
    // 缩放背景图.
    palette.setBrush(QPalette::Window,
                     QBrush(picture->scaled(
                                ui->album_image->size(),
                                Qt::IgnoreAspectRatio,
                                Qt::SmoothTransformation)));

    ui->album_image->setPalette(palette);
    SAFE_DELETE(picture);
}

void PlayScene::paintEvent(QPaintEvent*){

    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void PlayScene::OnLikeButtonClicked(){
    if(is_liked_){
        ui->tbtn_like->setObjectName("tbtn_like_normal");
        is_liked_ = false;
        g_action_dispatch->Like(false);
    }
    else{
        ui->tbtn_like->setObjectName("tbtn_like_liked");
        is_liked_ = true;
        g_action_dispatch->Like(true);
    }

    ////设置QSS样式表
    QFile file(":/Qss/Resource/Qss/PlayScene.css");
    if (file.open(QIODevice::ReadOnly)){
        ui->tbtn_like->setStyleSheet(file.readAll());
    }
    file.close();

}

void PlayScene::OnNextButtonClicked(){
    g_action_dispatch->Next();
}

void PlayScene::OnTrashButtonClicked(){
    g_action_dispatch->Trash();
}

void PlayScene::OnValueChanged(int value){
    g_action_dispatch->SetVolume(value);
}
