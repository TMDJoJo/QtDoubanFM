#include "Web.h"
#include <QDebug>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "Include/json/json.h"

Web::Web(QObject *parent) :
    QObject(parent),
    manage_(NULL)
{
    manage_ = new QNetworkAccessManager(this);
    Q_ASSERT(manage_);
    connect(manage_, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(OnReplyFinished(QNetworkReply*)));

    manage_->get(
                QNetworkRequest(
                    QUrl("http://douban.fm/j/mine/playlist?type=n&sid=&pt=0.0&channel=32&from=mainsite&r=259d4b0a31")
                    )
                );

}

Web::~Web(){
    SAFE_DELETE(manage_);
}

void Web::OnReplyFinished(QNetworkReply* reply){
    if(NULL == reply)
        return ;

    if (reply->error() == QNetworkReply::NoError){
        //read some thing
        QString str = QString::fromUtf8(reply->readAll().data());
        Json::Reader reader;
        Json::Value root;
        if(reader.parse(str.toStdString(), root)){
            // reader将Json字符串解析到root，root将包含Json里所有子元素
            qDebug()<<root["r"].asInt();
            if(!root["song"].isNull()){
                int size = root["song"].size();
                for(int index = 0;index < size;++index){
                    qDebug()<<root["song"][index]["title"].asString().c_str();
                    qDebug()<<root["song"][index]["url"].asString().c_str();
                }
            }
        }

    }
    else{
        //出错
        QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        //status_code是HTTP服务器的相应码
        qDebug( "error code: %d %d\n", status_code.toInt(), (int)reply->error());
        qDebug(qPrintable(reply->errorString()));
        return ;
    }
}
