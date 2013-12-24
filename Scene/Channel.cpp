#include "Channel.h"
#include "ui_Channel.h"
#include <QDebug>

Channel::Channel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Channel)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
}

Channel::~Channel()
{
    delete ui;
}

void Channel::set_channel_name(const QString name){
    ui->channel_name->setText(name);
}

void Channel::set_song_num(quint32 num){
    ui->song_num->setText(QString::number(num));
}

void Channel::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        emit clicked(channel_id_);
    }
}
