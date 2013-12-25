#include "AlbumScene.h"
#include "ui_AlbumScene.h"
#include <QDebug>

AlbumScene::AlbumScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumScene),
    is_pressed_(false)
{
    ui->setupUi(this);

    this->setCursor(Qt::PointingHandCursor);
    this->setAutoFillBackground(false);
    this->setMouseTracking(true);
    ui->album_shadow->hide();
    ////设置QSS样式表
    QFile file(":/Qss/Resource/Qss/AlbumScene.css");
    if (file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
    }
    file.close();

}

AlbumScene::~AlbumScene(){
    delete ui;
}

void AlbumScene::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        is_pressed_ = true;
        event->accept();
    }
    else
        return QWidget::mousePressEvent(event);
}

void AlbumScene::mouseReleaseEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton
            &&is_pressed_
            &&event->pos().x() > 0
            &&event->pos().x() < this->width()
            &&event->pos().y() > 0
            &&event->pos().y() < this->height()){
        is_pressed_ = false;
        emit clicked();
        event->accept();
    }
    else{
        return QWidget::mouseReleaseEvent(event);
    }
}

void AlbumScene::enterEvent(QEvent* event){
    ui->album_shadow->show();
    return QWidget::enterEvent(event);
}

void AlbumScene::leaveEvent(QEvent* event){
    is_pressed_ = false;
    ui->album_shadow->hide();
    return QWidget::leaveEvent(event);
}
