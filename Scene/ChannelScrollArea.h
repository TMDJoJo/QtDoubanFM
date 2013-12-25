#ifndef CHANNELSCROLLAREA_H
#define CHANNELSCROLLAREA_H

#include <QScrollArea>
#include <QGridLayout>
#include <QWidget>
#include <QResizeEvent>

#include "../Fm/Common.h"

class ChannelScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit ChannelScrollArea(QWidget *parent = 0);
    ~ChannelScrollArea();

    void AddWidget(QWidget*,int row,int column,Qt::Alignment alignment = 0);
    inline quint32 item_count(){ return item_count_; }

signals:
    
public slots:
private:
    QGridLayout* grid_layout_;

    QWidget* scroll_area_widget_contents;

    quint32 item_count_;
};

#endif // CHANNELSCROLLAREA_H
