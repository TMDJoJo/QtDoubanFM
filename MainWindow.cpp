#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPainter>
#include <QToolButton>
#include <QApplication>

#include "./Scene/PlayScene.h"
#include "./Fm/ActionDispatch.h"
#include "./Fm/Music/Music.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    pause_button_(NULL),
    close_button_(NULL),
    play_button_(NULL),
    tray_(NULL),
    tray_menu_(NULL)
{
    ui->setupUi(this);
    InitUi();
    InitTray();
    connect(g_music,SIGNAL(StateChangePlaying()),this,SLOT(OnStateChangePlaying()));
    connect(g_music,SIGNAL(StateChangePaused()),this,SLOT(OnStateChangePaused()));
    connect(tray_,SIGNAL(Show()),this,SLOT(OnShow()));

    this->activateWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
    SAFE_DELETE(close_button_);
    SAFE_DELETE(pause_button_);
    SAFE_DELETE(play_button_);
    SAFE_DELETE(tray_);
    SAFE_DELETE(tray_menu_);
}

void MainWindow::InitUi(){

    this->setWindowTitle(tr("豆瓣电台"));
    ////设置窗体标题栏隐藏
    setWindowFlags(Qt::FramelessWindowHint);

    ////设置QSS样式表
    QFile file(":/Qss/Resource/Qss/MainWindow.css");
    if (file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(file.readAll());
    }
    file.close();

    this->setAutoFillBackground(true);

    ////构建关闭按钮
    close_button_= new QToolButton(this);
    Q_ASSERT(close_button_);
    close_button_->setObjectName("main_close_btn");
    close_button_->setGeometry(this->width()-20, 0, 20, 20);
    close_button_->setCursor(Qt::PointingHandCursor);
    QObject::connect(close_button_, SIGNAL(clicked()),this,SLOT(OnCloseButtonClicked()));

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
    play_button_->setText(tr("继续播放 >"));
    play_button_->setCursor(Qt::PointingHandCursor);
    play_button_->setFocusPolicy(Qt::NoFocus);
    play_button_->hide();
    connect(play_button_, SIGNAL(clicked()),this, SLOT(OnPlay()));

    pause_button_->stackUnder(ui->channel_scene);
    play_button_->stackUnder(ui->channel_scene);

    pause_button_->stackUnder(play_button_);
    close_button_->stackUnder(play_button_);
}

void MainWindow::InitTray(){
    tray_ = new Tray(this);
    tray_menu_ = new TrayIconMenu(this);
    Q_ASSERT(tray_);
    Q_ASSERT(tray_menu_);

    tray_->setContextMenu(tray_menu_);
    tray_->setToolTip(tr("豆瓣电台"));
    tray_->show();
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
    //设置鼠标为未被按下
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
}

void MainWindow::OnPlay(){
    g_action_dispatch->Play();
}

void MainWindow::OnStateChangePlaying(){
    play_button_->hide();
}

void MainWindow::OnStateChangePaused(){
    play_button_->show();
}

void MainWindow::OnCloseButtonClicked(){
    this->showMinimized();
    this->hide();
}

void MainWindow::OnShow(){
    if(this->isHidden()
            ||this->isMinimized()){
        this->showNormal();
    }
    else{}
    this->activateWindow();
}
