#ifndef DOMAINMODEL_H
#define DOMAINMODEL_H

#include <QDebug>

#include <QString>
#include <QAbstractListModel>
#include <libvirt/libvirt.h>
#include <QObject>

#include "user.h"

class Domain//for objects for model
{
public:
  virDomainPtr m_dom;
  Domain(const int &id, virDomainPtr dom, QString username);
  int id() const;//for indexing
  QString name() const;//for domain name
private:
  int m_id;
  QString m_name;
};


class DomainModel :public QAbstractListModel
{
  Q_OBJECT
public:

  explicit DomainModel(QObject *parent = 0);
  DomainModel(User *user);
  //DomainModel(const DomainModel &temp);

  enum DomainRoles {
    IdRole,
        NameRole = Qt::UserRole + 1,
  };


  void addDomains();

  int rowCount(const QModelIndex & parent = QModelIndex()) const;

  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

  Q_INVOKABLE QString task(QString task,int index);

  Q_INVOKABLE void refresh();

protected:
  QHash<int, QByteArray> roleNames() const;

private:
  QList<Domain> m_domain;
  User *usr;

signals:

public slots:
};

#endif // DOMAINMODEL_H
