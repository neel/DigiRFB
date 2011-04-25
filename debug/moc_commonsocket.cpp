/****************************************************************************
** Meta object code from reading C++ file 'commonsocket.h'
**
** Created: Mon Apr 25 11:16:16 2011
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
static const uint qt_meta_data_DG__CommonSocket[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   31,   17,   17, 0x08,
      90,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DG__CommonSocket[] = {
    "DG::CommonSocket\0\0msgWaiting()\0"
    "socketState\0stateChangedSlot(QAbstractSocket::SocketState)\0"
    "readAvailableSlot()\0"
};

const QMetaObject DG::CommonSocket::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_DG__CommonSocket,
      qt_meta_data_DG__CommonSocket, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DG::CommonSocket::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DG::CommonSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DG::CommonSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DG__CommonSocket))
        return static_cast<void*>(const_cast< CommonSocket*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int DG::CommonSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: msgWaiting(); break;
        case 1: stateChangedSlot((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 2: readAvailableSlot(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DG::CommonSocket::msgWaiting()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
