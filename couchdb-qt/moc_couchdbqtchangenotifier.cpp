/****************************************************************************
** Meta object code from reading C++ file 'couchdbqtchangenotifier.h'
**
** Created: Thu Sep 9 00:19:26 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "couchdbqtchangenotifier.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'couchdbqtchangenotifier.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CouchDBQtChangeNotifier[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   25,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      61,   24,   24,   24, 0x08,
     101,   99,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CouchDBQtChangeNotifier[] = {
    "CouchDBQtChangeNotifier\0\0db,v\0"
    "notification(QString,QVariant)\0"
    "slotNotification(QHttpResponseHeader)\0"
    ",\0slotConnect(int,bool)\0"
};

const QMetaObject CouchDBQtChangeNotifier::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CouchDBQtChangeNotifier,
      qt_meta_data_CouchDBQtChangeNotifier, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CouchDBQtChangeNotifier::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CouchDBQtChangeNotifier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CouchDBQtChangeNotifier::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CouchDBQtChangeNotifier))
        return static_cast<void*>(const_cast< CouchDBQtChangeNotifier*>(this));
    return QObject::qt_metacast(_clname);
}

int CouchDBQtChangeNotifier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: notification((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 1: slotNotification((*reinterpret_cast< const QHttpResponseHeader(*)>(_a[1]))); break;
        case 2: slotConnect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CouchDBQtChangeNotifier::notification(const QString & _t1, const QVariant & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
