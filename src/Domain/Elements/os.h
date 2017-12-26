#ifndef OS_H
#define OS_H

#include <QString>
#include "CustomLibrary/vstringlist.h"
#include "CustomLibrary/vstandarditemmodel.h"
#include <QXmlStreamWriter>


class Os{
  QString kernel;
  QString initrd;
  QString cmdline;
  QString dtb;
  //type
  struct Type{
    QString arch;
    QString machine;
    QString value;
    QString xml();
    bool isEmpty(){
      return arch.isEmpty()&&machine.isEmpty()&&value.isEmpty();
    }
  }type;
  //boot
  struct Loader{
    QString readOnly;
    QString secure;
    QString type;
    QString value;
    QString xml();
    bool isEmpty(){
      return readOnly.isEmpty()&&secure.isEmpty()&&type.isEmpty()&&value.isEmpty();
    }
  }loader;
  struct NVRam{
    QString Template;
    QString value;
    QString xml();
    bool isEmpty(){
      return Template.isEmpty()&&value.isEmpty();
    }
  }nvram;
  struct Boot:public vstringList{

    QString xml(int i){
      return "<boot dev='"+this->at(i)+"'/>";
    }
  };
  Boot *boot;



  //bootmenu
  struct Bootmenu{
    QString enable;
    QString timeout;
    QString xml();
    bool isEmpty(){
      return enable.isEmpty()&&timeout.isEmpty();
    }
  }bootmenu;

  //smbios
  class Smbios{
    QString mode;

  public:
    QString xml(){
      return "<smbios mode='"+mode+"' />";
    }
    bool isEmpty(){
      return  mode.isEmpty();
    }

  }smbios;
  struct Acpi{
    QString tableType;
    QString tableValue;
    bool isEmpty(){
      return tableType.isEmpty()&&tableValue.isEmpty();
    }
    QString xml(){
      QString xml="";
      QXmlStreamWriter stream(&xml);
      stream.setAutoFormatting(true);
      stream.writeStartElement("acpi");
      stream.writeStartElement("table");
      stream.writeAttribute("type",tableType);
      stream.writeCharacters(tableValue);
      stream.writeEndElement();
      stream.writeEndElement();
      return xml;
    }
  }acpi;

  struct Bios{
    QString useSerial;
    QString rebootTimeout;
    QString xml();
    bool isEmpty(){
      return useSerial.isEmpty()&&rebootTimeout.isEmpty();
    }
  }bios;

  struct Container{
    QString init;
    //TODO make init args somthing more like QStandart item
    vstringList *initarg;
    QString initenvName;
    QString initenvValue;
    QString initdir;
    QString inituser;
    QString initgroup;
  }container;


  template <class T>
  void writeXml (QXmlStreamWriter *stream, T b) {
    if(!b.isEmpty())
      stream->writeDTD(b.xml());
  }

  QString getBiosBootloaderXml(){
    QString xml="";
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
    stream.writeStartElement("os");
    writeXml(&stream,type);
    writeXml(&stream,loader);
    writeXml(&stream,nvram);
    if(!boot->isEmpty()){
        for(int i=0;i<boot->size();i++){
           stream.writeDTD(boot->xml(i));
          }
      }
    writeXml(&stream,smbios);
    writeXml(&stream,bios);
    stream.writeEndElement();
    return xml;

  }

  QString getKernelBootXml(){
    QString xml="";
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
    stream.writeStartElement("os");
    writeXml(&stream,type);
    writeXml(&stream,loader);
    stream.writeStartElement("kernel");
    stream.writeCharacters(kernel);
    stream.writeEndElement();
    stream.writeStartElement("initrd");
    stream.writeCharacters(initrd);
    stream.writeEndElement();
    stream.writeStartElement("cmdline");
    stream.writeCharacters(cmdline);
    stream.writeEndElement();
    stream.writeStartElement("dtb");
    stream.writeCharacters(dtb);
    stream.writeEndElement();
    writeXml(&stream,acpi);
    stream.writeEndElement();
    return xml;
  }
  QString getContainerBootXml(){
    QString xml="";
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
    stream.writeStartElement("os");
    writeXml(&stream,type);
    stream.writeStartElement("init");
    stream.writeCharacters(container.init);
    stream.writeEndElement();

    for(int i=0;i<container.initarg->size();i++){
        stream.writeStartElement("intarg");
        stream.writeCharacters(container.initarg->at(1));
        stream.writeEndElement();
      }

    stream.writeStartElement("initenv");
    stream.writeAttribute("name",container.initenvName);
    stream.writeCharacters(container.initenvValue);
    stream.writeEndElement();
    stream.writeStartElement("initdir");
    stream.writeCharacters(container.initdir);
    stream.writeEndElement();
    stream.writeStartElement("inituser");
    stream.writeCharacters(container.inituser);
    stream.writeEndElement();
    stream.writeStartElement("initgroup");
    stream.writeCharacters(container.initgroup);
    stream.writeEndElement();
    stream.writeEndElement();
    return xml;
  }

};
class BootLoader{
  QString Value;
  QString Args;
  bool isEmpty(){
    return Value.isEmpty()&&Args.isEmpty();
  }
  QString getHostBootloaderXml(){
    QString xml="";
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
    stream.writeStartElement("bootloader");
    stream.writeCharacters(Value);
    stream.writeEndElement();
    stream.writeStartElement("bootloader_args");
    stream.writeCharacters(Args);
    stream.writeEndElement();
    return xml;
  }
};
class EntryModel:public VStandardItemModel{
  Q_OBJECT
public:
  enum EntryRoles{
    NameRole=Qt::UserRole+1,
    ValueRole
  };
  Q_INVOKABLE int size(){
    return rowCount();
  }
protected:
  QHash<int, QByteArray> roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ValueRole]="value";
    return roles;
  }

};
class SmbiosSystemInformation{
  static QString entryXml(EntryModel *value){
    QString xml;
    QXmlStreamWriter stream(&xml);
    stream.setAutoFormatting(true);
    int k=0;
    while (value->rowCount()) {
        stream.writeStartElement("entry");
        QString name=(value->data(value->index(k,0),EntryModel::NameRole).toString());
        stream.writeAttribute("name",name);
        QString val=(value->data(value->index(k,0),EntryModel::ValueRole).toString());
        stream.writeCharacters(val);
        stream.writeEndElement();
        k++;
      }
    return xml;
  }
  QString type="smbios";
  struct Bios{
    EntryModel biosEntry;
    QString xml();
  }bios;
  struct System{
    EntryModel systemEntry;
    QString xml();
  }system;
  struct BaseBoard{
    EntryModel baseboardEntry;
    QString xml();
  };
public:
  QString getSmbiosSystemInformation(){
    QString xml;
    return xml;
  }
};


#endif // OS_H
