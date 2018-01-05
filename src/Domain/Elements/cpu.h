#ifndef CPU_H
#define CPU_H
#include <QString>
#include <QXmlStreamWriter>
#include "CustomLibrary/vstandarditemmodel.h"
struct Model{
  QString fallback;
  QString vendor_id;
  QString value;
  bool isEmpty();
  QString xml();
};
struct Topology{
  QString sockets;
  QString cores;
  QString threads;
  QString xml();
  bool isEmpty();
  bool check(QString numberOfNumaNodes="1",QString Vcpu="1"){
    return Vcpu.toInt()>(numberOfNumaNodes.toInt()*sockets.toInt()* cores.toInt() * threads.toInt());
  }
};
class FeatureModel:public VStandardItemModel{
  Q_OBJECT
public:
  enum HostRoles {
    PolicyRole = Qt::UserRole+1,
    NameRole
  };
  FeatureModel(QObject *parent = nullptr);
  ~FeatureModel(){
  }
protected:
  QHash<int, QByteArray> roleNames() const {
    QHash<int, QByteArray> roles;
    roles[PolicyRole] = "policy";
    roles[NameRole] = "name";
    return roles;
  }
};

class TimerModel:public VStandardItemModel{
  Q_OBJECT
public:
  enum TimerModelRole {
    NameRole = Qt::UserRole+1,
    TickPolicyRole
  };
  TimerModel(QObject *parent = nullptr);
  ~TimerModel(){
  }
protected:
  QHash<int, QByteArray> roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TickPolicyRole] = "tickpolicy";
    roles[NameRole] = "name";
    return roles;
  }
};

struct Cache{
  QString level;
  QString mode;
  bool isEmpty();
  QString xml();
};


class Cpu
{
  //attributes of cpu tag
  QString match;
  QString check;
  QString mode;
  QString vendor;
  Topology topology;
  FeatureModel *feature;
  //NUMA topology
  QString numaXml;

  QString featureXml();

public:
  QString xml();

  Cpu();
};

Q_DECLARE_METATYPE(FeatureModel*)
#endif // CPU_H
