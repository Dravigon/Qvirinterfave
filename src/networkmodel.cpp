#include "networkmodel.h"
#include <QBuffer>


Network::Network(const int &id,virNetworkPtr dom)
    : m_net(dom),m_id(id)
{
    char *xml;
    m_name=QString(virNetworkGetName(m_net));
    if((xml=virNetworkGetXMLDesc(dom,VIR_NETWORK_XML_INACTIVE))!=NULL){
    QByteArray xml_buffer;
    xml_buffer.append(xml);
    delete [] xml;
    QBuffer buffer(&xml_buffer);
    buffer.open(QIODevice::ReadWrite);

    netxml=new networkxml(&buffer);
    if(netxml->read())
        editable=true;
    }
}

Network::~Network()
{
    if(editable)
        delete netxml;
}

int Network::id() const
{
    return m_id;
}

QString Network::name() const
{
    return m_name;
}

NetworkModel::NetworkModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

NetworkModel::NetworkModel(User *user)
{
    usr=user;
}

void NetworkModel::addNetworks()
{
    virNetworkPtr *networks=NULL;


    virConnectPtr conn=usr->getConn();
    QString username=usr->username();

    int ret;
    unsigned int flags = VIR_CONNECT_LIST_NETWORKS_ACTIVE|
            VIR_CONNECT_LIST_NETWORKS_INACTIVE;
    if(conn!=NULL){
        ret = virConnectListAllNetworks(conn, &networks, flags);
        if (ret < 0)
            qDebug()<<"error";
        int i=0;
        while(networks[i]){
            qDebug()<<i<<virNetworkGetName(networks[i])<<"0.2"<<"\n row count="<<rowCount();
            if((i+1)>rowCount()){
                qDebug()<<i<<">"<<rowCount();
                beginInsertRows(QModelIndex(), rowCount(), rowCount());
                m_network.append(*new Network(i,networks[i]));
                endInsertRows();
            }
            i++;
        }
    }
    if(networks!=NULL)
        delete [] networks;
}

void NetworkModel::refresh(){
    qDebug()<<"refreshed";
    addNetworks();
}

int NetworkModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_network.count();
}

QVariant NetworkModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_network.count())
        return QVariant();

    const Network &network = m_network[index.row()];
    if (role == IdRole)
        return network.id();
    else if (role == NameRole)
        return network.name();
    else if (role == ForwardExistRole)
        return network.netxml->isforwardExist;
    else if (role == ForwardModeRole)
        return network.netxml->forward.mode;
    else if (role == ForwardDevRole) {
        return network.netxml->forward.dev;
    }
    else if ( role == NatDefinedRole) {
        return network.netxml->forward.natExist;
    }
    else if (role == NatStartRole)
        return network.netxml->forward.nat.start;
    else if (role ==NatEndRole) {
        return network.netxml->forward.nat.end;
    }
    else if (role == BridgeExistRole) {
        return network.netxml->bridge.exist;
    }
    else if (role == BridgeNameRole)
        return network.netxml->bridge.name;
    else if (role== BridgeStpRole)
        return network.netxml->bridge.stp;
    else if (role == BridgeDelayRole)
        return  network.netxml->bridge.delay;
    else if ( role == BandwidthExistRole) {
        return  network.netxml->bandwidth.exist;
    }
    /*TODO
     *Add furthure roles
     */
    return QVariant();
}

QString NetworkModel::task(QString task, int index)
{
    QString ret="nil";
    if(task=="start"){
        if(!(virNetworkIsActive(m_network.at(index).m_net))){
            virNetworkCreate(m_network.at(index).m_net);
            ret="started";
        }
    }
    else if(task=="stop"){
        if((virNetworkIsActive(m_network.at(index).m_net))){
            virNetworkDestroy(m_network.at(index).m_net);
            ret="stopped";
        }
    }
    else if(task=="state"){
        if((virNetworkIsActive(m_network.at(index).m_net))){
            ret="started";
        }
        else
           ret="stopped";
    }

    ////return doTask(task,index,m_network.at(index));
    return ret;
}

QHash<int, QByteArray> NetworkModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[ForwardExistRole]="forwardExist";
    roles[ForwardModeRole]="forwardMode";
    roles[ForwardDevRole]="forwardDev";
    roles[NatDefinedRole]="natDefined";
    roles[NatStartRole]="natStart";
    roles[NatEndRole]="natEnd";
    roles[BridgeExistRole]="bridgeExist";
    roles[BridgeNameRole]="bridgeName";
    roles[BridgeStpRole]="bridgeStp";
    roles[BridgeDelayRole]="bridgeDelay";
    roles[BandwidthExistRole]="bandwidthExist";
    roles[BandWidthInboundAverageRole]="bandwidthInboundAverage";
    roles[BandWidthInboundPeakRole]="bandwidthInboundPeak";
    roles[BandwidthInboundBurstRole]="bandwidthInboundBurst";
    roles[BandWidthOutboundAverageRole]="bandwidthOutboundAverage";
    roles[BandWidthOutboundPeakRole]="bandwidthOutboundPeak";
    roles[BandwidthOutboundBurstRole]="bandwidthOutboundBurst";
    roles[IpSizeRole]="ipSize";
    roles[IpFamilyRole]="ipFamily";
    roles[IpAddressRole]="ipAddress";
    roles[IpPrefixRole]="ipPrefix";
    roles[IpNetmaskRole]="ipNetwask";
    roles[IpIndexRole]="ipIndex";
    roles[IpHasDhcpRole]="ipDhcpExist";
    roles[DhcpRangeExistRole]="dhcpRangeExist";
    roles[DhcpRangeStartRole]="dhcpRangeStart";
    roles[DhcpRangeEndRole]="dhcpRangeEnd";
    roles[DhcpHasHostRole]="dhcpHasHost";
    roles[DhcpHostSizeRole]="dhcpHostSize";
    roles[DhcpHostIndex]="dhcpHostIndex";
    roles[DhcpIdRole]="dhcpId";
    roles[DhcpMacRole]="dhcpMac";
    roles[DhcpNameRole]="dhcpName";
    roles[DhcpIpRole]="dhcpIp";

    return roles;
}

