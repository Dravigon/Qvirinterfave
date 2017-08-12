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
    void setId(QString id){
        m_id=id;
    }
    void setMac(QString mac){
        m_mac=mac;
    }
    void setName(QString name){
        m_name=name;
    }
    void setIp(QString ip){
        m_ip=ip;
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
        IdRole = 1,
        MacRole=2,
        NameRole=3,
        IpRole=4
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
        QString mac="55:AE:36:1D:29:30";
        QString name="host_temp";
        QString ip="192.168.1.10";
        HOST host=*new HOST(id,mac,name,ip);
        qDebug()<<"\n\nyeah\n\n";
        addHost(host);
        qDebug()<<"\n\n"+size()+"\n\n";
    }

    Q_INVOKABLE bool remove(){

        if(m_hosts.isEmpty()){
            return false;
        }
        beginRemoveRows(QModelIndex(),rowCount(),rowCount());
        m_hosts.pop_back();
        endRemoveRows();
        return true;

    }

    bool setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if (index.row() < 0 || index.row() > m_hosts.count())
            return false;

         HOST host = m_hosts[index.row()];
        if (role == IdRole)
            host.setId(value.toString());
        else if(role == NameRole)
            host.setName(value.toString());
        else if (role == MacRole) {
            host.setMac(value.toString());
        }
        else if(role == IpRole)
            host.setIp(value.toString());

        m_hosts[index.row()]=host;
        emit dataChanged(index, index);
        return true;
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
