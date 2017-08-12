#ifndef NETWORKXML_H
#define NETWORKXML_H



#include <QVariantList>
#include <QIODevice>

#include "networkattributes.h"



class networkxml
{
public:
  QString name;
  QString UUID=nullptr;
  //TODO must impliment domain  element in ui
  QString domainName;
  QString localOnly=nullptr;
  bool isforwardExist=false;
  Forward forward;
  Bridge bridge;
  bw bandwidth;
  IP4 ip4;
  IP6 ip6;
  QList<Route> route;
  //Dns dns;

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
