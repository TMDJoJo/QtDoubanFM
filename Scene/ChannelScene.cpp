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

    QGridLayout* hot_layout = new QGridLayout;
    hot_layout->setVerticalSpacing(45);
    hot_layout->setHorizontalSpacing(5);
    ui->hot_channel->setLayout(hot_layout);

    QGridLayout* fast_layout = new QGridLayout;
    fast_layout->setVerticalSpacing(45);
    fast_layout->setHorizontalSpacing(5);
    ui->fast_channel->setLayout(fast_layout);

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

void ChannelScene::AddHotChannel(const DouBanChannel* channel){

    Channel* new_channel = new Channel();
    Q_ASSERT(new_channel);
    new_channel->set_channel_name(channel->name_);
    new_channel->set_song_num(channel->song_num_);
    new_channel->set_channel_id(channel->id_);
    connect(new_channel,SIGNAL(clicked(quint32)),
            this,SLOT(OnChannelClicked(quint32)));
    QGridLayout* layout = dynamic_cast<QGridLayout*>(ui->hot_channel->layout());

    if(layout->count()%2 == 0)
        layout->addWidget(new_channel,layout->count()/2,0);
    else{
        layout->addWidget(new_channel,layout->count()/2,1);
    }

}

void ChannelScene::AddFastChannel(const DouBanChannel* channel){
    Channel* new_channel = new Channel();
    Q_ASSERT(new_channel);
    new_channel->set_channel_name(channel->name_);
    new_channel->set_song_num(channel->song_num_);
    new_channel->set_channel_id(channel->id_);

    connect(new_channel,SIGNAL(clicked(quint32)),
            this,SLOT(OnChannelClicked(quint32)));

    QGridLayout* layout = dynamic_cast<QGridLayout*>(ui->fast_channel->layout());

    if(layout->count()%2 == 0)
        layout->addWidget(new_channel,layout->count()/2,0);
    else{
        layout->addWidget(new_channel,layout->count()/2,1);
    }
}
