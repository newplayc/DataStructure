#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include<QMouseEvent>
#include<QLCDNumber>
#include<QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    aboutAct=new QAction(QIcon(":/logo.png"),tr("&About"),this);
    aboutAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(about()));

    aboutMenu=menuBar()->addMenu(tr("&About"));
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Open_triggered()
{
    QMessageBox::information(this,"message", "select to open");
    statusBar()->showMessage(tr("select to open the menu"));
}

void MainWindow::on_action_Save_triggered()
{
     QMessageBox::information(this,"message", "select to save");
}

void MainWindow::on_action_Exit_triggered()
{
    QMessageBox::information(this,"message", "select to exit");
    close();
}

void MainWindow::about()
 {
           QMessageBox::about(this,"message","select to about");
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


