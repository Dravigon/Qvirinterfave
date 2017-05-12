#ifndef NETWORKMODEL_H
#define NETWORKMODEL_H

#include<QString>
#include <QAbstractListModel>
#include<libvirt/libvirt.h>

#include "user.h"

class Network//for objects for model
{
public:
  virNetworkPtr m_net;
  Network(const int &id, virNetworkPtr dom);
  int id() const;//for indexing
  QString name() const;//for Network name
private:
  int m_id;
  QString m_name;
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
  User *usr;

signals:

public slots:
};

#endif // NETWORKMODEL_H
