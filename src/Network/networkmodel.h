#ifndef NETWORKMODEL_H
#define NETWORKMODEL_H

#include<QString>
#include <QAbstractListModel>
#include "../user.h"
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
  void removeNetworks();

  int rowCount(const QModelIndex & parent = QModelIndex()) const;

  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

  bool setData(const QModelIndex & index, const QVariant & value, int role) ;

  Q_INVOKABLE QString task(QString task,int index);

  Q_INVOKABLE bool set_data(int index,QVariant value,QString role);

  Q_INVOKABLE void refresh();

  Q_INVOKABLE void addNewNetwork(QString name);
  Q_INVOKABLE void lockResource(){
    lock=true;
  }
  Q_INVOKABLE void unlockResource(){
    lock=true;
  }

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
    //qDebug()<<"das fa:"<<m_network.at(index).netxml.bridge.delay;
    return ret;
  }
  Q_INVOKABLE void removeIndex(int i){

        beginRemoveRows(QModelIndex(), i, i);
        if((virNetworkIsActive(m_network.at(i).m_net))){
            virNetworkDestroy(m_network.at(i).m_net);
          }
        virNetworkUndefine(m_network.at(i).m_net);
        m_network.removeAt(i);
        endRemoveRows();

  }


protected:
  QHash<int, QByteArray> roleNames() const;

private:
  QList<Network> m_network;
  int m_IpIndex=0;
  int m_DhcpIndex=0;
  bool lock=false;
  User *usr;


signals:

public slots:
};

