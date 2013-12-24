#ifndef DOUBANWEB_H
#define DOUBANWEB_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

#include "../Type/DouBanSong.h"
#include "../Type/DouBanChannel.h"

class DouBanWeb : public QObject
{
    Q_OBJECT
public:
    explicit DouBanWeb(QObject *parent = 0);

//    static DouBanWeb& Instance(){
//        ////TODO: 在静态函数内实例化web_instance_出LNK2001错误
//        return web_instance_;
//    }
    bool GetNewList(const QString& arg);
    bool LikeSong(const QString& arg);
    bool TrashSong(const QString& arg);
    bool GetAlbumPicture(const QString& url);

    bool GetChannelId(const QString& arg);
signals:
    void ReceivedNewList(SongList*);
    void ReceivedAlbumPicture(QPixmap*);

    void ReceivedHotChannels(ChannelList*);
    void ReceivedFastChannels(ChannelList*);
private slots:
    void OnReceivedNewList();
    void OnReceivedAlbumPicture();
    void OnReceivedChannelId();
private:
    QNetworkReply* Get(const QString& url);
    ChannelList* ParseChannelList(const QString& str);

private:
    QNetworkAccessManager* network_manage_;
};

extern DouBanWeb* g_douban_web;
#endif // DOUBANWEB_H
