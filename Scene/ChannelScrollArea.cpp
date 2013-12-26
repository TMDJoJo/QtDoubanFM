#include "ChannelScrollArea.h"
#include <QDebug>

ChannelScrollArea::ChannelScrollArea(QWidget *parent) :
    QScrollArea(parent),
    grid_layout_(NULL),
    item_count_(0),
    scroll_area_widget_contents(NULL)
{

    scroll_area_widget_contents = new QWidget();
    Q_ASSERT(scroll_area_widget_contents);
    scroll_area_widget_contents->setObjectName("scroll_area_widget_contents");
    scroll_area_widget_contents->setAutoFillBackground(false);
    grid_layout_ = new QGridLayout(scroll_area_widget_contents);
    Q_ASSERT(grid_layout_);

    grid_layout_->setVerticalSpacing(5);
    grid_layout_->setHorizontalSpacing(5);
    grid_layout_->setContentsMargins(0,10,0,10);

    this->setWidget(scroll_area_widget_contents);
    this->setWidgetResizable(true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

ChannelScrollArea::~ChannelScrollArea(){
    ////手动析构与QT自身半自动析构同时使用注意事项
    ////QT自动回收内存 不会讲起儿子的指针置空
    ////以下执行顺序颠倒后执行析构是崩溃
    SAFE_DELETE(grid_layout_);
    SAFE_DELETE(scroll_area_widget_contents);
}

void ChannelScrollArea::AddWidget(QWidget* widget,int row,int column,Qt::Alignment alignment /*= 0*/){
    if(NULL == widget)
        return;
    //widget->setParent(this);
    if(NULL != grid_layout_){
        grid_layout_->addWidget(widget,row,column,alignment);
        ++item_count_;
    }

}

