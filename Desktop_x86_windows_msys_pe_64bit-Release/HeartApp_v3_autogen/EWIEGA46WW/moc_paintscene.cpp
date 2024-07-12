/****************************************************************************
** Meta object code from reading C++ file 'paintscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../paintscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paintscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_paintScene_t {
    QByteArrayData data[14];
    char stringdata0[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_paintScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_paintScene_t qt_meta_stringdata_paintScene = {
    {
QT_MOC_LITERAL(0, 0, 10), // "paintScene"
QT_MOC_LITERAL(1, 11, 18), // "actionPerformedLog"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "message"
QT_MOC_LITERAL(4, 39, 35), // "actionPerformedCurvatureCoeff..."
QT_MOC_LITERAL(5, 75, 21), // "actionPerformedFactor"
QT_MOC_LITERAL(6, 97, 22), // "actionPerformedAverage"
QT_MOC_LITERAL(7, 120, 23), // "actionPerformedFullName"
QT_MOC_LITERAL(8, 144, 22), // "actionPerformedComment"
QT_MOC_LITERAL(9, 167, 24), // "actionPerformedStatusBar"
QT_MOC_LITERAL(10, 192, 17), // "imageIndexChanged"
QT_MOC_LITERAL(11, 210, 5), // "index"
QT_MOC_LITERAL(12, 216, 11), // "imageOpened"
QT_MOC_LITERAL(13, 228, 8) // "fileName"

    },
    "paintScene\0actionPerformedLog\0\0message\0"
    "actionPerformedCurvatureCoefficient\0"
    "actionPerformedFactor\0actionPerformedAverage\0"
    "actionPerformedFullName\0actionPerformedComment\0"
    "actionPerformedStatusBar\0imageIndexChanged\0"
    "index\0imageOpened\0fileName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_paintScene[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       5,    1,   65,    2, 0x06 /* Public */,
       6,    1,   68,    2, 0x06 /* Public */,
       7,    1,   71,    2, 0x06 /* Public */,
       8,    1,   74,    2, 0x06 /* Public */,
       9,    1,   77,    2, 0x06 /* Public */,
      10,    1,   80,    2, 0x06 /* Public */,
      12,    1,   83,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::QString,   13,

       0        // eod
};

void paintScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<paintScene *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->actionPerformedLog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->actionPerformedCurvatureCoefficient((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->actionPerformedFactor((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->actionPerformedAverage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->actionPerformedFullName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->actionPerformedComment((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->actionPerformedStatusBar((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->imageIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->imageOpened((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (paintScene::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&paintScene::actionPerformedLog)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (paintScene::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&paintScene::actionPerformedCurvatureCoefficient)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (paintScene::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&paintScene::actionPerformedFactor)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (paintScene::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&paintScene::actionPerformedAverage)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (paintScene::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&paintScene::actionPerformedFullName)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (paintScene::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&paintScene::actionPerformedComment)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (paintScene::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&paintScene::actionPerformedStatusBar)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (paintScene::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&paintScene::imageIndexChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (paintScene::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&paintScene::imageOpened)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject paintScene::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_paintScene.data,
    qt_meta_data_paintScene,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *paintScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *paintScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_paintScene.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int paintScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void paintScene::actionPerformedLog(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void paintScene::actionPerformedCurvatureCoefficient(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void paintScene::actionPerformedFactor(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void paintScene::actionPerformedAverage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void paintScene::actionPerformedFullName(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void paintScene::actionPerformedComment(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void paintScene::actionPerformedStatusBar(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void paintScene::imageIndexChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void paintScene::imageOpened(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
