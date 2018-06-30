#include "storagepoolattributes.h"

StoragePoolAttributes::StoragePoolAttributes()
{

}

bool StoragePoolAttributes::Auth::isEmpty(){
    return type.isEmpty()&&(username.isEmpty()||Usage.isEmpty());
}

QString StoragePoolAttributes::Auth::xml(){
    QString auth="<auth ";
    if(!type.isEmpty())auth.append("type='"+type+"' ");
    if(!username.isEmpty())auth.append("username='"+username+"' ");
    auth.append("> <secret usage='"+Usage+"'/>");
    auth.append("</auth>");
    return auth;
}

Qstring StoragePoolAttributes::Source::xml(){
    QString xml="";
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
    stream.writeStartElement("source");
    for(int i=0;i<hostName.size();i++){
        stream.writeEmptyElement("host");
        QString name,port;
        if(!(name=hostName.at(i)).isEmpty())
            stream.writeAttribute("name", name);
        if(!(port=hostPort.at(i)).isEmpty())
            stream.writeAttribute("port", end);
    }
    for(int i=0;i<devicePath.size();i++){
        stream.writeEmptyElement("device");
        QString path;
        if(!(name=hostName.at(i)).isEmpty())
            stream.writeAttribute("path", path);
    }
    if(!auth.isEmpty())
        stream.writeDTD(auth.xml());
    stream.writeEmptyElement("format");
    stream.writeAttribute("type",formatType);
    stream.writeEndElement();
    return xml;
}

//      <permissions>
//        <owner>107</owner>
//        <group>107</group>
//        <mode>0744</mode>
//        <label>virt_image_t</label>
//      </permissions>



QString StoragePoolAttributes::Permission::xml(){
    QString xml="";
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
    stream.writeStartElement("permissions");
    if(!owner.isEmpty())
        stream.writeTextElement("owner",owner);
    if(!group.isEmpty())
        stream.writeTextElement("group",group);
    if(!mode.isEmpty())
        stream.writeTextElement("mode",mode);
    if(!label.isEmpty())
        stream.writeTextElement("label",label);
    stream.writeEndElement();
    return xml;
}

bool StoragePoolAttributes::Permission::isEmpty(){
    return owner.isEmpty()||group.isEmpty()||mode.isEmpty()||label.isEmpty();
}

QString StoragePoolAttributes::LuksEncryption::xml(){
    QString xml="";
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
    stream.writeEmptyElement("cipher");
    if(!cipherName.isEmpty())
        stream.writeAttribute("name",cipherName);
    if(!cipherSize.isEmpty())
        stream.writeAttribute("size",cipherSize);
    if(!cipherMode.isEmpty())
        stream.writeAttribute("mode",cipherMode);
    if(!cipherHash.isEmpty())
        stream.writeAttribute("hash",cipherHash);
    stream.writeEmptyElement("ivgen");
    if(!ivgenName.isEmpty())
        stream.writeAttribute("name",ivgenName);
    if(!ivgenHash.isEmpty())
        stream.writeAttribute("hash",ivgenHash);
    return xml;
}

QString StoragePoolAttributes::Encryption::xml(){
    //    <encryption format='luks'>
    //       <secret type='passphrase' uuid='f52a81b2-424e-490c-823d-6bd4235bc572'/>
    //       <cipher name='twofish' size='256' mode='cbc' hash='sha256'/>
    //       <ivgen name='plain64' hash='sha256'/>
    //    </encryption>
    QString xml="";
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
    stream.writeStartElement("encryption");
    stream.writeAttribute("format",encryptionType);
    stream.writeEmptyElement("secret");
    stream.writeAttribute("type",secretType);
    if(!secretUuid.isEmpty())
        stream.writeAttribute("uuid",secretUuid);
    if(!secretUsage.isEmpty())
        stream.writeAttribute("usage",secretUsage);
    if(encryptionType=="luks"){
        stream.writeDTD(luksencryption.xml());
    }
    stream.writeEndElement();
    return xml;
}

bool StoragePoolAttributes::Encryption::isEmpty(){
    return encryptionType.isEmpty()&&secretType.isEmpty()&&(secretUsage.isEmpty()||secretUuid.isEmpty());
}

QString StoragePoolAttributes::Target::xml(){
    QString xml="";
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
    stream.writeStartElement("target");
    stream.writeTextElement("path",path);
    stream.writeEmptyElement("format");
    stream.writeAttribute("type",formatType);
    if(!permission.isEmpty())
        stream.writeDTD(permission.xml());
    if(!encryption.isEmpty())
        stream.writeDTD(encryption.xml());
    stream.writeEndElement();
}
