/****************************************************************************
** Meta object code from reading C++ file 'commonsocket.h'
**
** Created: Sun Apr 17 00:07:44 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../commonsocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'commonsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CommonSocket[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CommonSocket[] = {
    "CommonSocket\0\0msgWaiting()\0"
    "readAvailableSlot()\0"
};

const QMetaObject CommonSocket::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_CommonSocket,
      qt_meta_data_CommonSocket, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CommonSocket::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CommonSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CommonSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CommonSocket))
        return static_cast<void*>(const_cast< CommonSocket*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int CommonSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: msgWaiting(); break;
        case 1: readAvailableSlot(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CommonSocket::msgWaiting()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
