#ifndef STORAGEPOOLATTRIBUTES_H
#define STORAGEPOOLATTRIBUTES_H
#include <QString>
#include <QXmlStreamWriter>

class StoragePoolAttributes
{
    QString name;
    QString allocation;
    QString capacity;
    QString capacityUnit;
    struct Auth{
        QString type;
        QString username;
        QString Usage;
        bool isEmpty();
        QString xml();
    };
    struct Source
    {
        QString name;
        QStringList hostName;
        QStringList hostPort;
        Auth auth;
        QStringList devicePath;
        QString formatType;
        Source() {}
        //TODO <adapter>
        Qstring xml();
    };
    struct Permission{
        QString owner;
        QString group;
        QString mode;
        QString label;
        QString xml();
        bool isEmpty();
    };

    struct LuksEncryption{
        QString cipherName;
        QString cipherSize;
        QString cipherMode;
        QString cipherHash;
        QString ivgenName;
        QString ivgenHash;
        QString xml();
    };
    struct Encryption{
        QString encryptionType;
        QString secretType;
        QString secretUuid;
        QString secretUsage;
        LuksEncryption luksencryption;
        QString xml();
        bool isEmpty();
    };
    struct Target
    {
        QString path;
        QString formatType;
        Permission permission;
        Encryption encryption;
        //TODO timestamp
        //TODO   <compat>1.1</compat>
//        <nocow/>
//        <features>
//          <lazy_refcounts/>
//        </features>
        Target() {}
        QString xml();
    };
public:
    StoragePoolAttributes();

};

#endif // STORAGEPOOLATTRIBUTES_H
