/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[253];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "openFile"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "saveFile"
QT_MOC_LITERAL(4, 30, 7), // "exitApp"
QT_MOC_LITERAL(5, 38, 9), // "closeFile"
QT_MOC_LITERAL(6, 48, 9), // "showAbout"
QT_MOC_LITERAL(7, 58, 12), // "showHowToUse"
QT_MOC_LITERAL(8, 71, 9), // "logAction"
QT_MOC_LITERAL(9, 81, 7), // "message"
QT_MOC_LITERAL(10, 89, 15), // "updateStatusBar"
QT_MOC_LITERAL(11, 105, 29), // "logActionCurvatureCoefficient"
QT_MOC_LITERAL(12, 135, 24), // "logActionCurvatureFactor"
QT_MOC_LITERAL(13, 160, 21), // "logActionAveragedData"
QT_MOC_LITERAL(14, 182, 12), // "saveFullName"
QT_MOC_LITERAL(15, 195, 11), // "saveComment"
QT_MOC_LITERAL(16, 207, 10), // "newPatient"
QT_MOC_LITERAL(17, 218, 16), // "logActionComment"
QT_MOC_LITERAL(18, 235, 17) // "logActionFullName"

    },
    "MainWindow\0openFile\0\0saveFile\0exitApp\0"
    "closeFile\0showAbout\0showHowToUse\0"
    "logAction\0message\0updateStatusBar\0"
    "logActionCurvatureCoefficient\0"
    "logActionCurvatureFactor\0logActionAveragedData\0"
    "saveFullName\0saveComment\0newPatient\0"
    "logActionComment\0logActionFullName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    1,  100,    2, 0x08 /* Private */,
      10,    0,  103,    2, 0x08 /* Private */,
      11,    1,  104,    2, 0x08 /* Private */,
      12,    1,  107,    2, 0x08 /* Private */,
      13,    1,  110,    2, 0x08 /* Private */,
      14,    0,  113,    2, 0x08 /* Private */,
      15,    0,  114,    2, 0x08 /* Private */,
      16,    0,  115,    2, 0x08 /* Private */,
      17,    1,  116,    2, 0x08 /* Private */,
      18,    1,  119,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openFile(); break;
        case 1: _t->saveFile(); break;
        case 2: _t->exitApp(); break;
        case 3: _t->closeFile(); break;
        case 4: _t->showAbout(); break;
        case 5: _t->showHowToUse(); break;
        case 6: _t->logAction((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->updateStatusBar(); break;
        case 8: _t->logActionCurvatureCoefficient((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->logActionCurvatureFactor((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->logActionAveragedData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->saveFullName(); break;
        case 12: _t->saveComment(); break;
        case 13: _t->newPatient(); break;
        case 14: _t->logActionComment((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->logActionFullName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
