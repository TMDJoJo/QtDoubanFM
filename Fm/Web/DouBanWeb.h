#ifndef DOUBANWEB_H
#define DOUBANWEB_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

#include "../Type/DouBanSong.h"

class DouBanWeb : public QObject
{
    Q_OBJECT
public:
    explicit DouBanWeb(QObject *parent = 0);

//    static DouBanWeb& Instance(){
//        ////TODO: �ھ�̬������ʵ����web_instance_��LNK2001����
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
private slots:
    void OnReceivedNewList();
    void OnReceivedAlbumPicture();
    void OnReceivedChannelId();
private:
    QNetworkReply* Get(const QString& url);

private:
    QNetworkAccessManager* network_manage_;
};

extern DouBanWeb* g_douban_web;
#endif // DOUBANWEB_H
