/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created: Thu May 9 01:26:34 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QFrame *frame_10;
    QFrame *frame_11;
    QPushButton *pushButton_light;
    QLabel *label_temp;
    QLabel *label_temp_value;
    QLabel *label_hum;
    QLabel *label_hum_value;
    QLabel *label_temp_value_2;
    QLabel *label_hum_value_2;
    QFrame *frame_12;
    QLabel *label_warn;
    QLineEdit *number_value;
    QLabel *label;
    QFrame *frame_13;
    QPushButton *Steln;
    QPushButton *key6;
    QPushButton *key4;
    QPushButton *key0;
    QPushButton *btn_Back;
    QPushButton *key2;
    QPushButton *key8;
    QPushButton *key3;
    QPushButton *key1;
    QPushButton *key9;
    QPushButton *key7;
    QPushButton *key5;
    QLabel *style;
    QLabel *weizhi;
    QLabel *state_b;
    QLabel *state;
    QLabel *style_value_3;
    QLabel *state_value;
    QLabel *weizhi_b;
    QLabel *weizhi_value;
    QLabel *style_b;
    QLabel *state_sim;
    QLabel *state_b_sim;
    QLabel *state_b_sim_2;
    QLabel *send_msg;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(800, 480);
        MainWidget->setStyleSheet(QString::fromUtf8(""));
        frame_10 = new QFrame(MainWidget);
        frame_10->setObjectName(QString::fromUtf8("frame_10"));
        frame_10->setGeometry(QRect(14, 60, 772, 407));
        frame_10->setFrameShape(QFrame::StyledPanel);
        frame_10->setFrameShadow(QFrame::Raised);
        frame_11 = new QFrame(frame_10);
        frame_11->setObjectName(QString::fromUtf8("frame_11"));
        frame_11->setGeometry(QRect(0, 0, 558, 407));
        frame_11->setFrameShape(QFrame::StyledPanel);
        frame_11->setFrameShadow(QFrame::Raised);
        pushButton_light = new QPushButton(frame_11);
        pushButton_light->setObjectName(QString::fromUtf8("pushButton_light"));
        pushButton_light->setGeometry(QRect(310, 220, 59, 61));
        QFont font;
        font.setPointSize(14);
        pushButton_light->setFont(font);
        pushButton_light->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        label_temp = new QLabel(frame_11);
        label_temp->setObjectName(QString::fromUtf8("label_temp"));
        label_temp->setGeometry(QRect(10, 10, 60, 25));
        label_temp->setFont(font);
        label_temp->setStyleSheet(QString::fromUtf8(""));
        label_temp_value = new QLabel(frame_11);
        label_temp_value->setObjectName(QString::fromUtf8("label_temp_value"));
        label_temp_value->setGeometry(QRect(60, 10, 40, 25));
        label_temp_value->setFont(font);
        label_temp_value->setStyleSheet(QString::fromUtf8(""));
        label_hum = new QLabel(frame_11);
        label_hum->setObjectName(QString::fromUtf8("label_hum"));
        label_hum->setGeometry(QRect(140, 10, 60, 25));
        label_hum->setFont(font);
        label_hum->setStyleSheet(QString::fromUtf8(""));
        label_hum_value = new QLabel(frame_11);
        label_hum_value->setObjectName(QString::fromUtf8("label_hum_value"));
        label_hum_value->setGeometry(QRect(180, 10, 40, 25));
        label_hum_value->setFont(font);
        label_hum_value->setStyleSheet(QString::fromUtf8(""));
        label_temp_value_2 = new QLabel(frame_11);
        label_temp_value_2->setObjectName(QString::fromUtf8("label_temp_value_2"));
        label_temp_value_2->setGeometry(QRect(100, 10, 50, 25));
        label_temp_value_2->setFont(font);
        label_temp_value_2->setStyleSheet(QString::fromUtf8(""));
        label_hum_value_2 = new QLabel(frame_11);
        label_hum_value_2->setObjectName(QString::fromUtf8("label_hum_value_2"));
        label_hum_value_2->setGeometry(QRect(220, 10, 50, 25));
        label_hum_value_2->setFont(font);
        label_hum_value_2->setStyleSheet(QString::fromUtf8(""));
        frame_12 = new QFrame(frame_10);
        frame_12->setObjectName(QString::fromUtf8("frame_12"));
        frame_12->setGeometry(QRect(564, 0, 208, 407));
        frame_12->setFrameShape(QFrame::StyledPanel);
        frame_12->setFrameShadow(QFrame::Raised);
        label_warn = new QLabel(frame_12);
        label_warn->setObjectName(QString::fromUtf8("label_warn"));
        label_warn->setGeometry(QRect(150, 10, 51, 51));
        label_warn->setFont(font);
        label_warn->setStyleSheet(QString::fromUtf8(""));
        number_value = new QLineEdit(frame_12);
        number_value->setObjectName(QString::fromUtf8("number_value"));
        number_value->setGeometry(QRect(59, 210, 141, 30));
        QFont font1;
        font1.setPointSize(12);
        number_value->setFont(font1);
        number_value->setFocusPolicy(Qt::ClickFocus);
        number_value->setMaxLength(11);
        number_value->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label = new QLabel(frame_12);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 210, 35, 30));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/images/telphone.png);"));
        frame_13 = new QFrame(frame_12);
        frame_13->setObjectName(QString::fromUtf8("frame_13"));
        frame_13->setGeometry(QRect(20, 243, 180, 161));
        frame_13->setFrameShape(QFrame::StyledPanel);
        frame_13->setFrameShadow(QFrame::Raised);
        Steln = new QPushButton(frame_13);
        Steln->setObjectName(QString::fromUtf8("Steln"));
        Steln->setGeometry(QRect(65, 120, 50, 38));
        Steln->setStyleSheet(QString::fromUtf8("outline-style:none;\n"
"background-image: url(:/images/savenum.png);"));
        Steln->setFlat(true);
        key6 = new QPushButton(frame_13);
        key6->setObjectName(QString::fromUtf8("key6"));
        key6->setGeometry(QRect(6, 44, 50, 38));
        key6->setStyleSheet(QString::fromUtf8("background-image: url(:/images/6.png);\n"
"outline-style:none;"));
        key6->setFlat(true);
        key4 = new QPushButton(frame_13);
        key4->setObjectName(QString::fromUtf8("key4"));
        key4->setGeometry(QRect(124, 44, 50, 38));
        key4->setStyleSheet(QString::fromUtf8("background-image: url(:/images/4.png);\n"
"outline-style:none;"));
        key4->setFlat(true);
        key0 = new QPushButton(frame_13);
        key0->setObjectName(QString::fromUtf8("key0"));
        key0->setGeometry(QRect(6, 120, 50, 38));
        key0->setStyleSheet(QString::fromUtf8("background-image: url(:/images/0.png);\n"
"outline-style:none;"));
        key0->setFlat(true);
        btn_Back = new QPushButton(frame_13);
        btn_Back->setObjectName(QString::fromUtf8("btn_Back"));
        btn_Back->setGeometry(QRect(124, 120, 50, 38));
        btn_Back->setStyleSheet(QString::fromUtf8("background-image: url(:/images/back.png);\n"
"outline-style:none;"));
        btn_Back->setFlat(true);
        key2 = new QPushButton(frame_13);
        key2->setObjectName(QString::fromUtf8("key2"));
        key2->setGeometry(QRect(65, 82, 50, 38));
        key2->setStyleSheet(QString::fromUtf8("background-image: url(:/images/2.png);\n"
"outline-style:none;"));
        key2->setFlat(true);
        key8 = new QPushButton(frame_13);
        key8->setObjectName(QString::fromUtf8("key8"));
        key8->setGeometry(QRect(65, 6, 50, 38));
        key8->setStyleSheet(QString::fromUtf8("background-image: url(:/images/8.png);\n"
"outline-style:none;"));
        key8->setFlat(true);
        key3 = new QPushButton(frame_13);
        key3->setObjectName(QString::fromUtf8("key3"));
        key3->setGeometry(QRect(6, 82, 50, 38));
        key3->setStyleSheet(QString::fromUtf8("background-image: url(:/images/3.png);\n"
"outline-style:none;"));
        key3->setFlat(true);
        key1 = new QPushButton(frame_13);
        key1->setObjectName(QString::fromUtf8("key1"));
        key1->setGeometry(QRect(124, 82, 50, 38));
        key1->setStyleSheet(QString::fromUtf8("background-image: url(:/images/1.png);\n"
"outline-style:none;"));
        key1->setFlat(true);
        key9 = new QPushButton(frame_13);
        key9->setObjectName(QString::fromUtf8("key9"));
        key9->setGeometry(QRect(6, 6, 50, 38));
        key9->setStyleSheet(QString::fromUtf8("background-image: url(:/images/9.png);\n"
"outline-style:none;"));
        key9->setFlat(true);
        key7 = new QPushButton(frame_13);
        key7->setObjectName(QString::fromUtf8("key7"));
        key7->setGeometry(QRect(134, 6, 50, 38));
        key7->setStyleSheet(QString::fromUtf8("background-image: url(:/images/7.png);\n"
"outline-style:none;"));
        key7->setFlat(true);
        key5 = new QPushButton(frame_13);
        key5->setObjectName(QString::fromUtf8("key5"));
        key5->setGeometry(QRect(65, 44, 50, 38));
        key5->setStyleSheet(QString::fromUtf8("background-image: url(:/images/5.png);\n"
"outline-style:none;"));
        key5->setFlat(true);
        style = new QLabel(frame_12);
        style->setObjectName(QString::fromUtf8("style"));
        style->setGeometry(QRect(14, 68, 16, 16));
        style->setStyleSheet(QString::fromUtf8("background-image: url(:/images/t2.png);"));
        weizhi = new QLabel(frame_12);
        weizhi->setObjectName(QString::fromUtf8("weizhi"));
        weizhi->setGeometry(QRect(14, 35, 16, 16));
        weizhi->setStyleSheet(QString::fromUtf8("background-image: url(:/images/t1.png);"));
        state_b = new QLabel(frame_12);
        state_b->setObjectName(QString::fromUtf8("state_b"));
        state_b->setGeometry(QRect(32, 98, 40, 25));
        state = new QLabel(frame_12);
        state->setObjectName(QString::fromUtf8("state"));
        state->setGeometry(QRect(14, 103, 16, 16));
        state->setStyleSheet(QString::fromUtf8("background-image: url(:/images/t3.png);"));
        style_value_3 = new QLabel(frame_12);
        style_value_3->setObjectName(QString::fromUtf8("style_value_3"));
        style_value_3->setGeometry(QRect(80, 63, 90, 25));
        state_value = new QLabel(frame_12);
        state_value->setObjectName(QString::fromUtf8("state_value"));
        state_value->setGeometry(QRect(80, 98, 90, 25));
        weizhi_b = new QLabel(frame_12);
        weizhi_b->setObjectName(QString::fromUtf8("weizhi_b"));
        weizhi_b->setGeometry(QRect(32, 30, 40, 25));
        weizhi_value = new QLabel(frame_12);
        weizhi_value->setObjectName(QString::fromUtf8("weizhi_value"));
        weizhi_value->setGeometry(QRect(80, 30, 90, 25));
        style_b = new QLabel(frame_12);
        style_b->setObjectName(QString::fromUtf8("style_b"));
        style_b->setGeometry(QRect(32, 63, 40, 25));
        state_sim = new QLabel(frame_12);
        state_sim->setObjectName(QString::fromUtf8("state_sim"));
        state_sim->setGeometry(QRect(79, 130, 91, 25));
        state_b_sim = new QLabel(frame_12);
        state_b_sim->setObjectName(QString::fromUtf8("state_b_sim"));
        state_b_sim->setGeometry(QRect(9, 130, 81, 25));
        state_b_sim_2 = new QLabel(frame_12);
        state_b_sim_2->setObjectName(QString::fromUtf8("state_b_sim_2"));
        state_b_sim_2->setGeometry(QRect(9, 160, 71, 25));
        send_msg = new QLabel(frame_12);
        send_msg->setObjectName(QString::fromUtf8("send_msg"));
        send_msg->setGeometry(QRect(80, 160, 111, 25));

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "MainWidget", 0, QApplication::UnicodeUTF8));
        pushButton_light->setText(QApplication::translate("MainWidget", "\347\224\265\347\201\257", 0, QApplication::UnicodeUTF8));
        label_temp->setText(QApplication::translate("MainWidget", "\346\270\251\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        label_temp_value->setText(QString());
        label_hum->setText(QApplication::translate("MainWidget", "\346\271\277\345\272\246\357\274\232", 0, QApplication::UnicodeUTF8));
        label_hum_value->setText(QString());
        label_temp_value_2->setText(QApplication::translate("MainWidget", "\342\204\203", 0, QApplication::UnicodeUTF8));
        label_hum_value_2->setText(QApplication::translate("MainWidget", "%", 0, QApplication::UnicodeUTF8));
        label_warn->setText(QApplication::translate("MainWidget", "  \350\255\246\346\212\245", 0, QApplication::UnicodeUTF8));
        number_value->setText(QString());
        label->setText(QString());
#ifndef QT_NO_ACCESSIBILITY
        Steln->setAccessibleName(QApplication::translate("MainWidget", "0x41", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        Steln->setText(QApplication::translate("MainWidget", "                  *", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        key6->setAccessibleName(QApplication::translate("MainWidget", "0x36", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        key6->setText(QApplication::translate("MainWidget", "                       6", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        key4->setAccessibleName(QApplication::translate("MainWidget", "0x34", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        key4->setText(QApplication::translate("MainWidget", "                 4", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        key0->setAccessibleName(QApplication::translate("MainWidget", "0x30", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        key0->setText(QApplication::translate("MainWidget", "                0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        btn_Back->setAccessibleName(QApplication::translate("MainWidget", "0x40", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        btn_Back->setText(QApplication::translate("MainWidget", "                -", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        key2->setAccessibleName(QApplication::translate("MainWidget", "0x32", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        key2->setText(QApplication::translate("MainWidget", "                   2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        key8->setAccessibleName(QApplication::translate("MainWidget", "0x38", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        key8->setText(QApplication::translate("MainWidget", "                      8", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        key3->setAccessibleName(QApplication::translate("MainWidget", "0x33", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        key3->setText(QApplication::translate("MainWidget", "                  3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        key1->setAccessibleName(QApplication::translate("MainWidget", "0x31", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        key1->setText(QApplication::translate("MainWidget", "                1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        key9->setAccessibleName(QApplication::translate("MainWidget", "0x39", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        key9->setText(QApplication::translate("MainWidget", "           9", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        key7->setAccessibleName(QApplication::translate("MainWidget", "0x37", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        key7->setText(QApplication::translate("MainWidget", "                     7", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        key5->setAccessibleName(QApplication::translate("MainWidget", "0x35", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY
        key5->setText(QApplication::translate("MainWidget", "                     5", 0, QApplication::UnicodeUTF8));
        style->setText(QString());
        weizhi->setText(QString());
        state_b->setText(QApplication::translate("MainWidget", "\347\212\266\346\200\201:", 0, QApplication::UnicodeUTF8));
        state->setText(QString());
        style_value_3->setText(QString());
        state_value->setText(QString());
        weizhi_b->setText(QApplication::translate("MainWidget", "\344\275\215\347\275\256:", 0, QApplication::UnicodeUTF8));
        weizhi_value->setText(QString());
        style_b->setText(QApplication::translate("MainWidget", "\347\261\273\345\236\213:", 0, QApplication::UnicodeUTF8));
        state_sim->setText(QApplication::translate("MainWidget", "not initialed", 0, QApplication::UnicodeUTF8));
        state_b_sim->setText(QApplication::translate("MainWidget", "SIM\347\212\266\346\200\201:", 0, QApplication::UnicodeUTF8));
        state_b_sim_2->setText(QApplication::translate("MainWidget", "\345\217\221\351\200\201\347\212\266\346\200\201:", 0, QApplication::UnicodeUTF8));
        send_msg->setText(QApplication::translate("MainWidget", "Not send!", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
