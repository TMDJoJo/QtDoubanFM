#include "PlayScene.h"
#include "ui_PlayScene.h"
#include <QFile>
#include <QPainter>
#include <QDebug>

#include "../Fm/ActionFactory.h"
#include "../Fm/SongAction.h"
#include "../Fm/ActionDispatch.h"

PlayScene::PlayScene(QWidget *parent) :
    QWidget(parent),
    is_liked_(false),
    ui(new Ui::PlayScene)
{
    ui->setupUi(this);
    InitUi();
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

    connect(ui->tbtn_like,SIGNAL(clicked()),this,SLOT(OnLikeButtonClicked()));
    connect(ui->tbtn_trash,SIGNAL(clicked()),this,SLOT(OnTrashButtonClicked()));
    connect(ui->tbtn_next,SIGNAL(clicked()),this,SLOT(OnNextButtonClicked()));
}

bool PlayScene::Excute(){
    ////消息回调


    return true;
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
    }
    else{
        ui->tbtn_like->setObjectName("tbtn_like_liked");
        is_liked_ = true;
    }

    ////设置QSS样式表
    QFile file(":/Qss/Resource/Qss/PlayScene.css");
    if (file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
    }
    file.close();

    g_action_dispatch->ActionSong(this,ActionFactory::SONG_LIKE);
}

void PlayScene::OnNextButtonClicked(){
    g_action_dispatch->ActionSong(this,ActionFactory::SONG_NEXT);
}

void PlayScene::OnTrashButtonClicked(){
    g_action_dispatch->ActionSong(this,ActionFactory::SONG_TRASH);
}
