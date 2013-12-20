#ifndef DOUBANWEB_H
#define DOUBANWEB_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

#include "../Type/DouBanSong.h"

const QChar GET_SONG_NEXT = 's';    ////return song list
const QChar GET_SONG_LIKE = 'r';    ////return song list
const QChar GET_SONG_UNLIKE = 'u';  ////return song list
const QChar GET_SONG_END = 'e';     ////return {"r":0}
const QChar GET_SONG_XXX = 'n';     ////return song list

class DouBanWeb : public QObject
{
    Q_OBJECT
public:
    explicit DouBanWeb(QObject *parent = 0);

//    static DouBanWeb& Instance(){
//        ////TODO: 在静态函数内实例化web_instance_出LNK2001错误
//        return web_instance_;
//    }
    bool GetNewList(/*prame*/);
    bool LikeSong(/*prame*/);
    bool TrashSong(/*prame*/);
    bool GetAlbumPicture(const QString url);
signals:
    void ReceivedNewList(SongList*);
    void ReceivedAlbumPicture(QPixmap*);
private slots:
    void OnReceivedNewList();
    void OnReceivedAlbumPicture();
private:
    QNetworkReply* Get(const QString& url);

private:
    QNetworkAccessManager* network_manage_;
};

extern DouBanWeb* g_douban_web;
#endif // DOUBANWEB_H
