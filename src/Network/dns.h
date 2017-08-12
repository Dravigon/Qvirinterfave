#ifndef DNS_H
#define DNS_H

#include <QString>

#include "../CustomLibrary/vstandarditemmodel.h"


class Txt: public VStandardItemModel{
    Q_OBJECT
public:
    Txt(QObject *parent = nullptr);
    ~Txt(){
    }

    enum TxtRoles {
        NameRole = Qt::UserRole+1,
        ValueRole
    };
protected:
    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[ValueRole]="value";
        return roles;
    }
};
class Forwarder: public VStandardItemModel{
    Q_OBJECT
public:
    Forwarder(QObject *parent=nullptr);
    enum ForwarderRole{
        DomainRole=Qt::UserRole+1,
        AddressRole
    };
protected:
    QHash<int,QByteArray> roleNames() const{
        QHash<int,QByteArray> roles;
        roles[AddressRole]="address";
        roles[DomainRole]="domain";
        return roles;
    }
};

class Srv: public VStandardItemModel{

public:
    Srv(QObject *parent=nullptr);
    enum ForwarderRole{
        DomainRole=Qt::UserRole+1,
        NameRole,
        ProtocolRole,
        TargetRole,
        PortRole,
        PriorityRole,
        WeightRole
    };
protected:
    QHash<int,QByteArray> roleNames() const{
        QHash<int,QByteArray> roles;
        roles[NameRole]="name";
        roles[DomainRole]="domain";
        roles[ProtocolRole]="protocol";
        roles[TargetRole]="target";
        roles[PortRole]="port";
        roles[PriorityRole]="priority";
        roles[WeightRole]="weight";
        return roles;
    }
};
//class Host:public QObject{
//    QString ip;
//    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged)
//    QList<QString> hostname;
//    Q_PROPERTY(QList<QString*> hostname READ hostname WRITE setHostname NOTIFY hostnameChanged)
//};

class Dns:public QObject
{
Q_OBJECT


public:
    Txt *txt() ;
    void setTxt(Txt & );
    Forwarder *forwarder() ;
    void setForwarder(Forwarder &forwarder);
    Srv *srv() ;
    void setSrv(Srv &srv);

   // Txt *txt=new Txt ;


    Dns();
protected:
    Forwarder *m_forwarder;
    Srv *m_srv;
    Txt *m_txt;


};

#endif // DNS_H
