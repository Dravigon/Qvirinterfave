#ifndef HOST_H
#define HOST_H
#include <QObject>
#include <QAbstractListModel>


class HOST
{

public:
    explicit HOST(QString &id,QString &mac,QString &name,QString &ip);
    QString id() const{
        return  m_id;
    }
    QString mac() const{
        return m_mac;
    }
    QString name() const{
        return m_name;
    }
    QString ip() const{
        return m_ip;
    }

private:

    QString m_id=NULL;
    QString m_mac=NULL;
    QString m_name=NULL;
    QString m_ip=NULL;

};
class HostModel:public QAbstractListModel{
    Q_OBJECT
public:
    enum HostRoles {
        IdRole = Qt::UserRole + 1,
        MacRole,
        NameRole,
        IpRole
    };

    HostModel(QObject *parent = 0);

    void addHost(const HOST &host);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QString data(const int & index, QString role) ;
    Q_INVOKABLE QString size(){
        return QString::number(m_hosts.length());
    }

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<HOST> m_hosts;
};

#endif // HOST_H
