#include "DouBanWeb.h"
#include <QDebug>
#include <QPixmap>

#include "Include/json/json.h"
#include "../Common.h"

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

bool DouBanWeb::GetNewList(const QString& arg){
    QNetworkReply* reply = Get(
                "http://douban.fm/j/mine/playlist?" + arg
                );
    connect(reply, SIGNAL(finished()),
            this, SLOT(OnReceivedNewList()));
    return true;
}

bool DouBanWeb::LikeSong(const QString& arg){
    QNetworkReply* reply = Get(
                "http://douban.fm/j/mine/playlist?" + arg
                );
    connect(reply, SIGNAL(finished()),
            this, SLOT(OnReceivedNewList()));
    return true;
}

bool DouBanWeb::TrashSong(const QString& arg){
    QNetworkReply* reply = Get(
                "http://douban.fm/j/mine/playlist?" + arg
                );
    connect(reply, SIGNAL(finished()),
            this, SLOT(OnReceivedNewList()));
    return true;
}

bool DouBanWeb::GetAlbumPicture(const QString& url){
    QNetworkReply* reply = Get(url);
    if(NULL == reply)
        return false;
    connect(reply,SIGNAL(finished()),this,SLOT(OnReceivedAlbumPicture()));
    return true;
}

bool DouBanWeb::GetChannelId(const QString& url){
    QNetworkReply* reply = Get(url);
    if(NULL == reply)
        return false;
    connect(reply,SIGNAL(finished()),this,SLOT(OnReceivedChannelId()));
    return true;
}

void DouBanWeb::OnReceivedNewList(){
    QNetworkReply* reply = dynamic_cast<QNetworkReply*>(sender());
    ////接收到新播放列表
    Q_ASSERT(reply);
    QString reply_string = QString::fromUtf8(reply->readAll());
    reply->deleteLater();
    ////处理jsons
    Json::Reader* reader = new Json::Reader;
    Q_ASSERT(reader);
    Json::Value* root = new Json::Value;
    Q_ASSERT(root);
    if(reader->parse(reply_string.toUtf8().data(),*root)){
        // reader将Json字符串解析到root，root将包含Json里所有子元素

        if((*root)["r"].isNull()
                ||(*root)["r"].asInt() != 0){
            QString err_string = (*root)["err"].asString().c_str();
            qDebug()<<err_string;
            ////接受错误
            SAFE_DELETE(reader);
            SAFE_DELETE(root);
            return;
        }

        if(!(*root)["song"].isNull()){
            int song_size = (*root)["song"].size();
            SongList* new_song_list = new SongList;
            Q_ASSERT(new_song_list);
            for(int index = 0;index < song_size;++index){
                DouBanSong* new_song = new DouBanSong;
                Q_ASSERT(new_song);
                new_song->aid_ = (*root)["song"][index]["aid"].asString().c_str();
                new_song->albumtitle_ = (*root)["song"][index]["albumtitle"].asString().c_str();
                new_song->album_ = (*root)["song"][index]["album"].asString().c_str();
                new_song->artist_ = (*root)["song"][index]["artist"].asString().c_str();
                new_song->company_ = (*root)["song"][index]["company"].asString().c_str();
                new_song->kbps_ = (*root)["song"][index]["kbps"].asString().c_str();
                new_song->length_ = (*root)["song"][index]["length"].asUInt();
                new_song->like_ = (*root)["song"][index]["like"].asBool();
                new_song->picture_ = (*root)["song"][index]["picture"].asString().c_str();
                new_song->public_time_ = (*root)["song"][index]["public_time"].asString().c_str();
                new_song->rating_avg_ = (*root)["song"][index]["rating_avg"].asDouble();
                new_song->sha256_ = (*root)["song"][index]["sha256"].asString().c_str();
                new_song->sid_ = (*root)["song"][index]["sid"].asString().c_str();
                new_song->ssid_ = (*root)["song"][index]["ssid"].asString().c_str();
                new_song->subtype_ = (*root)["song"][index]["subtype"].asString().c_str();
                new_song->title_ = (*root)["song"][index]["title"].asString().c_str();
                new_song->url_ = (*root)["song"][index]["url"].asString().c_str();

                new_song_list->push_back(new_song);
            }
            ////TODO: 回写数据
            emit ReceivedNewList(new_song_list);
        }
    }
    else{
        qDebug()<<"json parse fail";
    }

    SAFE_DELETE(reader);
    SAFE_DELETE(root);
}

void DouBanWeb::OnReceivedAlbumPicture(){
    QNetworkReply* reply = dynamic_cast<QNetworkReply*>(sender());
    ////接收到新播放列表
    Q_ASSERT(reply);
    if(reply->error() == QNetworkReply::NoError){
        QPixmap* picture = new QPixmap();
        Q_ASSERT(picture);
        if( !picture->loadFromData(reply->readAll()) ){
            reply->deleteLater();
            return;
        }
        reply->deleteLater();
        emit ReceivedAlbumPicture(picture);
    }
}
#include <QFile>
void DouBanWeb::OnReceivedChannelId(){
    QNetworkReply* reply = dynamic_cast<QNetworkReply*>(sender());
    ////接收到新播放列表
    Q_ASSERT(reply);
    if(reply->error() == QNetworkReply::NoError){

        QString douban_fm_html = reply->readAll();
//        QFile file("./aaa.txt");
//        file.open(QIODevice::ReadWrite);
//        file.write(douban_fm_html.toStdString().c_str());
//        file.close();
//        douban_fm_html

        QRegExp reg(".*window.hot_channels_json = \\[(.*)\\];\n.*window.fast_channels_json = \\[(.*)\\];\n.*window.com_channels_json =.*");
        if(reg.exactMatch(douban_fm_html)){
            qDebug()<<reg.cap(1);
            qDebug()<<reg.cap(2);
//            qDebug()<<reg.cap(3);
        }

//        QStringList labelList = douban_fm_html.split('\n');
//        qDebug()<<labelList.size();
//        QStringList::Iterator it = labelList.begin();
//        while(it != labelList.end()){
//            QRegExp reg(".*window.hot_channels_json = \\[(.+)\\];");

//            if(reg.exactMatch(*it)){
//                qDebug()<<reg.cap(1);
//                //qDebug()<<*it;
//            }

//            ++it;
//        }
    }

}
