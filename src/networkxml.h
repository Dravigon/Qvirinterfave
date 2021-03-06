#ifndef NETWORKXML_H
#define NETWORKXML_H

#include <QDebug>
#include <QBuffer>
#include <QString>
#include <QVariantList>
#include <QIODevice>
#include <QXmlStreamReader>
#include <host.h>

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
    QString stp="on";
    QString delay="0";
};
struct Qos{
    QString average="50";
    QString peak="50";
    QString burst="50";
};
struct bw{
    bool exist;
    Qos inbound;
    Qos outbound;
};

struct Dhcp{
    struct Range{
        bool exist=false;
        QString start;
        QString end;
    }range;
    bool hasHost=false;
    HostModel *host=new HostModel();
};
struct IP4
{
    bool exist=false;
    QString family="ip4";
    QString address;
    QString netmask="255.255.255.0";
    bool hasDhcp=false;
    Dhcp dhcp;
    IP4(){

    }
};
struct IP6
{
    bool exist=false;
    QString family="ip6";
    QString address;
    QString prefix=NULL;
    bool hasDhcp=false;
    Dhcp dhcp;
    IP6(){

    }
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
    bool isforwardExist=false;
    Forward forward;
    Bridge bridge;
    bw bandwidth;
    IP4 ip4;
    IP6 ip6;
    QList<Route> route;
    QIODevice *device;
    networkxml(networkxml const &temp){
        name=temp.name;
        isforwardExist=temp.isforwardExist;
        forward=temp.forward;
        bridge=temp.bridge;
        bandwidth=temp.bandwidth;
        ip4=temp.ip4;
        ip6=temp.ip6;
        route=temp.route;
        device=temp.device;
    }
    networkxml(){
        isforwardExist=false;
        bridge.exist=false;
        bandwidth.exist=false;
    }

    void setnet(networkxml temp);
    void setXml(QIODevice *dev);
    networkxml(QIODevice *dev);
    int read();
    QString write();
};

#endif // NETWORKXML_H
