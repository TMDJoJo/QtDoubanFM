#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPainter>
#include <QToolButton>

#include "./Scene/PlayScene.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}
#include <QApplication>
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
    QObject::connect(close_button_, SIGNAL(clicked()), qApp, SLOT(quit()));

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
