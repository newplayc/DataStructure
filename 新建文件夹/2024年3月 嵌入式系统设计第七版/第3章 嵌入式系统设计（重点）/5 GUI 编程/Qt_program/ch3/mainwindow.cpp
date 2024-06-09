#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signalandslot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{  x=0;
    ui->setupUi(this);
    //建立a和b的 连接
    connect(&a,SIGNAL(DataChanged(int)),&b,SLOT(SetData(int)));
    //在状态条输出对象a和b属性Data的初始值
    ui->statusBar->showMessage(tr("a.Data=%1 b.Data=%2").arg(a.Data).arg(b.Data));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBox_valueChanged(const QString &arg1)
{
     ui->statusBar->showMessage(arg1);
}


void MainWindow::on_actionAaa_triggered()
{   x++;
    //在菜单响应中,改变a的Data值
    a.SetData(x);
    //在状态条输出对象a和b属性Data的当前值
    ui->statusBar->showMessage(tr("a.Data=%1 b.Data=%2").arg(a.Data).arg(b.Data));
}
