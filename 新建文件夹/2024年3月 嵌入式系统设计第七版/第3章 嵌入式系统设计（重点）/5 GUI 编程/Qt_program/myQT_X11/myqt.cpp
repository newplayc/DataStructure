#include "myqt.h" 
MyDlg::MyDlg() 
{ 
   ui.setupUi(this); 
   QObject::connect(ui.pushbutton1, SIGNAL(clicked()), this, SLOT(ShowInfo()));
   QObject::connect(ui.pushbutton2, SIGNAL(clicked()), this, SLOT(close())); 
} 

void MyDlg::ShowInfo() 
{ 
   ui.textEdit->setHtml(QApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n" "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n" "p, li { white-space: pre-wrap; }\n" "</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n" "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0;text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; color:#55aaff;\">Welcome to UP-TECH</span></p></body></html>", 0, QApplication::UnicodeUTF8));
 }
