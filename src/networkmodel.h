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
  networkxml *netxml;
  virNetworkPtr m_net;
  bool editable=false;
  Network(const int &id, virNetworkPtr dom);
  ~Network();
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
      ForwardExistRole=Qt::UserRole + 1,
      ForwardModeRole = Qt::UserRole + 1,
      ForwardDevRole=Qt::UserRole + 1,
      NatDefinedRole=Qt::UserRole + 1,
      NatStartRole=Qt::UserRole + 1,
      NatEndRole=Qt::UserRole + 1,
      BridgeExisRole=Qt::UserRole + 1,
      BridgeNameRole=Qt::UserRole + 1,
      BridgeStpRole=Qt::UserRole + 1,
      BridgeDelayRole=Qt::UserRole + 1,
      BandwidthExistRole=Qt::UserRole + 1,
      BandWidthInboundAverageRole=Qt::UserRole + 1,
      BandWidthInboundPeakRole=Qt::UserRole + 1,
      BandwidthInboundBurstRole=Qt::UserRole + 1,
      BandWidthOutboundAverageRole=Qt::UserRole + 1,
      BandWidthOutboundPeakRole=Qt::UserRole + 1,
      BandwidthOutboundBurstRole=Qt::UserRole + 1,
      IpSizeRole=Qt::UserRole + 1,
      IpFamilyRole=Qt::UserRole + 1,
      IpAddressRole=Qt::UserRole + 1,
      IpPrefixRole=Qt::UserRole + 1,
      IpNetmaskRole=Qt::UserRole + 1,
      IpCurrentIndexRole=Qt::UserRole + 1,
      IpHasDhcpRole=Qt::UserRole + 1,

  };


  void addNetworks();

  int rowCount(const QModelIndex & parent = QModelIndex()) const;

  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

  Q_INVOKABLE QString task(QString task,int index);

  Q_INVOKABLE void refresh();

protected:
  QHash<int, QByteArray> roleNames() const;

private:
  QList<Network> m_network;
  int m_IpCurrentIndexRole=0;
  User *usr;

signals:

public slots:
};

#endif // NETWORKMODEL_H
