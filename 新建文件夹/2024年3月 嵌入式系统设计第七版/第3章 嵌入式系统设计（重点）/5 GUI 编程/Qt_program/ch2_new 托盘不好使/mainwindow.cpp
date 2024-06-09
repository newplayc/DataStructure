#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include<QMouseEvent>
#include<QLCDNumber>
#include<QTime>
#include<QSystemTrayIcon>
#include<QIcon>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    aboutAct=new QAction(QIcon(":/logo.png"),tr("&A 关于"),this);
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(about()));

    aboutMenu=menuBar()->addMenu(tr("&A 关于"));
    aboutMenu->addAction(aboutAct);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(aboutAct);

    QTime Current_Time=QTime::currentTime();
    myToolBarTime=new QLCDNumber(ui->mainToolBar);
    myToolBarTime->setDigitCount(15);
    myToolBarTime->display(Current_Time.toString("HH:mm:ss.zzz"));
    ui->mainToolBar->addWidget(myToolBarTime);
    this->startTimer(1000);

    MouseX=new QLabel(ui->statusBar);
    MouseX->setFixedWidth(50);
    MouseX->setIndent(3);

    MouseY=new QLabel(ui->statusBar);
    MouseY->setFixedWidth(50);
    MouseY->setIndent(3);

    ui->statusBar->addWidget(MouseX);
    ui->statusBar->addWidget(MouseY);

    setMouseTracking(true);

    QIcon systemIcon(":/qt-logo.png");
    myTrayIcon=new QSystemTrayIcon(systemIcon,this);
    myTrayIcon->show();
    myTrayIcon->showMessage("提示","单击隐藏，双击显示主窗口");
    myTrayIcon->setContextMenu(ui->menuF);

    connect(myTrayIcon,SIGNAL(activated(QSystemTrayIcon::ActivateionReason)),this,SLOT(QSystemTrayIcon::ActivationReason));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionO_triggered()
{
    QMessageBox::information(this,"消息", "选择了打开菜单项");
    statusBar()->showMessage(tr("选择了打开菜单项"));
}

void MainWindow::on_actionS_triggered()
{
     QMessageBox::information(this,"消息", "选择了保存菜单项");
}

void MainWindow::on_actionE_triggered()
{
    QMessageBox::information(this,"消息", "选择了退出菜单项");
    close();
}

void MainWindow::about()
 {
           QMessageBox::about(this,"消息","选择了关于菜单项");
 }

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::RightButton)
    {
        aboutMenu->popup(event->globalPos());
    }

        if (event->button()==Qt::LeftButton)
        {
           ui->menuF->popup(event->globalPos());
        }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    QTime Current_Time=QTime::currentTime();
    myToolBarTime->display(Current_Time.toString("HH:mm:ss.zzz"));
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    MouseX->setNum(event->x());
    MouseY->setNum(event->y());
}

void MainWindow::activated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::Trigger:
                                                      this->hide();
                                                      break;
        case QSystemTrayIcon::DoubleClick:
                                                  this->showNormal();
                                                  break;
        default:break;
    }
}
