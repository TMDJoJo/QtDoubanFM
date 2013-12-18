#include "DouBanWeb.h"
#include <QDebug>

DouBanWeb* g_douban_web = NULL;

DouBanWeb::DouBanWeb(QObject *parent) :
    QObject(parent),
    network_manage_(NULL)
{
    network_manage_ = new QNetworkAccessManager(this);
    if(NULL == network_manage_){
        qDebug()<<"err";
    }
    Q_ASSERT(network_manage_);
}

QNetworkReply* DouBanWeb::Get(const QString& url){

    if(NULL == network_manage_)
        return NULL;
    ////函数异步
    return network_manage_->get( QNetworkRequest(QUrl(url)) );
}

bool DouBanWeb::GetNewList(/*prame*/){
    QNetworkReply* reply = Get(
                "http://douban.fm/j/mine/playlist?type=n&sid=&pt=0.0&channel=6&from=mainsite&r=54fb71862a"
                );
    connect(reply, SIGNAL(finished()),
            this, SLOT(OnReceivedNewList()));
    return true;
}

bool DouBanWeb::LikeSong(/*prame*/){

    return true;
}

bool DouBanWeb::TrashSong(/*prame*/){

    return true;
}

void DouBanWeb::OnReceivedNewList(){
    QNetworkReply* reply = dynamic_cast<QNetworkReply*>(sender());
    ////接收到新播放列表
    Q_ASSERT(reply);
    qDebug()<<reply->readAll();
    ////处理jsons


    reply->deleteLater();
}
