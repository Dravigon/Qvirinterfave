/****************************************************************************
** Meta object code from reading C++ file 'networkmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/networkmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetworkModel_t {
    QByteArrayData data[11];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkModel_t qt_meta_stringdata_NetworkModel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "NetworkModel"
QT_MOC_LITERAL(1, 13, 4), // "task"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 5), // "index"
QT_MOC_LITERAL(4, 25, 8), // "set_data"
QT_MOC_LITERAL(5, 34, 5), // "value"
QT_MOC_LITERAL(6, 40, 4), // "role"
QT_MOC_LITERAL(7, 45, 7), // "refresh"
QT_MOC_LITERAL(8, 53, 10), // "setXmlData"
QT_MOC_LITERAL(9, 64, 7), // "ipIndex"
QT_MOC_LITERAL(10, 72, 9) // "dhcpIndex"

    },
    "NetworkModel\0task\0\0index\0set_data\0"
    "value\0role\0refresh\0setXmlData\0ipIndex\0"
    "dhcpIndex"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       2,   50, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x02 /* Public */,
       4,    3,   39,    2, 0x02 /* Public */,
       7,    0,   46,    2, 0x02 /* Public */,
       8,    1,   47,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::QString, QMetaType::QString, QMetaType::Int,    1,    3,
    QMetaType::Bool, QMetaType::Int, QMetaType::QVariant, QMetaType::QString,    3,    5,    6,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int,    3,

 // properties: name, type, flags
       9, QMetaType::Int, 0x00095103,
      10, QMetaType::Int, 0x00095103,

       0        // eod
};

void NetworkModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NetworkModel *_t = static_cast<NetworkModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QString _r = _t->task((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->set_data((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->refresh(); break;
        case 3: { bool _r = _t->setXmlData((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        NetworkModel *_t = static_cast<NetworkModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->ipIndex(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->dhcpIndex(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        NetworkModel *_t = static_cast<NetworkModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setIpIndex(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setDhcpIndex(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject NetworkModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_NetworkModel.data,
      qt_meta_data_NetworkModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NetworkModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkModel.stringdata0))
        return static_cast<void*>(const_cast< NetworkModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int NetworkModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
