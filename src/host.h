#ifndef HOST_H
#define HOST_H
#include <QObject>
#include <QDebug>
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
    HostModel(const HostModel &parent){
        this->m_hosts=parent.m_hosts;
    }

    void addHost(const HOST &host);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QString data(const int & index, QString role) ;
    Q_INVOKABLE void create(){
        QString id=QString("1");
        QString mac="215:5952:5555:200";
        QString name="host_temp";
        QString ip="192.168.1.10";
        HOST host=*new HOST(id,mac,name,ip);
        qDebug()<<"\n\nyeah\n\n";
        addHost(host);
        qDebug()<<"\n\n"+size()+"\n\n";

    }

    Q_INVOKABLE bool set_data(int index, QVariant value, QString role)
    {
        QModelIndex temp;
        QByteArray t;
        t=role.toUtf8();
        temp=QAbstractItemModel::createIndex(index, 1);
        return setData(temp,value,roleNames().key(t));
    }

    Q_INVOKABLE QString size(){
        return QString::number(m_hosts.length());
    }


protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<HOST> m_hosts;
};
Q_DECLARE_METATYPE(HostModel)
#endif // HOST_H
