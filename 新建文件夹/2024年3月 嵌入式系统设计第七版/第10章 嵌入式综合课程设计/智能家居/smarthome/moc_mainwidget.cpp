/****************************************************************************
** Meta object code from reading C++ file 'mainwidget.h'
**
** Created: Thu May 9 01:26:41 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      34,   11,   11,   11, 0x05,
      56,   11,   11,   11, 0x05,
      77,   11,   11,   11, 0x05,
      99,   11,   11,   11, 0x05,
     121,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     142,   11,   11,   11, 0x0a,
     168,  164,   11,   11, 0x0a,
     187,   11,   11,   11, 0x0a,
     221,  214,   11,   11, 0x0a,
     239,   11,   11,   11, 0x0a,
     255,   11,   11,   11, 0x0a,
     270,   11,   11,   11, 0x0a,
     286,   11,   11,   11, 0x0a,
     302,   11,   11,   11, 0x0a,
     317,   11,   11,   11, 0x0a,
     333,   11,   11,   11, 0x0a,
     344,   11,   11,   11, 0x0a,
     356,   11,   11,   11, 0x0a,
     370,  368,   11,   11, 0x0a,
     394,  390,   11,   11, 0x0a,
     407,  390,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWidget[] = {
    "MainWidget\0\0Irda_StateChanged_1()\0"
    "Smog_StateChanged_1()\0Int_StateChanged_1()\0"
    "Irda_StateChanged_0()\0Smog_StateChanged_0()\0"
    "Int_StateChanged_0()\0on_btn_Back_clicked()\0"
    "btn\0onBtn_clicked(int)\0"
    "pushButton_light_clicked()\0sensor\0"
    "gprs_sendMsg(int)\0Smog_change_1()\0"
    "Int_change_1()\0Irda_change_1()\0"
    "Smog_change_0()\0Int_change_0()\0"
    "Irda_change_0()\0int_show()\0smog_show()\0"
    "irda_show()\0x\0show_TempHum(ulong)\0sim\0"
    "Set_Sim(int)\0Set_Send(int)\0"
};

const QMetaObject MainWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWidget,
      qt_meta_data_MainWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWidget))
        return static_cast<void*>(const_cast< MainWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Irda_StateChanged_1(); break;
        case 1: Smog_StateChanged_1(); break;
        case 2: Int_StateChanged_1(); break;
        case 3: Irda_StateChanged_0(); break;
        case 4: Smog_StateChanged_0(); break;
        case 5: Int_StateChanged_0(); break;
        case 6: on_btn_Back_clicked(); break;
        case 7: onBtn_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: pushButton_light_clicked(); break;
        case 9: gprs_sendMsg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: Smog_change_1(); break;
        case 11: Int_change_1(); break;
        case 12: Irda_change_1(); break;
        case 13: Smog_change_0(); break;
        case 14: Int_change_0(); break;
        case 15: Irda_change_0(); break;
        case 16: int_show(); break;
        case 17: smog_show(); break;
        case 18: irda_show(); break;
        case 19: show_TempHum((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        case 20: Set_Sim((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: Set_Send((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void MainWidget::Irda_StateChanged_1()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWidget::Smog_StateChanged_1()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWidget::Int_StateChanged_1()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainWidget::Irda_StateChanged_0()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void MainWidget::Smog_StateChanged_0()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void MainWidget::Int_StateChanged_0()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
