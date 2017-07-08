#include "host.h"

HOST::HOST(QString &id, QString &mac, QString &name, QString &ip)
    :m_id(id),m_mac(mac),m_name(name),m_ip(ip)
{

}



HostModel::HostModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void HostModel::addHost(const HOST &host)
{
    HostModel::beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_hosts << host;
    HostModel::endInsertRows();
}

int HostModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_hosts.count();
}

QVariant HostModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_hosts.count())
        return QVariant();

    const HOST &host = m_hosts[index.row()];
    if (role == IdRole)
        return host.id();
    else if (role == NameRole)
        return host.name();
    else if (role==MacRole)
        return host.mac();
    else if (role==IpRole)
        return host.ip();
    return QVariant();
}

QString HostModel::data(const int & index, QString role) {
    if (index < 0 || index >= m_hosts.count())
        return NULL;

    const HOST &host = m_hosts[index];
    if (role == "id")
        return host.id();
    else if (role == "name")
        return host.name();
    else if (role=="mac")
        return host.mac();
    else if (role=="ip")
        return host.ip();
    return NULL;
}

//![0]
QHash<int, QByteArray> HostModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[MacRole]="mac";
    roles[IpRole]="ip";
    return roles;
}
//![0]


