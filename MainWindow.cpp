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
    tray_menu_(NULL),
    music_(NULL),
    douban_web_(NULL)
{
    ui->setupUi(this);
    InitUi();
    InitTray();
    InitMusic();

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
    QFile qss_file(":/Qss/Resource/Qss/MainWindow.css");
    if (qss_file.open(QIODevice::ReadOnly)){
        this->setStyleSheet(qss_file.readAll());
        qss_file.close();
    }

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

    connect(tray_,SIGNAL(Show()),this,SLOT(OnShow()));
}

void MainWindow::InitWeb(){
    ////客户端与web通信
    douban_web_ = new DouBanWeb(this);
    Q_ASSERT(douban_web_);
    connect(douban_web_,SIGNAL(ReceivedNewList(SongList*)),
            music_,SLOT(OnReceivedNewList(SongList*)));
}

void MainWindow::InitMusic(){
    music_ = new Music(this);
    Q_ASSERT(music_);
    connect(music_,SIGNAL(StateChanged(Music::Music_State,Music::Music_State)),
            this,SLOT(OnStateChangePlaying()));

    connect(music_,SIGNAL(PlayTimeTick(qint64,qint64)),
            this,SLOT(OnPlayTimeTick(qint64,qint64)));
    connect(music_,SIGNAL(SongAboutFinish(const DouBanSong*)),
            this,SLOT(OnSongAboutFinish(const DouBanSong*)));
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    moveing_ = true;
    move_position_ = event->globalPos()-pos();
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
    ////暂停
    if(NULL != music_)
        music_->Pause();
}

void MainWindow::OnPlay(){
    ////播放
    if(NULL != music_)
        music_->Play();
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

void MainWindow::OnMusicStateChange(
        Music::Music_State new_state,Music::Music_State /*old_state*/){
    if(new_state == Music::PausedState){
        play_button_->show();
    }
    else if(new_state == Music::PlayingState){
        play_button_->hide();
    }
}

void MainWindow::OnPlayTimeTick(qint64 play_time,qint64 remaining_time){
    ui->play_scene->set_play_time(play_time,remaining_time);
}

////end of a song
////get  http://douban.fm/j/mine/playlist?type=e&sid=549095&channel=170&pt=107.7&pb=64&from=mainsite&r=778a1ca772
////reponse  {"r":0}
void MainWindow::OnSongAboutFinish(const DouBanSong* current_song){
    if(NULL == current_song)
            //||NULL == channel_scene_)
        return;
    QString song_id = current_song->sid_;
    QString channel_id = QString::number(ui->channel_scene->current_channel_id());
    QString play_time = QString("%1").arg(float(current_song->length_)/1);
    QString type = "e";
    QString arg = QString("type=%1"
                          "&sid=%2"
                          "&pt=%3"
                          "&channel=%4"
                          "&pb=%5"
                          "&from=%6").arg(
                type,
                song_id,play_time,
                channel_id,QString::number(64),
                "mainsite");
    douban_web_->GetNewList(arg,DouBanWeb::FINISH_SONG);
}

