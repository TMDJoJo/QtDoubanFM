#ifndef DOUBANCHANNEL_H
#define DOUBANCHANNEL_H
#include <QString>
#include <QList>

//{
//  "intro": "生于八零年代的我们，听着这些歌成长",
//  "name": "八零",
//  "song_num": 6056,
//  "creator": {
//    "url": "http:\/\/site.douban.com\/douban.fm\/",
//    "name": "豆瓣FM",
//    "id": 1
//  },
//  "banner": "http:\/\/img5.douban.com\/img\/fmadmin\/chlBanner\/26386.jpg",
//  "cover": "http:\/\/img5.douban.com\/img\/fmadmin\/icon\/26386.jpg",
//  "id": 4,
//  "hot_songs": [
//    "Because Of You",
//    "U Make Me Wanna",
//    "You're Beautiful"
//  ]
//}

struct DouBanChannel_T{
    QString intro_;
    QString name_;
    QString banner_;
    QString cover_;
    quint32 id_;
    quint32 song_num_;
    QList<QString> hot_songs_;
    ////TODO: with out creator info
};

typedef struct DouBanChannel_T DouBanChannel;
typedef QList<DouBanChannel*> ChannelList;
#endif // DOUBANCHANNEL_H
