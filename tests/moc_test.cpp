/****************************************************************************
** Meta object code from reading C++ file 'test.h'
**
** Created: Sun Apr 4 19:03:27 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "test.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ResponsePrinter[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   17,   16,   16, 0x08,
      49,   16,   16,   16, 0x08,
      97,   94,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ResponsePrinter[] = {
    "ResponsePrinter\0\0list\0showDataBases(QStringList)\0"
    "showDataBaseEntries(CouchDBDocumentInfoList)\0"
    "qv\0showEntry(QVariant)\0"
};

const QMetaObject ResponsePrinter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ResponsePrinter,
      qt_meta_data_ResponsePrinter, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ResponsePrinter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ResponsePrinter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ResponsePrinter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ResponsePrinter))
        return static_cast<void*>(const_cast< ResponsePrinter*>(this));
    return QObject::qt_metacast(_clname);
}

int ResponsePrinter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showDataBases((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 1: showDataBaseEntries((*reinterpret_cast< const CouchDBDocumentInfoList(*)>(_a[1]))); break;
        case 2: showEntry((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
