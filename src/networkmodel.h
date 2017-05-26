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
  Network(const int &id, virNetworkPtr dom);
  int id() const;//for indexing
  QString name() const;//for Network name
//  bool forwardExist() const;
//  QString forwardMode() const;
//  QString forwardDev() const;
//  bool natDefined() const;
//  QString natStart() const;
//  QString natEnd() const;
//  bool bridgeExist() const;
//  QString bridgeName() const;
//  QString bridgeStp() const;
//  QString bridgeDelay() const;
//  bool bandwidthExist() const;
//  QString bandwidthInboundAverage() const;
//  QString bandwidthInboundPeak() const;
//  QString bandwidthInboundBurst() const;
//  QString bandwidthOutboundAverage() const;
//  QString bandwidthOutboundPeak() const;
//  QString bandwidthOutboundBurst() const;
//  int ipSize() const;
//  QString ipFamily() const;
//  QString ipAddress() const;
//  QString ipPrefix() const;
//  QString ipNetwask() const;
//  QString ipDhcpExist() const;
//  bool dhcpRangeExist() const;
//  QString dhcpRangeStart() const;
//  QString dhcpRangeEnd() const;
//  bool dhcpHasHost() const;
//  int dhcpHostSize() const;
//  QString dhcpId() const;
//  QString dhcpMac() const;
//  QString dhcpName() const;
//  QString dhcpIp() const;
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
      IpSizeRole=Qt::UserRole + 19,
      IpFamilyRole=Qt::UserRole + 20,
      IpAddressRole=Qt::UserRole + 21,
      IpPrefixRole=Qt::UserRole + 22,
      IpNetmaskRole=Qt::UserRole + 23,
      IpDhcpExistRole=Qt::UserRole + 24,
      DhcpRangeExistRole=Qt::UserRole + 25,
      DhcpRangeStartRole=Qt::UserRole + 26,
      DhcpRangeEndRole=Qt::UserRole + 27,
      DhcpHasHostRole=Qt::UserRole + 28,
      DhcpHostSizeRole=Qt::UserRole + 29,
      DhcpIdRole=Qt::UserRole + 30,
      DhcpMacRole=Qt::UserRole + 31,
      DhcpNameRole=Qt::UserRole + 32,
      DhcpIpRole=Qt::UserRole + 33,

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
