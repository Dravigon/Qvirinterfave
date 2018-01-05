/****************************************************************************
** Meta object code from reading C++ file 'vstringlist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/CustomLibrary/vstringlist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vstringlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vstringList_t {
    QByteArrayData data[10];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vstringList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vstringList_t qt_meta_stringdata_vstringList = {
    {
QT_MOC_LITERAL(0, 0, 11), // "vstringList"
QT_MOC_LITERAL(1, 12, 6), // "append"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 6), // "string"
QT_MOC_LITERAL(4, 27, 2), // "at"
QT_MOC_LITERAL(5, 30, 1), // "i"
QT_MOC_LITERAL(6, 32, 6), // "remove"
QT_MOC_LITERAL(7, 39, 5), // "index"
QT_MOC_LITERAL(8, 45, 4), // "size"
QT_MOC_LITERAL(9, 50, 7) // "isEmpty"

    },
    "vstringList\0append\0\0string\0at\0i\0remove\0"
    "index\0size\0isEmpty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vstringList[] = {

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
       1,    1,   39,    2, 0x02 /* Public */,
       4,    1,   42,    2, 0x02 /* Public */,
       6,    1,   45,    2, 0x02 /* Public */,
       8,    0,   48,    2, 0x02 /* Public */,
       9,    0,   49,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::QString, QMetaType::Int,    5,
    QMetaType::Bool, QMetaType::Int,    7,
    QMetaType::Int,
    QMetaType::Bool,

       0        // eod
};

void vstringList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vstringList *_t = static_cast<vstringList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->append((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: { QString _r = _t->at((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->remove((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->size();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->isEmpty();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject vstringList::staticMetaObject = {
    { &QStandardItemModel::staticMetaObject, qt_meta_stringdata_vstringList.data,
      qt_meta_data_vstringList,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *vstringList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vstringList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vstringList.stringdata0))
        return static_cast<void*>(this);
    return QStandardItemModel::qt_metacast(_clname);
}

int vstringList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
