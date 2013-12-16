#ifndef WEB_H
#define WEB_H

#include <QObject>
#include <QNetworkAccessManager>

#include "../Common.h"

class Web : public QObject
{
    Q_OBJECT
public:
    explicit Web(QObject *parent = 0);
    ~Web();
signals:
    
private slots:
    void OnReplyFinished(QNetworkReply*);

private:
    QNetworkAccessManager* manage_;
};

#endif // WEB_H
