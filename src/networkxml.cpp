#include "networkxml.h"

void networkxml::setnet(networkxml temp)
{
    name=temp.name;
    isforwardExist=temp.isforwardExist;
    forward=temp.forward;
    bridge=temp.bridge;
    bandwidth=temp.bandwidth;
    ip4=temp.ip4;
    ip6=temp.ip6;
    route=temp.route;
    device=temp.device;
}

void networkxml::setXml(QIODevice *dev)
{
    //    qDebug()<<"__Network_:"<<dev->readAll();
    //    qDebug()<<"____________";
    device=dev;
}

networkxml::networkxml(QIODevice *dev)
{
    device=dev;
    isforwardExist=false;
    bridge.exist=false;
    bandwidth.exist=false;

}
int networkxml::read(){
    QIODevice *dev=device;
    QXmlStreamReader stream1(dev);
    // qDebug()<<device->readAll();
    while (!stream1.atEnd()) {
        if(stream1.isEndElement()){
            qDebug()<<"reached end element";
            stream1.readNext();
            continue;
        }
        if(stream1.isStartElement()){

            if(stream1.name()=="name"){
                stream1.readNext();
                name=stream1.text().toString();
            }
            else if(stream1.name()=="bridge"){
                bridge.exist=true;
                bridge.name=stream1.attributes().value("name").toString();
                bridge.stp=stream1.attributes().value("stp").toString()!=""?stream1.attributes().value("stp").toString():"on";
                bridge.delay=stream1.attributes().value("delay").toString()!=""?stream1.attributes().value("delay").toString():"0";
            }
            else if(stream1.name()=="forward"){
                isforwardExist=true;
                forward.mode=stream1.attributes().value("mode").toString();
                forward.dev=stream1.attributes().value("dev").toString()!=""?stream1.attributes().value("dev").toString():NULL;
                if((forward.mode=="nat")&&(!stream1.isEndElement())){
                    qDebug()<<"nat def is present"<<stream1.isEndElement();
                    stream1.readNextStartElement();
                    if(!stream1.isEndElement()){
                        stream1.readNextStartElement();
                        qDebug()<<stream1.name();
                        forward.natExist=true;
                        forward.nat.start=stream1.attributes().value("start").toString();
                        forward.nat.end=stream1.attributes().value("end").toString();
                    }
                }
            }
            else if(stream1.name()=="bandwidth"){
                bandwidth.exist=true;
                stream1.readNextStartElement();
                qDebug()<<"\nbw read next:"<<stream1.name();
                if(stream1.name()=="inbound"){
                    qDebug()<<"\nbw in avg:"<<(bandwidth.inbound.average=stream1.attributes().value("average").toString());
                    bandwidth.inbound.peak=stream1.attributes().value("peak").toString();
                    bandwidth.inbound.burst=stream1.attributes().value("burst").toString();
                }
                stream1.readNextStartElement();
                stream1.readNextStartElement();
                qDebug()<<"bw read next:"<<stream1.name();
                if(stream1.name()=="outbound"){
                    qDebug()<<(bandwidth.outbound.average=stream1.attributes().value("average").toString());
                    bandwidth.outbound.peak=stream1.attributes().value("peak").toString();
                    bandwidth.outbound.burst=stream1.attributes().value("burst").toString();
                }
            }
            else if(stream1.name()=="ip"){
                IP4 temp;
                IP6 temp1;
                temp.hasDhcp=false;
                temp.dhcp.range.exist=false;
                temp1.hasDhcp=false;
                temp1.dhcp.range.exist=false;
                while(stream1.isEndElement()){
                    stream1.readNextStartElement();
                    qDebug()<<"end string"<<stream1.attributes().value("family").toString();
                }
                qDebug()<<stream1.attributes().value("family").toString();


                if((stream1.attributes().value("family").toString()=="ipv4")||(stream1.attributes().value("family").toString()=="")){
                    temp.exist=true;
                    qDebug()<<"true ip4";
                }
                else if(stream1.attributes().value("family").toString()=="ipv6"){
                    temp1.exist=true;
                }


                if(stream1.attributes().value("family").toString()=="ipv6"){
                    qDebug()<<"ip6";
                    ip6.exist=true;
                    qDebug()<<"family:"<<(temp1.family=stream1.attributes().value("family").toString());
                    qDebug()<<"prefix:"<<(temp1.prefix=stream1.attributes().value("prefix").toString());
                    if(stream1.attributes().value("address").toString()!=""){
                        temp1.address=stream1.attributes().value("address").toString();
                        qDebug()<<"address:"<<(temp1.prefix=stream1.attributes().value("address").toString());
                    }
                    stream1.readNextStartElement();
                    if(stream1.name()=="dhcp"){
                        qDebug()<<stream1.name();
                        temp1.hasDhcp=true;
                        stream1.readNextStartElement();
                        if(stream1.name()=="range"){
                            temp1.dhcp.range.exist=true;
                            temp1.dhcp.range.start=stream1.attributes().value("start").toString();
                            temp1.dhcp.range.end=stream1.attributes().value("end").toString();
                        }

                        while ((stream1.name()=="host")&&(stream1.name()!="")&&(!stream1.atEnd())) {

                            temp.dhcp.hasHost=true;
                            bool flag=false;
                            //HOST *htemp=new HOST();
                            QString ip,mac,id,name;
                            if((temp1.family=="ipv4")||(temp1.family=="")){
                                mac=(stream1.attributes().value("mac").toString());
                                flag=true;
                            }
                            if(stream1.attributes().value("id").toString()!=""){
                                id=(stream1.attributes().value("id").toString());
                                flag=true;
                            }
                            if(stream1.attributes().value("name").toString()!=""){
                                name=(stream1.attributes().value("name").toString());
                                flag=true;
                            }
                            if(stream1.attributes().value("ip").toString()!=""){
                                ip=(stream1.attributes().value("ip").toString());
                                flag=true;
                            }
                            if(flag){
                                temp1.dhcp.host->addHost(HOST(id,mac,name,ip));
                                qDebug()<<stream1.name()<<" name:"<<stream1.attributes().value("name").toString();
                            }
                            stream1.readNextStartElement();
                            while(stream1.isEndElement())
                                stream1.readNextStartElement();
                        }
                    }
                    ip6=temp1;

                    qDebug()<<"size is:"<<ip6.dhcp.host->size();
                }
                else if((stream1.attributes().value("family").toString()=="ipv4")||(stream1.attributes().value("family").toString()=="")){
                    temp.exist=true;
                    qDebug()<<"ip \n \n ip4 \n \n"<<ip4.exist;
                    qDebug()<<"family:"<<(temp.family=stream1.attributes().value("family").toString());
                    qDebug()<<"netmask"<<(temp.netmask=stream1.attributes().value("netmask").toString());
                    if(stream1.attributes().value("address").toString()!=""){
                        temp.address=stream1.attributes().value("address").toString();
                        qDebug()<<"address"<<stream1.attributes().value("address").toString();
                    }
                    stream1.readNextStartElement();
                    if(stream1.name()=="dhcp"){
                        qDebug()<<stream1.name();
                        temp.hasDhcp=true;
                        stream1.readNextStartElement();
                        if(stream1.name()=="range"){
                            temp.dhcp.range.exist=true;
                            temp.dhcp.range.start=stream1.attributes().value("start").toString();
                            temp.dhcp.range.end=stream1.attributes().value("end").toString();
                        }

                        while ((stream1.name()=="host")&&(stream1.name()!="")&&(!stream1.atEnd())) {

                            temp.dhcp.hasHost=true;
                            bool flag=false;
                            QString id,name,mac,ip;

                            if((temp.family=="ipv4")||(temp.family=="")){
                                mac=(stream1.attributes().value("mac").toString());
                                flag=true;
                            }
                            if(stream1.attributes().value("id").toString()!=""){
                                id=(stream1.attributes().value("id").toString());
                                flag=true;
                            }
                            if(stream1.attributes().value("name").toString()!=""){
                                name=(stream1.attributes().value("name").toString());
                                flag=true;
                            }
                            if(stream1.attributes().value("ip").toString()!=""){
                                ip=(stream1.attributes().value("ip").toString());
                                flag=true;
                            }
                            if(flag){
                                //explicit HOST(QString &id,QString &mac,QString &name,QString &ip);
                                temp.dhcp.host->addHost(HOST(id,mac,name,ip));
                                qDebug()<<stream1.name()<<" name:"<<stream1.attributes().value("name").toString();
                            }
                            stream1.readNextStartElement();
                            while(stream1.isEndElement())
                                stream1.readNextStartElement();
                        }
                    }
                    ip4=temp;
                }
                continue;
            }
            else if(stream1.name()=="route"){
                Route temp;
                qDebug()<<stream1.name();
                if(stream1.attributes().value("family").toString()!="ipv6"){
                    temp.family=stream1.attributes().value("family").toString();
                    temp.prefix=stream1.attributes().value("prefix").toString();
                }
                if((stream1.attributes().value("family").toString()!="ipv4")||(stream1.attributes().value("family").toString()!="")){
                    temp.family=stream1.attributes().value("family").toString();
                    temp.netmask=stream1.attributes().value("netmask").toString();
                }
                if(stream1.attributes().value("address").toString()!=""){
                    temp.address=stream1.attributes().value("address").toString();
                }
                if(stream1.attributes().value("gateway").toString()!=""){
                    temp.gateway=stream1.attributes().value("gateway").toString();
                }
                route.append(temp);
            }
        }
        stream1.readNext();

    }
    dev->close();
    return 0;
}

