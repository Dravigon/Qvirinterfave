#include "networkmodel.h"
#include <QtCore/QBuffer>
#include <QFile>


Network::Network(const int &id, const virNetworkPtr &dom)
  : m_net(dom),m_id(id)
{
  char *xml;
  m_name=QString(virNetworkGetName(m_net));
  if((xml=virNetworkGetXMLDesc(dom,VIR_NETWORK_XML_INACTIVE))!=nullptr){
      QByteArray xml_buffer;

      //    qDebug()<<xml;
      //for testing purposes
      // QString x;
      //x="<network>\n  <name>local6</name>\n  <bridge name='virbr1'/>\n  <forward mode='route' dev='eth1'/>\n  <ip address='192.168.122.1' netmask='255.255.255.0'>\n    <dhcp>\n      <range start='192.168.122.2' end='192.168.122.254'/>\n    </dhcp>\n  </ip>\n  <ip family='ipv6' address='2001:db8:ca2:2::1' prefix='64'>\n    <dhcp>\n      <host name='paul' ip='2001:db8:ca2:2:3::1'/>\n      <host id='0:1:0:1:18:aa:62:fe:0:16:3e:44:55:66' ip='2001:db8:ca2:2:3::2'/>\n      <host id='0:3:0:1:0:16:3e:11:22:33' name='ralph' ip='2001:db8:ca2:2:3::3'/>\n      <host id='0:4:7e:7d:f0:7d:a8:bc:c5:d2:13:32:11:ed:16:ea:84:63' name='badbob' ip='2001:db8:ca2:2:3::4'/>\n    </dhcp>\n  </ip>\n</network>\n";
      //   xml_buffer.append(x);
      xml_buffer.append(xml);
      delete [] xml;
      QBuffer buffer(&xml_buffer);
      buffer.open(QIODevice::ReadWrite);

      netxml.setXml(&buffer);
      if(netxml.read())
        editable=true;
    }
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

void NetworkModel::addNetworks(){
  if(!lock){
      virNetworkPtr *networks=nullptr;
      virConnectPtr conn=usr->getConn();
      QString username=usr->username();
      int ret;
      unsigned int flags = VIR_CONNECT_LIST_NETWORKS_ACTIVE|
          VIR_CONNECT_LIST_NETWORKS_INACTIVE;
      if(conn!=nullptr){
          ret = virConnectListAllNetworks(conn, &networks, flags);
          if (ret < 0)
            qDebug()<<"error";
          qDebug()<<"value of ret="<<ret;
          int i=0;
          while(networks[i]){
              if((i+1)>rowCount()){
                  qDebug()<<&"Triggered network "<<i<<" refresh";
                  beginInsertRows(QModelIndex(), rowCount(), rowCount());
                  m_network.append(*new Network(i,networks[i]));
                  endInsertRows();
                }
              i++;
            }
          if(!m_network.isEmpty()&&(i!=m_network.size())&&(m_network.size()!=0)){
              removeNetworks();
              if(i!=0)
                addNetworks();
            }
        }
      if(networks!=nullptr)
        delete [] networks;
    }
}

void NetworkModel::removeNetworks(){
  if(!lock){
      virNetworkPtr *networks=nullptr;
      virConnectPtr conn=usr->getConn();
      QString username=usr->username();
      int ret;
      unsigned int flags = VIR_CONNECT_LIST_NETWORKS_ACTIVE|
          VIR_CONNECT_LIST_NETWORKS_INACTIVE;
      if(conn!=nullptr){
          ret = virConnectListAllNetworks(conn, &networks, flags);
          if (ret < 0)
            qDebug()<<"error";
          int i=0;
          while(networks[i]){
              int flag=0;
              for(int j=0;j<m_network.size();j++){
                  if(networks[i]!=m_network.at(j).m_net){
                      flag++;
                    }
                  else{
                      flag=0;
                      break;
                    }
                }
              if(flag>0){
                  beginRemoveRows(QModelIndex(), i, i);
                  m_network.removeAt(i);
                  endRemoveRows();
                  i=i-1;
                }
              i++;
            }
          if((i!=m_network.size())&&(m_network.size()!=0)){
              beginRemoveRows(QModelIndex(), i, i);
              m_network.removeAt(i);
              endRemoveRows();
            }
        }
      if(networks!=nullptr)
        delete [] networks;
    }
}

void NetworkModel::refresh(){
  addNetworks();
}

void NetworkModel::addNewNetwork(QString name)
{
  networkxml netXml;
  QFile *stream=new QFile(":/DefaultXml/NetworkXml.xml");
  netXml.setXml(stream);
  netXml.name=name;

  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  virNetworkPtr virNet;
  virNet=virNetworkDefineXML(usr->getConn(),netXml.write().toStdString().c_str());
  Network newNet(rowCount(),virNet);
  m_network.append(newNet);
  endInsertRows();

  delete stream;

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
    return network.netxml.isforwardExist;
  else if (role == ForwardModeRole)
    return network.netxml.forward.getMode();
  else if (role == ForwardDevRole){
      // qDebug()<<"this is the returned dev value"<<network.netxml.forward.getDev();
      return network.netxml.forward.getDev();
    }
  else if ( role == NatDefinedRole)
    return network.netxml.forward.isNat();
  else if (role == NatStartRole){
      //qDebug()<<"this is the returned value"<<network.netxml.forward.getNat().getStart();
      return network.netxml.forward.getNat()->getStart();
    }
  else if (role ==NatEndRole)
    return network.netxml.forward.getNat()->getEnd();
  else if (role == BridgeExistRole) {
      return network.netxml.bridge.exist;
    }
  else if (role == BridgeNameRole)
    return network.netxml.bridge.getName();
  else if (role== BridgeStpRole)
    return network.netxml.bridge.getStp();
  else if (role == BridgeDelayRole)
    return  network.netxml.bridge.getDelay();
  else if ( role == BandwidthExistRole) {
      return  network.netxml.bandwidth.exist;
    }
  else if (role == BandWidthInboundAverageRole)
    return network.netxml.bandwidth.getInbound()->getAverage();
  else if (role == BandWidthInboundPeakRole)
    return network.netxml.bandwidth.getInbound()->getPeak();
  else if (role == BandwidthInboundBurstRole)
    return network.netxml.bandwidth.getInbound()->getBurst();
  else if (role == BandWidthOutboundAverageRole)
    return network.netxml.bandwidth.getOutbound()->getAverage();
  else if (role == BandWidthOutboundPeakRole)
    return network.netxml.bandwidth.getOutbound()->getPeak();
  else if (role == BandwidthOutboundBurstRole)
    return network.netxml.bandwidth.getOutbound()->getBurst();
  else if( role == Ip4ExistRole)
    return network.netxml.ip4.getExist();
  else if(role == Ip4FamilyRole)
    return network.netxml.ip4.getFamily();
  else if(role == Ip4AddressRole)
    return network.netxml.ip4.getAddress();
  else if(role == Ip4NetmaskRole)
    return network.netxml.ip4.getNetmask();
  else if(role == Ip4DhcpExistRole)
    return network.netxml.ip4.getHasDhcp();
  else if( role == Ip6ExistRole)
    return network.netxml.ip6.getExist();
  else if(role == Ip6FamilyRole)
    return network.netxml.ip6.getFamily();
  else if(role == Ip6AddressRole)
    return network.netxml.ip6.getAddress();
  else if(role == Ip6PrefixRole)
    return network.netxml.ip6.getPrefix();
  else if(role == Ip6DhcpExistRole)
    return network.netxml.ip6.getHasDhcp();
  else if(role == Ip4DhcpRangeExistRole)
    return network.netxml.ip4.getDhcp().rangeExist();
  else if(role == Ip4DhcpRangeStartRole)
    return  network.netxml.ip4.getDhcp().getRange()->start;
  else if(role == Ip4DhcpRangeEndRole)
    return  network.netxml.ip4.getDhcp().getRange()->end;
  else if(role == Ip4DhcpHasHostRole)
    return network.netxml.ip4.getDhcp().hasHost;
  else if(role == Ip4DhcpHostModelRole)
    return QVariant::fromValue(network.netxml.ip4.getDhcp().getHost());//testing

  else if(role == Ip6DhcpRangeExistRole){
      return network.netxml.ip6.getDhcp().rangeExist();
    }
  else if(role == Ip6DhcpRangeStartRole) {
      return  network.netxml.ip6.getDhcp().getRange()->start;
    }
  else if(role == Ip6DhcpRangeEndRole) {
      return  network.netxml.ip6.getDhcp().getRange()->end;
    }
  else if(role == Ip6DhcpHasHostRole) {
      return network.netxml.ip6.getDhcp().hasHost;
    }
  else if(role == Ip6DhcpHostModelRole) {
      return QVariant::fromValue(network.netxml.ip6.getDhcp().getHost());
    }//testing
  //    else if(role == Ip4DhcpIdRole)
  //        return network.netxml.ip.at(m_IpIndex).dhcp.host.at(m_DhcpIndex).id;
  //    else if(role == Ip4DhcpNameRole)
  //        return network.netxml.ip.at(m_IpIndex).dhcp.host.at(m_DhcpIndex).name;
  //    else if(role == Ip4DhcpMacRole)
  //        return network.netxml.ip.at(m_IpIndex).dhcp.host.at(m_DhcpIndex).mac;
  //    else if(role == Ip4DhcpIpRole)
  //        return network.netxml.ip.at(m_IpIndex).dhcp.host.at(m_DhcpIndex).ip;
  return QVariant();
}

bool NetworkModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
  qDebug()<<"see:"<<value;
  //       qDebug()<<"\ncalled set data before and index recived "<<index.row()<<"\ncount is "<<m_network.count()<<"value recieved"<<value.toString()<<" role is "<<role;
  if (index.row() < 0 || index.row() > m_network.count())
    return false;
  //    qDebug()<<"\ncalled set data \n";
  //    qDebug()<<"role no of model is:"<<ForwardModeRole;
  Network network = m_network[index.row()];
  if (role == IdRole)
    return network.id();
  else if (role == NameRole)
    network.netxml.name=value.toString();
  else if (role == ForwardExistRole)
    network.netxml.isforwardExist=value.toBool();
  else if (role == ForwardModeRole){
      //        qDebug()<<"\ncalled set mode \n";
      network.netxml.forward.setMode(value.toString());
    }
  else if (role == ForwardDevRole)
    network.netxml.forward.setDev(value.toString());
  //    else if ( role == NatDefinedRole)
  //        network.netxml.forward.getNat().set(value.toBool());
  else if (role == NatStartRole){
      network.netxml.forward.getNat()->setStart(value.toString());
      qDebug()<<"this is start"<<network.netxml.forward.getNat()->getStart();
    }
  else if (role ==NatEndRole)
    network.netxml.forward.getNat()->setEnd(value.toString());
  else if (role == BridgeExistRole)
    network.netxml.bridge.exist=value.toBool();
  else if (role == BridgeNameRole)
    network.netxml.bridge.setName(value.toString());
  else if (role== BridgeStpRole)
    network.netxml.bridge.setStp(value.toString());
  else if (role == BridgeDelayRole)
    network.netxml.bridge.setDelay(value.toString());
  else if ( role == BandwidthExistRole)
    network.netxml.bandwidth.exist=value.toBool();

  else if (role == BandWidthInboundAverageRole)
    network.netxml.bandwidth.getInbound()->setAverage(value.toString());
  else if (role == BandWidthInboundPeakRole)
    network.netxml.bandwidth.getInbound()->setPeak(value.toString());
  else if (role == BandwidthInboundBurstRole)
    network.netxml.bandwidth.getInbound()->setBurst(value.toString());
  else if (role == BandWidthOutboundAverageRole)
    network.netxml.bandwidth.getOutbound()->setAverage(value.toString());
  else if (role == BandWidthOutboundPeakRole)
    network.netxml.bandwidth.getOutbound()->setPeak(value.toString());
  else if (role == BandwidthOutboundBurstRole)
    network.netxml.bandwidth.getOutbound()->setBurst(value.toString());
  else if(role == Ip4ExistRole)
    network.netxml.ip4.setExist(value.toBool());
  else if(role == Ip4AddressRole)
    network.netxml.ip4.setAddress(value.toString());
  else if(role == Ip4NetmaskRole)
    network.netxml.ip4.setNetmask(value.toString());
  else if(role == Ip4DhcpExistRole)
    network.netxml.ip4.setHasDhcp(value.toBool());
  else if(role == Ip4DhcpRangeExistRole)
    network.netxml.ip4.getDhcp().rangeExist(value.toBool());
  else if(role == Ip4DhcpRangeStartRole)
    network.netxml.ip4.getDhcp().getRange()->start=value.toString();
  else if(role == Ip4DhcpRangeEndRole)
    network.netxml.ip4.getDhcp().getRange()->end=value.toString();
  else if(role == Ip4DhcpHasHostRole)
    network.netxml.ip4.getDhcp().setHasHost(value.toBool());
  else if(role == Ip4DhcpHostModelRole)
    //http://www.bogotobogo.com/Qt/Qt5_QVariant_meta_object_system_MetaType.php
    //refer that for more info
    network.netxml.ip4.getDhcp().setHost(value.value<HostModel*>());

  else if( role == Ip6ExistRole)
    network.netxml.ip6.setExist(value.toBool());
  else if(role == Ip6FamilyRole)
    network.netxml.ip6.setFamily(value.toString());
  else if(role == Ip6AddressRole)
    network.netxml.ip6.setAddress(value.toString());
  else if(role == Ip6PrefixRole)
    network.netxml.ip6.setPrefix(value.toString());
  else if(role == Ip6DhcpExistRole)
    network.netxml.ip6.setHasDhcp(value.toBool());
  else if(role == Ip6DhcpRangeExistRole)
    network.netxml.ip6.getDhcp().rangeExist(value.toBool());
  else if(role == Ip6DhcpRangeStartRole)
    network.netxml.ip6.getDhcp().getRange()->start=value.toString();
  else if(role == Ip6DhcpRangeEndRole)
    network.netxml.ip6.getDhcp().getRange()->end=value.toString();
  else if(role == Ip6DhcpHasHostRole)
    network.netxml.ip6.getDhcp().setHasHost(value.toBool());
  else if(role == Ip6DhcpHostModelRole)
    //http://www.bogotobogo.com/Qt/Qt5_QVariant_meta_object_system_MetaType.php
    //refer that for more info
    network.netxml.ip6.getDhcp().setHost(value.value<HostModel*>());


  //this statement sets the data
  m_network[index.row()]=network;
  // qDebug()<<"well name is"<<m_network[index.row()].netxml.forward.mode<<" name in temp is "<<network.netxml.forward.mode;
  emit dataChanged(index, index);
  return true;
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
      //        qDebug()<<"OMG!!!!! "<<virNetworkGetName(m_network.at(index).m_net);
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

bool NetworkModel::set_data(int index, QVariant value, QString role)
{
  QModelIndex temp;
  QByteArray t;
  t=role.toUtf8();
  temp=QAbstractItemModel::createIndex(index, 1);
  return setData(temp,value,roleNames().key(t));
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
  roles[Ip4ExistRole]="ip4Exist";
  roles[Ip4FamilyRole]="ip4Family";
  roles[Ip4AddressRole]="ip4Address";
  roles[Ip4NetmaskRole]="ip4Netmask";
  roles[Ip4DhcpExistRole]="ip4DhcpExist";
  roles[Ip6ExistRole]="ip6Exist";
  roles[Ip6FamilyRole]="ip6Family";
  roles[Ip6AddressRole]="ip6Address";
  roles[Ip6PrefixRole]="ip6Prefix";
  roles[Ip6DhcpExistRole]="ip6DhcpExist";
  roles[Ip4DhcpRangeExistRole]="ip4DhcpRangeExist";
  roles[Ip4DhcpRangeStartRole]="ip4DhcpRangeStart";
  roles[Ip4DhcpRangeEndRole]="ip4DhcpRangeEnd";
  roles[Ip4DhcpHasHostRole]="ip4DhcpHasHost";
  roles[Ip4DhcpHostModelRole]="ip4DhcpHostModel";


  roles[Ip6DhcpRangeExistRole]="ip6DhcpRangeExist";
  roles[Ip6DhcpRangeStartRole]="ip6DhcpRangeStart";
  roles[Ip6DhcpRangeEndRole]="ip6DhcpRangeEnd";
  roles[Ip6DhcpHasHostRole]="ip6DhcpHasHost";
  roles[Ip6DhcpHostModelRole]="ip6DhcpHostModel";


  return roles;
}

