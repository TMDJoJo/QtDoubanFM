#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPainter>
#include <QToolButton>
#include <QApplication>

#include "./Scene/PlayScene.h"
#include "./Fm/ActionDispatch.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    pause_button_(NULL),
    close_button_(NULL),
    play_button_(NULL)
{
    ui->setupUi(this);
    InitUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUi(){
    ////���ô������������
    setWindowFlags(Qt::FramelessWindowHint);

    ////����QSS��ʽ��
    QFile file(":/Qss/Resource/Qss/MainWindow.css");
    if (file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
    }
    file.close();

    this->setAutoFillBackground(true);

    ////�����رհ�ť
    close_button_= new QToolButton(this);
    Q_ASSERT(close_button_);
    close_button_->setObjectName("main_close_btn");
    close_button_->setGeometry(this->width()-20, 0, 20, 20);
    close_button_->setCursor(Qt::PointingHandCursor);
    QObject::connect(close_button_, SIGNAL(clicked()),qApp, SLOT(quit()));

    pause_button_ = new QToolButton(this);
    Q_ASSERT(pause_button_);
    pause_button_->setObjectName("main_pause_btn");
    pause_button_->setGeometry(this->width()-45,0,25,25);
    pause_button_->setCursor(Qt::PointingHandCursor);
    connect(pause_button_, SIGNAL(clicked()),this, SLOT(OnPause()));

    play_button_ = new QPushButton(this);
    Q_ASSERT(play_button_);
    play_button_->setObjectName("main_play_btn");
    play_button_->setGeometry(176,0,244,190);
    play_button_->setText(tr("�������� >"));
    play_button_->setCursor(Qt::PointingHandCursor);
    play_button_->setFocusPolicy(Qt::NoFocus);
    play_button_->hide();
    connect(play_button_, SIGNAL(clicked()),this, SLOT(OnPlay()));

    pause_button_->stackUnder(ui->channel_scene);
    play_button_->stackUnder(ui->channel_scene);

    pause_button_->stackUnder(play_button_);
    close_button_->stackUnder(play_button_);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    moveing_ = true;
    move_position_ = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (moveing_
        &&(event->buttons() == Qt::LeftButton)
        &&(event->globalPos()-move_position_).manhattanLength() > QApplication::startDragDistance()
        ){
        move(event->globalPos()-move_position_);
        move_position_ = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    //�������Ϊδ������
    moveing_ = false;
    //event->accept();
    return QWidget::mouseReleaseEvent(event);
}

void MainWindow::paintEvent(QPaintEvent*){

    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void MainWindow::OnPause(){
    g_action_dispatch->Pause();
    play_button_->show();
}

void MainWindow::OnPlay(){
    g_action_dispatch->Play();
    play_button_->hide();
}
