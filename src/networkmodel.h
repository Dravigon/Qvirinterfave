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
    Network(const int &id, const virNetworkPtr &dom);
    int id() const;//for indexing
    QString name() const;//for Network name
    bool setXmlData() {
        virConnectPtr temp = virNetworkGetConnect(m_net);
        virNetworkPtr netTemp=m_net;
        virNetworkUndefine(m_net);
      //  qDebug()<<"WELL THIS IS"<<netxml.write().toStdString().c_str();
        if(((m_net)=virNetworkDefineXML(temp,netxml.write().toStdString().c_str()))!=NULL){

            if(virNetworkCreate(m_net)==0){
        //        qDebug()<<"name:"<<virNetworkGetName(m_net);
                if(virNetworkIsActive(m_net)){
                    virNetworkDestroy(m_net);
                }
                return true;
            }
            else{
                virNetworkCreate(netTemp);
                return false;
            }
        }
        else
            return false;
    }

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
        NameRole =   1,
        ForwardExistRole=  2,
        ForwardModeRole =   3,
        ForwardDevRole=  4,
        NatDefinedRole=  5,
        NatStartRole=  6,
        NatEndRole=  7,
        BridgeExistRole=  8,
        BridgeNameRole=  9,
        BridgeStpRole=  10,
        BridgeDelayRole=  11,
        BandwidthExistRole=  12,
        BandWidthInboundAverageRole=  13,
        BandWidthInboundPeakRole=  14,
        BandwidthInboundBurstRole=  15,
        BandWidthOutboundAverageRole=  16,
        BandWidthOutboundPeakRole=  17,
        BandwidthOutboundBurstRole=  18,
        Ip4ExistRole=  19,
        //20 is not necessary
        Ip4FamilyRole=  20,
        //remove 20
        Ip4AddressRole=  21,
        Ip4NetmaskRole=  23,
        Ip4DhcpExistRole=  24,
        Ip6ExistRole=  25,
        Ip6FamilyRole=  26,
        Ip6AddressRole=  27,
        Ip6PrefixRole=  28,
        Ip6DhcpExistRole=  29,
        Ip4DhcpRangeExistRole=  30,
        Ip4DhcpRangeStartRole=  31,
        Ip4DhcpRangeEndRole=  32,
        Ip4DhcpHasHostRole=  33,
        Ip4DhcpHostModelRole=  34,//      Ip4DhcpHostSizeRole=  34,
        Ip6DhcpRangeExistRole=  35,
        Ip6DhcpRangeStartRole=  36,
        Ip6DhcpRangeEndRole=  37,
        Ip6DhcpHasHostRole=  38,
        Ip6DhcpHostModelRole=39


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
    Q_INVOKABLE bool setXmlData(int index){
        //Network *n=new Network(m_network.at(index));
      //  const  a = 3; // I promisse i won't change a
              Network *ptr;
              ptr = (Network*)( &m_network.at(index) );

        bool ret= ptr->setXmlData();
        qDebug()<<"das fa:"<<m_network.at(index).netxml.bridge.delay;
        return ret;
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
