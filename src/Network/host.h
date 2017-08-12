#ifndef HOST_H
#define HOST_H
#include "../CustomLibrary/vstandarditemmodel.h"



class HostModel : public VStandardItemModel
{
Q_OBJECT
public:
    enum HostRoles {
        IdRole = Qt::UserRole+1,
        MacRole,
        NameRole,
        IpRole
    };
    HostModel(QObject *parent = nullptr);
    ~HostModel(){
    }

    Q_INVOKABLE void create(){
        QStandardItem* item=new QStandardItem();
        item->setData("1",IdRole);
        item->setData("55:AE:36:1D:29:30",MacRole);
        item->setData("host_temp",NameRole);
        item->setData("192.168.1.10",IpRole);
        add(item);
        qDebug()<<"\n\n""\n\n";
    }
    Q_INVOKABLE int size(){
        return rowCount();
    }

protected:
    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[IdRole] = "id";
        roles[NameRole] = "name";
        roles[MacRole]="mac";
        roles[IpRole]="ip";
        return roles;
    }
};

Q_DECLARE_METATYPE(HostModel*)
#endif // HOST_H
