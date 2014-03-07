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
public:
    enum GetNewListType{
        FINISH_SONG     = 0,
        LIKE               ,
        TRASH              ,
        NEXT               ,
        END_LIST
    };
    Q_OBJECT
public:
    explicit DouBanWeb(QObject *parent = 0);

    void GetNewList(const QString& arg,GetNewListType type);
    bool GetAlbumPicture(const QString& url);

    bool GetChannelId(const QString& arg);
signals:
    void ReceivedNewList(SongList*);
    void ReceivedAlbumPicture(QPixmap*);

    void ReceivedHotChannels(ChannelList*);
    void ReceivedFastChannels(ChannelList*);
private slots:
    void OnFinishReceivedNewList();
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
