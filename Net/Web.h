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
        ////TODO: �ھ�̬������ʵ����web_instance_��LNK2001����
        return web_instance_;
    }
    void Init(){
        connect(manage_, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(OnReplyFinished(QNetworkReply*)));
    }
    ~Web();
    bool Get(const QString& url,const QObject* receiver);
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

