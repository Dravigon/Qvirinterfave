#ifndef NETWORKXML_H
#define NETWORKXML_H

#include <QDebug>
#include <QString>
#include <QVector>
#include <QIODevice>
#include <QXmlStreamReader>

struct Nat{
    QString start;
    QString end;
};

struct Forward{
    QString mode;
    QString dev=NULL;
    bool natExist=false;
    Nat nat;
};
struct Bridge{
    bool exist;
    QString name;
    QString stp=NULL;
    QString delay=NULL;
};
struct Qos{
    QString average=NULL;
    QString peak=NULL;
    QString burst=NULL;
};
struct bw{
    bool exist;
    Qos inbound;
    Qos outbound;
};
struct HOST{
    QString id=NULL;
    QString mac=NULL;
    QString name=NULL;
    QString ip=NULL;
};
struct Dhcp{
    struct Range{
        bool exist=false;
        QString start=NULL;
        QString end;
    }range;
    bool hasHost;
    QVector<HOST> host;
};
struct IP
{
    QString family=NULL;
    QString address;
    QString prefix=NULL;
    QString netmask=NULL;
    bool hasDhcp;
    Dhcp dhcp;
};
struct Route{
    QString family=NULL;
    QString address;
    QString prefix=NULL;
    QString netmask=NULL;
    QString gateway=NULL;
};


class networkxml
{
public:
    QString name;
    bool isforwardExist;
    Forward forward;
    Bridge bridge;
    bw bandwidth;
    QVector<IP>ip;
    QVector<Route> route;

    QIODevice *device;
public:
    networkxml(){

    }
    void setnet(networkxml temp);
    networkxml(QIODevice *dev);
    int read();
    int write();
};

#endif // NETWORKXML_H
