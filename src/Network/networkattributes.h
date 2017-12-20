#ifndef NETWORKATTRIBUTES_H
#define NETWORKATTRIBUTES_H
#include <QString>
#include <QXmlStreamWriter>
#include <QDebug>
#include "host.h"
#include <QBuffer>


class networkAttributes
{
public:
  networkAttributes();
};

class Nat:public QObject{

  QString start;
  QString end;

public:
 Nat(QObject *parent = nullptr);
  Nat(const Nat &value);
  QString xml();
  bool natExist();
  QString getStart() const;
  void setStart(const QString &value);
  QString getEnd() const;
  void setEnd(const QString &value);
};

class Forward{

  QString mode;
  QString dev=nullptr;
  QSharedPointer<Nat> nat =
      QSharedPointer<Nat>(new Nat, &QObject::deleteLater);

public:

  QString xml();
  bool isNat() const{
    return (mode=="nat");
  }
  QString getMode() const;
  void setMode(const QString &value);
  QString getDev() const;
  void setDev(const QString &value);
  Nat *getNat() const;
  void setNat(const Nat &value);
};
class Bridge{
  QString name;
  QString stp="on";
  QString delay="0";
public:
  Bridge(){}
  Bridge(QString name,QString stp,QString delay){
    this->name=name;
    this->stp=stp;
    this->delay=delay;
  }
  bool exist=false;
  QString xml();
  QString getName() const;
  void setName(const QString &value);
  QString getStp() const;
  void setStp(const QString &value);
  QString getDelay() const;
  void setDelay(const QString &value);
};
class Qos:public QObject{
  QString average="50";
  QString peak="50";
  QString burst="50";
public:
  Qos(){}
  Qos(const Qos &value);
  Qos(QString avg,QString peak,QString burst){
    average=avg;
    this->peak=peak;
    this->burst=burst;
  }
  QString xml(QString type);
  bool isEmpty(){
    return average.isEmpty()&&peak.isEmpty()&&burst.isEmpty();
  }
  QString getAverage() const;
  void setAverage(const QString &value);
  QString getPeak() const;
  void setPeak(const QString &value);
  QString getBurst() const;
  void setBurst(const QString &value);
};
class bw{

  QSharedPointer<Qos> inbound =
      QSharedPointer<Qos>(new Qos, &QObject::deleteLater);
  QSharedPointer<Qos> outbound =
      QSharedPointer<Qos>(new Qos, &QObject::deleteLater);

public:

  bool exist=false;
  QString xml();
  Qos *getInbound() const;
  void setInbound(const Qos &value);
  Qos *getOutbound() const;
  void setOutbound(const Qos &value);
};

class Range:public QObject{
public:
  Range();
  Range(const Range &value);
  bool exist=false;
  QString start;
  QString end;
};

class Dhcp{
  //Range range;
  QSharedPointer<Range> range =
      QSharedPointer<Range>(new Range, &QObject::deleteLater);

  HostModel *host;
public:
  bool hasHost;
  bool rangeExist(){
    return range->exist;
  }
  void rangeExist(bool val){
    range->exist=val;
  }
  Dhcp(){
    host=new HostModel;
  }
  Dhcp(QString start,QString end){
    host=new HostModel;
    range->start=start;
    range->end=end;
    range->exist=true;
  }

  void append(QStandardItem* item){
    host->appendRow(item);
  }
  Q_INVOKABLE int numberOfHost(){
    return host->rowCount();
  }
  QString xml(QString ForwardMode);
  Range *getRange() const;
  void setRange(const Range&value);
  HostModel *getHost() const;
  void setHost(HostModel *value);
  void setHasHost(bool value);
  bool getHasHost() const;
};
class IP4
{
  bool exist=false;
  QString family="ip4";
  QString address;
  QString netmask="255.255.255.0";
  bool hasDhcp=false;
  Dhcp dhcp;

public:
  IP4(){

  }
  QString xml();
  bool getExist() const;
  void setExist(bool value);
  QString getFamily() const;
  void setFamily(const QString &value);
  QString getAddress() const;
  void setAddress(const QString &value);
  QString getNetmask() const;
  void setNetmask(const QString &value);
  bool getHasDhcp() const;
  void setHasDhcp(bool value);
  Dhcp getDhcp() const;
  void setDhcp(const Dhcp &value);
};
class IP6
{
  bool exist=false;
  QString family="ip6";
  QString address;
  QString prefix=nullptr;
  bool hasDhcp=false;
  Dhcp dhcp;

public:
  IP6(){

  }
  QString getFamily() const;
  void setFamily(const QString &value);
  QString getAddress() const;
  void setAddress(const QString &value);
  QString getPrefix() const;
  void setPrefix(const QString &value);
  bool getHasDhcp() const;
  void setHasDhcp(bool value);
  Dhcp getDhcp() const;
  void setDhcp(const Dhcp &value);
  bool getExist() const;
  void setExist(bool value);
};
struct Route{
  QString family=nullptr;
  QString address;
  QString prefix=nullptr;
  QString netmask=nullptr;
  QString gateway=nullptr;
};


#endif // NETWORKATTRIBUTES_H
