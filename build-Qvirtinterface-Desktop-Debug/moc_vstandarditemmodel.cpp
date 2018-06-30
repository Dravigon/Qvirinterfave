/****************************************************************************
** Meta object code from reading C++ file 'vstandarditemmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/CustomLibrary/vstandarditemmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vstandarditemmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VStandardItemModel_t {
    QByteArrayData data[12];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VStandardItemModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VStandardItemModel_t qt_meta_stringdata_VStandardItemModel = {
    {
QT_MOC_LITERAL(0, 0, 18), // "VStandardItemModel"
QT_MOC_LITERAL(1, 19, 8), // "set_data"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 1), // "i"
QT_MOC_LITERAL(4, 31, 5), // "value"
QT_MOC_LITERAL(5, 37, 4), // "role"
QT_MOC_LITERAL(6, 42, 4), // "size"
QT_MOC_LITERAL(7, 47, 3), // "add"
QT_MOC_LITERAL(8, 51, 14), // "QStandardItem*"
QT_MOC_LITERAL(9, 66, 4), // "item"
QT_MOC_LITERAL(10, 71, 8), // "removeat"
QT_MOC_LITERAL(11, 80, 10) // "removelast"

    },
    "VStandardItemModel\0set_data\0\0i\0value\0"
    "role\0size\0add\0QStandardItem*\0item\0"
    "removeat\0removelast"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VStandardItemModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x02 /* Public */,
       6,    0,   46,    2, 0x02 /* Public */,
       7,    1,   47,    2, 0x02 /* Public */,
      10,    1,   50,    2, 0x02 /* Public */,
      11,    0,   53,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Bool, QMetaType::Int,    3,
    QMetaType::Bool,

       0        // eod
};

void VStandardItemModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VStandardItemModel *_t = static_cast<VStandardItemModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_data((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: { int _r = _t->size();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->add((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 3: { bool _r = _t->removeat((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->removelast();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VStandardItemModel::staticMetaObject = {
    { &QStandardItemModel::staticMetaObject, qt_meta_stringdata_VStandardItemModel.data,
      qt_meta_data_VStandardItemModel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VStandardItemModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VStandardItemModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VStandardItemModel.stringdata0))
        return static_cast<void*>(this);
    return QStandardItemModel::qt_metacast(_clname);
}

int VStandardItemModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStandardItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
