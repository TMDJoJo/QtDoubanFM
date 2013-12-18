#ifndef DOUBANSONG_H
#define DOUBANSONG_H
#include <QString>
#include <QList>

/*    example
aid: "3075444"
album: "/subject/3075444/"
albumtitle: "��������04�����ݳ���"
artist: "̷ӽ�� / �����"
company: "Universal"
kbps: "64"
length: 201
like: 0
picture: "http://img5.douban.com/mpic/s3903877.jpg"
public_time: "2004"
rating_avg: 4.18118
sha256: "94ffc90aafe7311c504be7bf5ed146c2f57c949ef9efa664c54590529d875ddd"
sid: "40753"
ssid: "a106"
subtype: ""
title: "һ������"
url: "http://mr4.douban.com/201312181753/ea16659aa3b53a5da5d7b76487ee7afb/view/song/small/p40753.mp3"
*/

struct DouBanSong_T{
    QString album_;
    QString picture_;
    QString ssid_;
    QString artist_;
    QString url_;
    QString company_;
    QString title_;
    QString sha256_;
    QString albumtitle_;
    QString subtype;
    QString public_time_;
    double rating_avg_;
    quint32 length_;
    quint32 sid_;
    quint32 aid_;
    quint32 kbps_;
    bool like_;
};

typedef struct DouBanSong_T DouBanSong;

typedef QList<DouBanSong*> SongList;
#endif // DOUBANSONG_H
