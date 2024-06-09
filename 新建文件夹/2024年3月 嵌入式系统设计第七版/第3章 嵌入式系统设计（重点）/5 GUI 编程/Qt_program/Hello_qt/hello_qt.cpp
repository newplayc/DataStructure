#include <QDesktopWidget>
#include <QApplication>
#include <QLabel>
int main(int argc,char *argv[])
 {
    QApplication app(argc,argv);
    QLabel *label=new QLabel("Hello Qt!");
    label->show();
    //设置Label窗口居中显示
    int x=(QApplication::desktop()->width()-label->width())/2;
    int y=(QApplication::desktop()->height()-label->height())/2;
    label->setGeometry(x,y,label->width(),label->height());

    return app.exec(); 
 }