#endif // NETWORKMODEL_H
/*TODO
 * Addressing
*The final set of elements define the addresses (IPv4 and/or IPv6, as well as MAC) to be assigned to the bridge device associated with the virtual network, and optionally enable DHCP services. These elements are only valid for isolated networks (no forward element specified), and for those with a forward mode of 'route' or 'nat'.

...
<mac address='00:16:3E:5D:C7:9E'/>
<domain name="example.com"/>
<dns>
  <txt name="example" value="example value"/>
  <forwarder addr="8.8.8.8"/>
  <forwarder domain='example.com' addr="8.8.4.4"/>
  <forwarder domain='www.example.com'/>
  <srv service='name' protocol='tcp' domain='test-domain-name' target='.'
    port='1024' priority='10' weight='10'/>
  <host ip='192.168.122.2'>
    <hostname>myhost</hostname>
    <hostname>myhostalias</hostname>
  </host>
</dns>
<ip address="192.168.122.1" netmask="255.255.255.0" localPtr="yes">
  <dhcp>
    <range start="192.168.122.100" end="192.168.122.254"/>
    <host mac="00:16:3e:77:e2:ed" name="foo.example.com" ip="192.168.122.10"/>
    <host mac="00:16:3e:3e:a9:1a" name="bar.example.com" ip="192.168.122.11"/>
  </dhcp>
</ip>
<ip family="ipv6" address="2001:db8:ca2:2::1" prefix="64" localPtr="yes"/>
<route family="ipv6" address="2001:db9:ca1:1::" prefix="64" gateway="2001:db8:ca2:2::2"/>
mac
The address attribute defines a MAC (hardware) address formatted as 6 groups of 2-digit hexadecimal numbers, the groups separated by colons (eg, "52:54:00:1C:DA:2F"). This MAC address is assigned to the bridge device when it is created. Generally it is best to not specify a MAC address when creating a network - in this case, if a defined MAC address is needed for proper operation, libvirt will automatically generate a random MAC address and save it in the config. Allowing libvirt to generate the MAC address will assure that it is compatible with the idiosyncrasies of the platform where libvirt is running. Since 0.8.8
dns
The dns element of a network contains configuration information for the virtual network's DNS server Since 0.9.3.
The dns element can have an optional enable attribute Since 2.2.0. If enable is "no", then no DNS server will be setup by libvirt for this network (and any other configuration in <dns> will be ignored). If enable is "yes" or unspecified (including the complete absence of any <dns> element) then a DNS server will be setup by libvirt to listen on all IP addresses specified in the network's configuration.

The dns element can have an optional forwardPlainNames attribute Since 1.1.2. If forwardPlainNames is "no", then DNS resolution requests for names that are not qualified with a domain (i.e. names with no "." character) will not be forwarded to the host's upstream DNS server - they will only be resolved if they are known locally within the virtual network's own DNS server. If forwardPlainNames is "yes", unqualified names will be forwarded to the upstream DNS server if they can't be resolved by the virtual network's own DNS server.

Currently supported sub-elements of <dns> are:
forwarder
The dns element can have 0 or more <forwarder> elements. Each forwarder element defines an alternate DNS server to use for some, or all, DNS requests sent to this network's DNS server. There are two attributes - domain, and addr; at least one of these must be specified in any <forwarder> element. If both domain and addr are specified, then all requests that match the given domain will be forwarded to the DNS server at addr. If only domain is specified, then all matching domains will be resolved locally (or via the host's standard DNS forwarding if they can't be resolved locally). If an addr is specified by itself, then all DNS requests to the network's DNS server will be forwarded to the DNS server at that address with no exceptions. addr Since 1.1.3, domain Since 2.2.0.
txt
A dns element can have 0 or more txt elements. Each txt element defines a DNS TXT record and has two attributes, both required: a name that can be queried via dns, and a value that will be returned when that name is queried. names cannot contain embedded spaces or commas. value is a single string that can contain multiple values separated by commas. Since 0.9.3
host
The host element within dns is the definition of DNS hosts to be passed to the DNS service. The IP address is identified by the ip attribute and the names for that IP address are identified in the hostname sub-elements of the host element. Since 0.9.3
srv
The dns element can have also 0 or more srv record elements. Each srv record element defines a DNS SRV record and has 2 mandatory and 5 optional attributes. The mandatory attributes are service name and protocol (tcp, udp) and the optional attributes are target, port, priority, weight and domain as defined in DNS server SRV RFC (RFC 2782). Since 0.9.9
ip
The address attribute defines an IPv4 address in dotted-decimal format, or an IPv6 address in standard colon-separated hexadecimal format, that will be configured on the bridge device associated with the virtual network. To the guests this IPv4 address will be their IPv4 default route. For IPv6, the default route is established via Router Advertisement. For IPv4 addresses, the netmask attribute defines the significant bits of the network address, again specified in dotted-decimal format. For IPv6 addresses, and as an alternate method for IPv4 addresses, the significant bits of the network address can be specified with the prefix attribute, which is an integer (for example, netmask='255.255.255.0' could also be given as prefix='24'). The family attribute is used to specify the type of address - ipv4 or ipv6; if no family is given, ipv4 is assumed. More than one address of each family can be defined for a network. The optional localPtr attribute (since 3.0.0) configures the DNS server to not forward any reverse DNS requests for IP addresses from the network configured by the address and netmask/prefix attributes. For some unusual network prefixes (not divisible by 8 for IPv4 or not divisible by 4 for IPv6) libvirt may be unable to compute the PTR domain automatically. The ip element is supported since 0.3.0. IPv6, multiple addresses on a single network, family, and prefix are supported since 0.8.7. The ip element may contain the following elements:
tftp
The optional tftp element and its mandatory root attribute enable TFTP services. The attribute specifies the path to the root directory served via TFTP. The tftp element is not supported for IPv6 addresses, and can only be specified on a single IPv4 address per network. Since 0.7.1
dhcp
The presence of this element enables DHCP services on the virtual network. The dhcp element is supported for both IPv4 (since 0.3.0) and IPv6 (since 1.0.1), but only for one IP address of each type per network. The following sub-elements are supported:
range
The start and end attributes on the range element specify the boundaries of a pool of addresses to be provided to DHCP clients. These two addresses must lie within the scope of the network defined on the parent ip element. There may be zero or more range elements specified. Since 0.3.0
host
Within the dhcp element there may be zero or more host elements. These specify hosts which will be given names and predefined IP addresses by the built-in DHCP server. Any IPv4 host element must specify the MAC address of the host to be assigned a given name (via the mac attribute), the IP to be assigned to that host (via the ip attribute), and the name itself (the name attribute). The IPv6 host element differs slightly from that for IPv4: there is no mac attribute since a MAC address has no defined meaning in IPv6. Instead, the name attribute is used to identify the host to be assigned the IPv6 address. For DHCPv6, the name is the plain name of the client host sent by the client to the server. Note that this method of assigning a specific IP address can also be used for IPv4 instead of the mac attribute. Since 0.4.5
bootp
The optional bootp element specifies BOOTP options to be provided by the DHCP server for IPv4 only. Two attributes are supported: file is mandatory and gives the file to be used for the boot image; server is optional and gives the address of the TFTP server from which the boot image will be fetched. server defaults to the same host that runs the DHCP server, as is the case when the tftp element is used. The BOOTP options currently have to be the same for all address ranges and statically assigned addresses. Since 0.7.1 (server since 0.7.3)
*/
