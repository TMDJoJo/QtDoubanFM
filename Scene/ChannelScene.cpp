#include "ChannelScene.h"
#include "ui_ChannelScene.h"
#include <QFile>
#include <QDebug>
#include <QPainter>
#include <QGridLayout>

#include "./Channel.h"
#include "../Fm/ActionDispatch.h"

ChannelScene::ChannelScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelScene),
    siderbar_animation_(NULL),
    is_spread_(false),
    current_channel_id_(0)
{
    ui->setupUi(this);

    //this->setAutoFillBackground(true);
    ui->sidebar_btn->setObjectName("sidebar_btn_180");
    ui->sidebar_btn->setFocusPolicy(Qt::NoFocus);
    ////设置QSS样式表
    QFile file(":/Qss/Resource/Qss/ChannelScene.css");
    if (file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());    }
    file.close();

    g_action_dispatch->set_channel_scene(this);

    connect(ui->sidebar_btn,SIGNAL(clicked()),
            this,SLOT(OnSidebarClicked()));
}

ChannelScene::~ChannelScene()
{
    while(!hot_channel_list_->isEmpty()){
        DouBanChannel* channel = hot_channel_list_->front();
        hot_channel_list_->pop_front();
        SAFE_DELETE(channel);
    }
    while(!fast_channel_list_->isEmpty()){
        DouBanChannel* channel = fast_channel_list_->front();
        fast_channel_list_->pop_front();
        SAFE_DELETE(channel);
    }
    SAFE_DELETE(hot_channel_list_);
    SAFE_DELETE(fast_channel_list_);
    SAFE_DELETE(siderbar_animation_);
    delete ui;
}

void ChannelScene::paintEvent(QPaintEvent*){

    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void ChannelScene::OnSidebarClicked(){
    siderbar_animation_ = new QPropertyAnimation(this,"pos");
    Q_ASSERT(siderbar_animation_);
    siderbar_animation_->setDuration(200);

    if(is_spread_){
        siderbar_animation_->setStartValue(QPoint(this->pos().x(),this->pos().y()));
        siderbar_animation_->setEndValue(
                    QPoint(ui->sidebar_btn->width() - this->width(),0)
                    );
        is_spread_ = false;
    }
    else{
        siderbar_animation_->setStartValue(QPoint(this->pos().x(),this->pos().y()));
        siderbar_animation_->setEndValue(QPoint(0,0));
        is_spread_ = true;
    }
    siderbar_animation_->start(QAbstractAnimation::DeleteWhenStopped);
    connect(siderbar_animation_,SIGNAL(finished()),this,SLOT(OnSiderbarAnimationFinished()));
}

void ChannelScene::OnSiderbarAnimationFinished(){
    if(is_spread_){
        ui->sidebar_btn->setObjectName("sidebar_btn");
    }
    else{
        ui->sidebar_btn->setObjectName("sidebar_btn_180");
    }
    ////设置QSS样式表
    QFile file(":/Qss/Resource/Qss/ChannelScene.css");
    if (file.open(QIODevice::ReadOnly)){
        ui->sidebar_btn->setStyleSheet(file.readAll());
    }
    file.close();
}

void ChannelScene::OnChannelClicked(quint32 channel_id){
    current_channel_id_ = channel_id;
    g_action_dispatch->ChangeChannel(current_channel_id_,channel_id);
}

void ChannelScene::AddHotChannel(DouBanChannel* channel){

    if(NULL == channel)
        return;
    Channel* new_channel = new Channel(channel);
    Q_ASSERT(new_channel);
//    new_channel->set_channel_name(channel->name_ + "MHz");
//    new_channel->set_song_num(QString::number(channel->song_num_) + tr("首歌曲"));
//    new_channel->set_channel_id(channel->id_);
    connect(new_channel,SIGNAL(clicked(quint32)),
            this,SLOT(OnChannelClicked(quint32)));

    if(ui->hot_channel_scroll_area->item_count()%2 == 0)
        ui->hot_channel_scroll_area->AddWidget(new_channel,ui->hot_channel_scroll_area->item_count()/2,0);
    else{
        ui->hot_channel_scroll_area->AddWidget(new_channel,ui->hot_channel_scroll_area->item_count()/2,1);
    }

}

void ChannelScene::AddFastChannel(DouBanChannel* channel){

    if(NULL == channel)
        return;

    Channel* new_channel = new Channel(channel);
    Q_ASSERT(new_channel);
//    new_channel->set_channel_name(channel->name_ + "MHz");
//    new_channel->set_song_num(QString::number(channel->song_num_) + tr("首歌曲"));
//    new_channel->set_channel_id(channel->id_);

    connect(new_channel,SIGNAL(clicked(quint32)),
            this,SLOT(OnChannelClicked(quint32)));

    if(ui->fast_channel_scroll_area->item_count()%2 == 0)
        ui->fast_channel_scroll_area->AddWidget(new_channel,ui->fast_channel_scroll_area->item_count()/2,0);
    else{
        ui->fast_channel_scroll_area->AddWidget(new_channel,ui->fast_channel_scroll_area->item_count()/2,1);
    }
}
