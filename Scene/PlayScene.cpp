#include "PlayScene.h"
#include "ui_PlayScene.h"
#include <QFile>
#include <QPainter>
#include <QDebug>

#include "../Fm/ActionFactory.h"
#include "../Fm/SongAction.h"

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

    ////����QSS��ʽ��
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
    ////��Ϣ�ص�


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

    ////����QSS��ʽ��
    QFile file(":/Qss/Resource/Qss/PlayScene.css");
    if (file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
    }
    file.close();
}
#include <QNetworkReply>
#include "../Net/Web.h"
void PlayScene::OnNextButtonClicked(){
    //Web* web = new Web();
    Web::Instance().Get(
                "http://douban.fm/j/mine/playlist?type=n&sid=&pt=0.0&channel=6&from=mainsite&r=54fb71862a",
                this);

    SongAction* action = dynamic_cast<SongAction*>(
                ActionFactory::CreateAction(this,ActionFactory::SONG_NEXT)
                );
    action->Excute();
    SAFE_DELETE(action);
}

void PlayScene::method(QNetworkReply* replay){
    qDebug()<<replay->readAll();
}

void PlayScene::OnTrashButtonClicked(){
    SongAction* action = dynamic_cast<SongAction*>(
                ActionFactory::CreateAction(this,ActionFactory::SONG_TRASH)
                );
    action->Excute();
    SAFE_DELETE(action);
}
