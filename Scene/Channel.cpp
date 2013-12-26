#include "Channel.h"
#include "ui_Channel.h"
#include <QDebug>
#include <QFile>
#include <QPainter>

Channel::Channel(DouBanChannel* channel,QWidget *parent /*= 0*/) :
    QWidget(parent),
    ui(new Ui::Channel),
    channel_(channel)
{
    ui->setupUi(this);

    this->setCursor(Qt::PointingHandCursor);
    this->setAutoFillBackground(false);

    ui->channel_name->setText(channel_->name_ + tr("MHz"));
    ui->song_num->setText(QString::number(channel_->song_num_) + tr("首歌曲"));

    QString tool_tip;
    if(!channel_->intro_.isEmpty()){
        tool_tip += tr("<b>简介：</b><font color=#888888>") + channel_->intro_ + tr("</font>");
    }
    if(channel_->hot_songs_.size() > 0){
        if(!tool_tip.isEmpty()){
            tool_tip += tr("<br>");
        }
        tool_tip += tr("<b>热门歌曲：</b><font color=#888888>") + channel_->hot_songs_.join("/") + tr("</font>");
    }
    this->setToolTip(tool_tip);

    ////设置QSS样式表
    QFile file(":/Qss/Resource/Qss/Channel.css");
    if (file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
    }
    file.close();
}


Channel::~Channel()
{
    SAFE_DELETE(channel_);
    delete ui;
}

void Channel::paintEvent(QPaintEvent*){

    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void Channel::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        is_pressed_ = true;
        event->accept();
    }
    else
        return QWidget::mousePressEvent(event);
}

void Channel::mouseReleaseEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton
            &&is_pressed_
            &&event->pos().x() > 0
            &&event->pos().x() < this->width()
            &&event->pos().y() > 0
            &&event->pos().y() < this->height()){
        is_pressed_ = false;
        emit clicked(channel_->id_);
        event->accept();
    }
    else{
        return QWidget::mouseReleaseEvent(event);
    }
}

void Channel::leaveEvent(QEvent* event){
    is_pressed_ = false;
    return QWidget::leaveEvent(event);
}
