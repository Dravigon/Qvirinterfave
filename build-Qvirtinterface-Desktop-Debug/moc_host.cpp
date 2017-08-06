/****************************************************************************
** Meta object code from reading C++ file 'host.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/host.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'host.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HostModel_t {
    QByteArrayData data[9];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HostModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HostModel_t qt_meta_stringdata_HostModel = {
    {
QT_MOC_LITERAL(0, 0, 9), // "HostModel"
QT_MOC_LITERAL(1, 10, 6), // "create"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 6), // "remove"
QT_MOC_LITERAL(4, 25, 8), // "set_data"
QT_MOC_LITERAL(5, 34, 5), // "index"
QT_MOC_LITERAL(6, 40, 5), // "value"
QT_MOC_LITERAL(7, 46, 4), // "role"
QT_MOC_LITERAL(8, 51, 4) // "size"

    },
    "HostModel\0create\0\0remove\0set_data\0"
    "index\0value\0role\0size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HostModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x02 /* Public */,
       3,    0,   35,    2, 0x02 /* Public */,
       4,    3,   36,    2, 0x02 /* Public */,
       8,    0,   43,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::Int, QMetaType::QVariant, QMetaType::QString,    5,    6,    7,
    QMetaType::QString,

       0        // eod
};

void HostModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HostModel *_t = static_cast<HostModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->create(); break;
        case 1: { bool _r = _t->remove();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->set_data((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { QString _r = _t->size();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject HostModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_HostModel.data,
      qt_meta_data_HostModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *HostModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HostModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HostModel.stringdata0))
        return static_cast<void*>(const_cast< HostModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int HostModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
