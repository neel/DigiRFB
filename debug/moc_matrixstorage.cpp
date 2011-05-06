/****************************************************************************
** Meta object code from reading C++ file 'matrixstorage.h'
**
** Created: Thu May 5 22:35:15 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../matrixstorage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'matrixstorage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DG__MatrixStorage[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_DG__MatrixStorage[] = {
    "DG::MatrixStorage\0\0enqueued()\0"
};

const QMetaObject DG::MatrixStorage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DG__MatrixStorage,
      qt_meta_data_DG__MatrixStorage, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DG::MatrixStorage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DG::MatrixStorage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DG::MatrixStorage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DG__MatrixStorage))
        return static_cast<void*>(const_cast< MatrixStorage*>(this));
    return QObject::qt_metacast(_clname);
}

int DG::MatrixStorage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: enqueued(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void DG::MatrixStorage::enqueued()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
