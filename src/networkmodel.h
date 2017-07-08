#ifndef NETWORKMODEL_H
#define NETWORKMODEL_H

#include<QString>
#include <QAbstractListModel>
#include<libvirt/libvirt.h>

#include "user.h"
#include "networkxml.h"

class Network//for objects for model
{
public:
networkxml netxml;
  virNetworkPtr m_net;
  bool editable=false;
  Network(const int &id,const virNetworkPtr &dom);
  int id() const;//for indexing
  QString name() const;//for Network name


private:
  int m_id;
  QString m_name=NULL;


};


class NetworkModel :public QAbstractListModel
{
  Q_OBJECT
public:

  explicit NetworkModel(QObject *parent = 0);
  NetworkModel(User *user);
  //NetworkModel(const NetworkModel &temp);

  enum NetworkRoles {
    IdRole,
        NameRole = Qt::UserRole + 1,
      ForwardExistRole=Qt::UserRole + 2,
      ForwardModeRole = Qt::UserRole + 3,
      ForwardDevRole=Qt::UserRole + 4,
      NatDefinedRole=Qt::UserRole + 5,
      NatStartRole=Qt::UserRole + 6,
      NatEndRole=Qt::UserRole + 7,
      BridgeExistRole=Qt::UserRole + 8,
      BridgeNameRole=Qt::UserRole + 9,
      BridgeStpRole=Qt::UserRole + 10,
      BridgeDelayRole=Qt::UserRole + 11,
      BandwidthExistRole=Qt::UserRole + 12,
      BandWidthInboundAverageRole=Qt::UserRole + 13,
      BandWidthInboundPeakRole=Qt::UserRole + 14,
      BandwidthInboundBurstRole=Qt::UserRole + 15,
      BandWidthOutboundAverageRole=Qt::UserRole + 16,
      BandWidthOutboundPeakRole=Qt::UserRole + 17,
      BandwidthOutboundBurstRole=Qt::UserRole + 18,
      Ip4ExistRole=Qt::UserRole + 19,
      Ip4FamilyRole=Qt::UserRole + 20,
      Ip4AddressRole=Qt::UserRole + 21,
      Ip4NetmaskRole=Qt::UserRole + 23,
      Ip4DhcpExistRole=Qt::UserRole + 24,
      Ip6ExistRole=Qt::UserRole + 25,
      Ip6FamilyRole=Qt::UserRole + 26,
      Ip6AddressRole=Qt::UserRole + 27,
      Ip6PrefixRole=Qt::UserRole + 28,
      Ip6DhcpExistRole=Qt::UserRole + 29,
      Ip4DhcpRangeExistRole=Qt::UserRole + 30,
      Ip4DhcpRangeStartRole=Qt::UserRole + 31,
      Ip4DhcpRangeEndRole=Qt::UserRole + 32,
      Ip4DhcpHasHostRole=Qt::UserRole + 33,
      Ip4DhcpHostModelRole=Qt::UserRole + 34,//      Ip4DhcpHostSizeRole=Qt::UserRole + 34,

      Ip4DhcpIdRole=Qt::UserRole + 34,
      Ip4DhcpMacRole=Qt::UserRole + 35,
      Ip4DhcpNameRole=Qt::UserRole + 36,
      Ip4DhcpIpRole=Qt::UserRole + 37,
      Ip6DhcpRangeExistRole=Qt::UserRole + 38,
      Ip6DhcpRangeStartRole=Qt::UserRole + 39,
      Ip6DhcpRangeEndRole=Qt::UserRole + 40,
      Ip6DhcpHasHostRole=Qt::UserRole + 41,
      Ip6DhcpHostSizeRole=Qt::UserRole + 42,
      Ip6DhcpIdRole=Qt::UserRole + 43,
      Ip6DhcpMacRole=Qt::UserRole + 44,
      Ip6DhcpNameRole=Qt::UserRole + 45,
      Ip6DhcpIpRole=Qt::UserRole + 46,

  };


  void addNetworks();

  int rowCount(const QModelIndex & parent = QModelIndex()) const;

  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

  bool setData(const QModelIndex & index, const QVariant & value, int role) ;

  Q_INVOKABLE QString task(QString task,int index);

  Q_INVOKABLE bool set_data(int index,QVariant value,QString role);

  Q_INVOKABLE void refresh();
  Q_PROPERTY(int ipIndex READ ipIndex WRITE setIpIndex )
  Q_PROPERTY(int dhcpIndex READ dhcpIndex WRITE setDhcpIndex )
  int dhcpIndex() const{
      return m_DhcpIndex;
  }
  void setDhcpIndex(int temp){
      m_DhcpIndex=temp;
  }
  int ipIndex() const{
      return m_IpIndex;
  }
  void setIpIndex(int temp){
      m_IpIndex=temp;
  }


protected:
  QHash<int, QByteArray> roleNames() const;

private:
  QList<Network> m_network;
  int m_IpIndex=0;
  int m_DhcpIndex=0;
  User *usr;

signals:

public slots:
};

#endif // NETWORKMODEL_H
