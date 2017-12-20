#ifndef DOMAINATTRIBUTES_H
#define DOMAINATTRIBUTES_H
#include <QString>
#include <QXmlStreamWriter>
#include "CustomLibrary/vstandarditemmodel.h"
#include "./Elements/os.h"

/*<domain type='qemu'>
  <name>QEmu-fedora-i686</name>
  <uuid>c7a5fdbd-cdaf-9455-926a-d65c16db1809</uuid>
  <memory>219200</memory>
  <currentMemory>219200</currentMemory>
  <vcpu>2</vcpu>
  <os>
    <type arch='i686' machine='pc'>hvm</type>
    <boot dev='cdrom'/>
  </os>
  <devices>
    <emulator>/usr/bin/qemu-system-x86_64</emulator>
    <disk type='file' device='cdrom'>
      <source file='/home/user/boot.iso'/>
      <target dev='hdc'/>
      <readonly/>
    </disk>
    <disk type='file' device='disk'>
      <source file='/home/user/fedora.img'/>
      <target dev='hda'/>
    </disk>
    <interface type='network'>
      <source network='default'/>
    </interface>
    <graphics type='vnc' port='-1'/>
  </devices>
</domain>
*/
class VCpus{
  QString placement;
  QString cpuset;
  QString current;
  QString value;
};
class domainAttributes
{
  QString name;
  QString uuid;
  QString title;
  QString description;
  Os os;
  VCpus vcpu;
  QString vcpus;//get value from QML
  QString iothreads;
  //TODO impliment cputune feature when possible
  QString memory;
  QString currentMemory;
public:
  domainAttributes();
};

#endif // DOMAINATTRIBUTES_H
