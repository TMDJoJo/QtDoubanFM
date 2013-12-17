#include "Web.h"
#include <QDebug>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "Include/json/json.h"

Web Web::web_instance_;

Web::Web(QObject *parent) :
    QObject(parent),
    manage_(NULL)
{
    manage_ = new QNetworkAccessManager(this);
    if(NULL == manage_){
        qDebug()<<"err";
    }
    Q_ASSERT(manage_);
}

Web::~Web(){
    SAFE_DELETE(manage_);
}

//Web* Web::Instance(){
//    if(NULL == web_){
//        web_ = new Web();
//        Q_ASSERT(web_);
//    }
//    return web_;
//}

bool Web::Get(const QString& url,const QObject* receiver){

    if(NULL == manage_)
        return false;
    ////次函数异步
    QNetworkReply* reply = manage_->get( QNetworkRequest(QUrl(url)) );
    connect(manage_, SIGNAL(finished(QNetworkReply*)),
            receiver, SLOT(method(QNetworkReply*)));
    return NULL;
}

void Web::OnReplyFinished(QNetworkReply* reply){
    qDebug()<<"OnReplyFinished"<<reply;
    if(NULL == reply)
        return ;

    if (reply->error() == QNetworkReply::NoError){
        //read some thing
        //qDebug()<<QString::fromUtf8( reply->readAll() );
        QString str = QString::fromUtf8( reply->readAll() );

        Json::Reader reader;
        Json::Value root;
        if(reader.parse(str.toStdString(), root)){
            // reader将Json字符串解析到root，root将包含Json里所有子元素

            if(!root["song"].isNull()){
                int size = root["song"].size();
                for(int index = 0;index < size;++index){
                    qDebug()<<root["song"][index]["title"].asString().c_str();
                    //qDebug()<<root["song"][index]["url"].asString().c_str();
                }
            }
        }
        else{
            qDebug()<<"json parse fail";
        }

    }
    else{
        //出错
        QVariant status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        //status_code是HTTP服务器的相应码
        qDebug( "error code: %d %d\n", status_code.toInt(), (int)reply->error());
        qDebug(qPrintable(reply->errorString()));
    }
}
