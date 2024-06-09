/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created: Sun Apr 2 05:44:35 2017
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QTextEdit *textEdit;
    QPushButton *pushbutton1;
    QPushButton *pushbutton2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(400, 300);
        textEdit = new QTextEdit(Form);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(30, 50, 171, 201));
        pushbutton1 = new QPushButton(Form);
        pushbutton1->setObjectName(QString::fromUtf8("pushbutton1"));
        pushbutton1->setGeometry(QRect(260, 80, 85, 27));
        pushbutton2 = new QPushButton(Form);
        pushbutton2->setObjectName(QString::fromUtf8("pushbutton2"));
        pushbutton2->setGeometry(QRect(260, 170, 85, 27));

        retranslateUi(Form);
        QObject::connect(pushbutton1, SIGNAL(clicked()), textEdit, SLOT(clear()));
        QObject::connect(pushbutton2, SIGNAL(clicked()), Form, SLOT(close()));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt;\">this is an example for QT-X11</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        pushbutton1->setText(QApplication::translate("Form", "show", 0, QApplication::UnicodeUTF8));
        pushbutton2->setText(QApplication::translate("Form", "exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
