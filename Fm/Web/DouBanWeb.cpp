#include "DouBanWeb.h"
#include <QDebug>

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
    QString reply_string = QString::fromUtf8(reply->readAll());
    reply->deleteLater();

    ////处理jsons
    Json::Reader* reader = new Json::Reader;
    Q_ASSERT(reader);
    Json::Value* root = new Json::Value;
    Q_ASSERT(root);
    if(reader->parse(reply_string.toStdString(),*root)){
        // reader将Json字符串解析到root，root将包含Json里所有子元素

        if((*root)["r"].isNull()
                ||(*root)["r"].asInt() != 0){
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
