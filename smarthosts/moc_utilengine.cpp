/****************************************************************************
** Meta object code from reading C++ file 'utilengine.h'
**
** Created: Sat Nov 24 12:24:19 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "utilengine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'utilengine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UtilEngine[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   36,   36,   36, 0x05,
      37,   36,   36,   36, 0x05,
      63,   36,   36,   36, 0x05,
      90,  122,   36,   36, 0x05,
     124,  122,   36,   36, 0x05,

 // slots: signature, parameters, type, tag, flags
     167,   36,  179,   36, 0x0a,
     191,   36,  202,   36, 0x0a,
     225,   36,  245,   36, 0x0a,
     253,   36,  245,   36, 0x0a,
     268,   36,  245,   36, 0x0a,
     287,   36,  296,   36, 0x0a,
     301,   36,   36,   36, 0x0a,
     328,   36,   36,   36, 0x0a,
     355,   36,   36,   36, 0x0a,
     378,   36,   36,   36, 0x0a,
     396,   36,   36,   36, 0x0a,
     425,   36,   36,   36, 0x0a,
     445,  122,   36,   36, 0x0a,
     481,   36,   36,   36, 0x08,
     516,   36,   36,   36, 0x08,
     545,  122,   36,   36, 0x08,
     576,  122,   36,   36, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UtilEngine[] = {
    "UtilEngine\0signal_writeHosts_done()\0"
    "\0signal_updateHosts_done()\0"
    "signal_praseDone(QVariant)\0"
    "signal_error(QVariant,QVariant)\0,\0"
    "signal_downloadProgress(QVariant,QVariant)\0"
    "getTitles()\0QStringList\0getItems()\0"
    "QVector<QStringList*>*\0getLastUpdateTime()\0"
    "QString\0getHostsDate()\0getHostsFileType()\0"
    "isRoot()\0bool\0setHostsFileType(QVariant)\0"
    "slot_updateSavedHostFile()\0"
    "slot_writeCleanHosts()\0slot_writeHosts()\0"
    "slot_writeHosts(QStringList)\0"
    "slot_resetUIItems()\0"
    "slot_tickChanged(QVariant,QVariant)\0"
    "slot_replyFinished(QNetworkReply*)\0"
    "slot_parseHostsFile(QString)\0"
    "slot_tickChanged(QString,bool)\0"
    "slot_downloadProgress(qint64,qint64)\0"
};

const QMetaObject UtilEngine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UtilEngine,
      qt_meta_data_UtilEngine, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UtilEngine::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UtilEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UtilEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UtilEngine))
        return static_cast<void*>(const_cast< UtilEngine*>(this));
    return QObject::qt_metacast(_clname);
}

int UtilEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signal_writeHosts_done(); break;
        case 1: signal_updateHosts_done(); break;
        case 2: signal_praseDone((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 3: signal_error((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 4: signal_downloadProgress((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 5: { QStringList _r = getTitles();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 6: { QVector<QStringList*>* _r = getItems();
            if (_a[0]) *reinterpret_cast< QVector<QStringList*>**>(_a[0]) = _r; }  break;
        case 7: { QString _r = getLastUpdateTime();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { QString _r = getHostsDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: { QString _r = getHostsFileType();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: { bool _r = isRoot();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: setHostsFileType((*reinterpret_cast< QVariant(*)>(_a[1]))); break;
        case 12: slot_updateSavedHostFile(); break;
        case 13: slot_writeCleanHosts(); break;
        case 14: slot_writeHosts(); break;
        case 15: slot_writeHosts((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 16: slot_resetUIItems(); break;
        case 17: slot_tickChanged((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 18: slot_replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 19: slot_parseHostsFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: slot_tickChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 21: slot_downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void UtilEngine::signal_writeHosts_done()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void UtilEngine::signal_updateHosts_done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void UtilEngine::signal_praseDone(QVariant _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UtilEngine::signal_error(QVariant _t1, QVariant _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UtilEngine::signal_downloadProgress(QVariant _t1, QVariant _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
