#include "networkxml.h"

networkxml::networkxml(QIODevice *dev)
{
    device=dev;
    isforwardExist=false;
    bridge.exist=false;
    bandwidth.exist=false;

}
int networkxml::read(){
    QXmlStreamReader stream1(device);
    while (!stream1.atEnd()) {
        if(stream1.isStartElement()){
            if(stream1.name()=="name"){
                stream1.readNext();
                name=stream1.text().toString();
            }

            else if(stream1.name()=="bridge"){
                bridge.exist=true;
                bridge.name=stream1.attributes().value("name").toString();
                bridge.stp=stream1.attributes().value("stp").toString()!=""?stream1.attributes().value("stp").toString():"on";
                bridge.delay=stream1.attributes().value("delay").toString()!=""?stream1.attributes().value("stp").toString():"0";
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
                IP temp;
                temp.hasDhcp=false;
                temp.dhcp.range.exist=false;
                while(stream1.isEndElement()){
                    stream1.readNextStartElement();
                    qDebug()<<"end string"<<stream1.attributes().value("family").toString();
                }
                qDebug()<<stream1.attributes().value("family").toString();

                if(stream1.attributes().value("family").toString()=="ipv6"){
                    qDebug()<<"ip6";
                    qDebug()<<(temp.family=stream1.attributes().value("family").toString());
                    qDebug()<<(temp.prefix=stream1.attributes().value("prefix").toString());
                }
                if((stream1.attributes().value("family").toString()=="ipv4")||(stream1.attributes().value("family").toString()=="")){
                    qDebug()<<"ip";
                    qDebug()<<(temp.family=stream1.attributes().value("family").toString());
                    qDebug()<<(temp.netmask=stream1.attributes().value("netmask").toString());
                }
                if(stream1.attributes().value("address").toString()!=""){
                    temp.address=stream1.attributes().value("address").toString();
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
                        HOST htemp;
                        if((temp.family=="ipv4")||(temp.family=="")){
                            htemp.mac=stream1.attributes().value("mac").toString();
                            flag=true;
                        }
                        if(stream1.attributes().value("id").toString()!=""){
                            htemp.id=stream1.attributes().value("id").toString();
                            flag=true;
                        }
                        if(stream1.attributes().value("name").toString()!=""){
                            htemp.name=stream1.attributes().value("name").toString();
                            flag=true;
                        }
                        if(stream1.attributes().value("ip").toString()!=""){
                            htemp.ip=stream1.attributes().value("ip").toString();
                            flag=true;
                        }
                        if(flag){
                            temp.dhcp.host.append(htemp);
                            qDebug()<<stream1.name()<<" name:"<<stream1.attributes().value("name").toString();
                        }
                        stream1.readNextStartElement();
                        while(stream1.isEndElement())
                            stream1.readNextStartElement();
                    }
                }
                ip.append(temp);
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
        stream1.readNextStartElement();

    }
    device->close();
    return 0;
}

int networkxml::write(){

    device->open(QIODevice::ReadWrite);
    QXmlStreamWriter stream(device);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();

    stream.writeStartElement("network");
    stream.writeTextElement("name",name);

    if(bridge.exist){
        stream.writeStartElement("bridge");
        stream.writeAttribute("name", bridge.name);
        stream.writeAttribute("stp", bridge.stp);
        stream.writeAttribute("delay",bridge.delay);
        stream.writeEndElement();
    }

    if(isforwardExist){
        stream.writeStartElement("forward");
        stream.writeAttribute("mode", forward.mode);
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
    while (i<ip.size()){
        qDebug()<<"i="<<i;
        IP Ip=ip.at(i);
        if(Ip.hasDhcp){
            qDebug()<<Ip.hasDhcp;
            stream.writeStartElement("ip");
            if(Ip.family!=NULL)
                stream.writeAttribute("family", Ip.family);
            stream.writeAttribute("address", Ip.address);
            if(Ip.prefix!=NULL)
                stream.writeAttribute("prefix", Ip.prefix);
            if(Ip.netmask!=NULL)
                stream.writeAttribute("netmask", Ip.netmask);

            stream.writeStartElement("dhcp");
            if(Ip.dhcp.range.exist){
                stream.writeEmptyElement("range");
                stream.writeAttribute("start", Ip.dhcp.range.start);
                stream.writeAttribute("end", Ip.dhcp.range.end);
            }
            if (Ip.dhcp.hasHost) {
                int k=0;
                while (Ip.dhcp.host.size()>k) {
                    HOST Host=Ip.dhcp.host.at(k);
                    stream.writeEmptyElement("host");
                    if(Host.id!=NULL)
                        stream.writeAttribute("id", Host.id);
                    if(Host.mac!=NULL)
                        stream.writeAttribute("mac", Host.mac);
                    if(Host.name!=NULL)
                        stream.writeAttribute("name", Host.name);
                    if(Host.ip!=NULL)
                        stream.writeAttribute("ip", Host.ip);
                    k++;
                }

            }
            stream.writeEndElement();
            stream.writeEndElement();
        }
        else{
            qDebug()<<Ip.hasDhcp;
            stream.writeEmptyElement("ip");
            if(Ip.family!=NULL)
                stream.writeAttribute("family", Ip.family);
            stream.writeAttribute("address", Ip.address);
            if(Ip.prefix!=NULL)
                stream.writeAttribute("prefix", Ip.prefix);
            if(Ip.netmask!=NULL)
                stream.writeAttribute("netmask", Ip.netmask);
        }
        i++;
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
    stream.writeEndDocument();
    device->close();
    return 0;
}