QString networkxml::write(){

    QString xml;

    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
//    stream.writeStartDocument();

    stream.writeStartElement("network");
    stream.writeTextElement("name",name);

    if(bridge.exist){
        stream.writeStartElement("bridge");
        stream.writeAttribute("name", bridge.name);
        stream.writeAttribute("stp", bridge.stp);
        stream.writeAttribute("delay",bridge.delay=="on"?"50":bridge.delay);
        stream.writeEndElement();
    }

    if(isforwardExist){
        stream.writeStartElement("forward");
        stream.writeAttribute("mode", forward.mode);
        qDebug()<<"mode::"<< forward.mode;
        if(forward.dev!=NULL)
            stream.writeAttribute("dev", forward.dev);
        if(forward.natExist){
            stream.writeStartElement("nat");
            stream.writeEmptyElement("port");
            stream.writeAttribute("start", forward.nat.start);
            stream.writeAttribute("end", forward.nat.end);
            stream.writeEndElement();
        }
        stream.writeEndElement();
    }


    if(bandwidth.exist){
        stream.writeStartElement("bandwidth");
        stream.writeEmptyElement("inbound");

        stream.writeAttribute("average", bandwidth.inbound.average);
        stream.writeAttribute("peak", bandwidth.inbound.peak);
        stream.writeAttribute("burst", bandwidth.inbound.burst);
        stream.writeEmptyElement("outbound");
        stream.writeAttribute("average", bandwidth.outbound.average);
        stream.writeAttribute("peak", bandwidth.outbound.peak);
        stream.writeAttribute("burst", bandwidth.outbound.burst);
        stream.writeEndElement();
    }
    int i=0;

    qDebug()<<"i="<<i;

    if(ip4.exist){

        qDebug()<<ip4.hasDhcp;
        stream.writeStartElement("ip");
        if(ip4.family!=NULL)
            stream.writeAttribute("family", ip4.family);
        stream.writeAttribute("address", ip4.address);
        qDebug()<<"Address:"<<ip4.address;
        if(ip4.netmask!=NULL)
            stream.writeAttribute("netmask",ip4.netmask);
        if(ip4.hasDhcp){
            stream.writeStartElement("dhcp");
            if(ip4.dhcp.range.exist){
                stream.writeEmptyElement("range");
                stream.writeAttribute("start", ip4.dhcp.range.start);
                stream.writeAttribute("end", ip4.dhcp.range.end);
            }
            if (ip4.dhcp.hasHost) {
                int k=0;
                while (ip4.dhcp.host->rowCount()>k) {
                    QString id,ip,name,mac;
                    id=ip4.dhcp.host->data(k,"id");
                    ip=ip4.dhcp.host->data(k,"ip");
                    name=ip4.dhcp.host->data(k,"name");
                    mac=ip4.dhcp.host->data(k,"mac");
                    // HOST *Host=new HOST(id,name,mac,ip);
                    stream.writeEmptyElement("host");
                    if(id!=NULL)
                        stream.writeAttribute("id", id);
                    if(mac!=NULL)
                        stream.writeAttribute("mac",mac);
                    if(name!=NULL)
                        stream.writeAttribute("name", name);
                    if(ip!=NULL)
                        stream.writeAttribute("ip",ip);
                    k++;
                }

            }
            stream.writeEndElement();
            stream.writeEndElement();
        }
        else{
            qDebug()<<ip4.hasDhcp;
            stream.writeEmptyElement("ip");
            if(ip4.family!=NULL)
                stream.writeAttribute("family", ip4.family);
            stream.writeAttribute("address", ip4.address);
            //            if(Ip.prefix!=NULL)
            //                stream.writeAttribute("prefix", Ip.prefix);
            if(ip4.netmask!=NULL)
                stream.writeAttribute("netmask", ip4.netmask);
        }
    }

    if(ip6.exist){
        //   IP6 Ip=ip6;

        qDebug()<<ip6.hasDhcp;
        stream.writeStartElement("ip");
        if(ip6.family!=NULL)
            stream.writeAttribute("family", ip6.family);
        stream.writeAttribute("address", ip6.address);
        if(ip6.prefix!=NULL)
            stream.writeAttribute("prefix", ip6.prefix);
        //            if(ip6.netmask!=NULL)
        //                stream.writeAttribute("netmask", ip6.netmask);
        if(ip6.hasDhcp){
            stream.writeStartElement("dhcp");
            if(ip6.dhcp.range.exist){
                stream.writeEmptyElement("range");
                stream.writeAttribute("start", ip6.dhcp.range.start);
                stream.writeAttribute("end", ip6.dhcp.range.end);
            }
            if (ip6.dhcp.hasHost) {
                int k=0;

                while (ip6.dhcp.host->rowCount()>k) {
                    QString id,ip,name,mac;
                    id=ip6.dhcp.host->data(k,"id");
                    ip=ip6.dhcp.host->data(k,"ip");
                    name=ip6.dhcp.host->data(k,"name");
                    mac=ip6.dhcp.host->data(k,"mac");
                    stream.writeEmptyElement("host");
                    if(id!=NULL)
                        stream.writeAttribute("id", id);
                    if(mac!=NULL)
                        stream.writeAttribute("mac",mac);
                    if(name!=NULL)
                        stream.writeAttribute("name", name);
                    if(ip!=NULL)
                        stream.writeAttribute("ip",ip);
                    k++;
                }

            }
            stream.writeEndElement();
            stream.writeEndElement();
        }
        else{
            qDebug()<<ip6.hasDhcp;
            stream.writeEmptyElement("ip");
            if(ip6.family!=NULL)
                stream.writeAttribute("family", ip6.family);
            stream.writeAttribute("address", ip6.address);
            if(ip6.prefix!=NULL)
                stream.writeAttribute("prefix", ip6.prefix);
            //            if(ip6.netmask!=NULL)
            //                stream.writeAttribute("netmask", ip6.netmask);
        }
    }



    i=0;
    while (route.size()>i){
        Route Rou=route.at(i);
        stream.writeStartElement("route");
        if(Rou.family!=NULL)
            stream.writeAttribute("family", Rou.family);
        stream.writeAttribute("address", Rou.address);
        if(Rou.prefix!=NULL)
            stream.writeAttribute("prefix", Rou.prefix);
        if(Rou.netmask!=NULL)
            stream.writeAttribute("netmask", Rou.netmask);
        if(Rou.gateway!=NULL)
            stream.writeAttribute("gateway", Rou.gateway);
        stream.writeEndElement();
        i++;
    }


    stream.writeEndElement();
//    stream.writeEndDocument();

    qDebug()<<"this is war!!!!!"<<xml;
    return xml;
}
