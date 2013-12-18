#ifndef WEB_H
#define WEB_H

#include <QObject>
#include <QNetworkAccessManager>

#include "../Fm/Common.h"

class Web : public QObject
{

    Q_OBJECT
public:
    static Web& Instance(){
        ////TODO: 在静态函数内实例化web_instance_出LNK2001错误
        return web_instance_;
    }
    void Init(){
        connect(manage_, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(OnReplyFinished(QNetworkReply*)));
    }
    ~Web();
    QNetworkReply* Get(const QString& url);
signals:
    
private slots:
    void OnReplyFinished(QNetworkReply*);

private:
    explicit Web(QObject *parent = 0);

private:
    QNetworkAccessManager* manage_;

    static Web web_instance_;
};

#endif // WEB_H

