/****************************************************************************
** Meta object code from reading C++ file 'couchdb-qt.h'
**
** Created: Fri Apr 16 21:54:16 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "couchdb-qt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'couchdb-qt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CouchDBQt[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   11,   10,   10, 0x05,
      53,   50,   10,   10, 0x25,
      75,   11,   10,   10, 0x05,
     105,   50,   10,   10, 0x25,
     127,   10,   10,   10, 0x05,
     156,   10,   10,   10, 0x05,
     199,  197,   10,   10, 0x05,
     227,   11,   10,   10, 0x05,
     257,   50,   10,   10, 0x25,
     279,   11,   10,   10, 0x05,
     309,   50,   10,   10, 0x25,
     341,  331,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     378,   10,   10,   10, 0x0a,
     397,  394,   10,   10, 0x0a,
     421,  394,   10,   10, 0x0a,
     445,  394,   10,   10, 0x0a,
     473,  468,   10,   10, 0x0a,
     513,  506,   10,   10, 0x0a,
     577,  558,   10,   10, 0x0a,
     618,  468,   10,   10, 0x0a,
     660,  654,   10,   10, 0x0a,
     698,   10,   10,   10, 0x08,
     728,   10,   10,   10, 0x08,
     758,   10,   10,   10, 0x08,
     790,   10,   10,   10, 0x08,
     819,   10,   10,   10, 0x08,
     848,   10,   10,   10, 0x08,
     879,   10,   10,   10, 0x08,
     910,   10,   10,   10, 0x08,
     947,  394,   10,   10, 0x08,
     982,  197,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CouchDBQt[] = {
    "CouchDBQt\0\0ok,error\0databaseCreated(bool,QString)\0"
    "ok\0databaseCreated(bool)\0"
    "databaseDeleted(bool,QString)\0"
    "databaseDeleted(bool)\0"
    "databasesListed(QStringList)\0"
    "documentsListed(CouchDBDocumentInfoList)\0"
    "v\0documentRetrieved(QVariant)\0"
    "documentUpdated(bool,QString)\0"
    "documentUpdated(bool)\0"
    "documentRemoved(bool,QString)\0"
    "documentRemoved(bool)\0db,change\0"
    "changeNotification(QString,QVariant)\0"
    "listDatabases()\0db\0createDatabase(QString)\0"
    "deleteDatabase(QString)\0listDocuments(QString)\0"
    "info\0getDocument(CouchDBDocumentInfo)\0"
    "info,v\0updateDocument(CouchDBDocumentInfo,QVariant)\0"
    "docname,database,v\0"
    "createDocument(QString,QString,QVariant)\0"
    "deleteDocument(CouchDBDocumentInfo)\0"
    "db,on\0setNotificationsEnabled(QString,bool)\0"
    "slotDatabaseListingFinished()\0"
    "slotDocumentListingFinished()\0"
    "slotDocumentRetrievalFinished()\0"
    "slotDocumentUpdateFinished()\0"
    "slotDocumentDeleteFinished()\0"
    "slotDatabaseCreationFinished()\0"
    "slotDatabaseDeletionFinished()\0"
    "slotDocumentDeleteProgress(QVariant)\0"
    "slotNotificationTriggered(QString)\0"
    "slotDocumentUpdateProgress(QVariant)\0"
};

const QMetaObject CouchDBQt::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CouchDBQt,
      qt_meta_data_CouchDBQt, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CouchDBQt::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CouchDBQt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CouchDBQt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CouchDBQt))
        return static_cast<void*>(const_cast< CouchDBQt*>(this));
    return QObject::qt_metacast(_clname);
}

int CouchDBQt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: databaseCreated((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: databaseCreated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: databaseDeleted((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: databaseDeleted((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: databasesListed((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 5: documentsListed((*reinterpret_cast< const CouchDBDocumentInfoList(*)>(_a[1]))); break;
        case 6: documentRetrieved((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 7: documentUpdated((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: documentUpdated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: documentRemoved((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: documentRemoved((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: changeNotification((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 12: listDatabases(); break;
        case 13: createDatabase((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: deleteDatabase((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: listDocuments((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: getDocument((*reinterpret_cast< const CouchDBDocumentInfo(*)>(_a[1]))); break;
        case 17: updateDocument((*reinterpret_cast< const CouchDBDocumentInfo(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 18: createDocument((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QVariant(*)>(_a[3]))); break;
        case 19: deleteDocument((*reinterpret_cast< const CouchDBDocumentInfo(*)>(_a[1]))); break;
        case 20: setNotificationsEnabled((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 21: slotDatabaseListingFinished(); break;
        case 22: slotDocumentListingFinished(); break;
        case 23: slotDocumentRetrievalFinished(); break;
        case 24: slotDocumentUpdateFinished(); break;
        case 25: slotDocumentDeleteFinished(); break;
        case 26: slotDatabaseCreationFinished(); break;
        case 27: slotDatabaseDeletionFinished(); break;
        case 28: slotDocumentDeleteProgress((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 29: slotNotificationTriggered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 30: slotDocumentUpdateProgress((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 31;
    }
    return _id;
}

// SIGNAL 0
void CouchDBQt::databaseCreated(bool _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void CouchDBQt::databaseDeleted(bool _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void CouchDBQt::databasesListed(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CouchDBQt::documentsListed(const CouchDBDocumentInfoList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CouchDBQt::documentRetrieved(const QVariant & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CouchDBQt::documentUpdated(bool _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 9
void CouchDBQt::documentRemoved(bool _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 11
void CouchDBQt::changeNotification(const QString & _t1, const QVariant & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_END_MOC_NAMESPACE
