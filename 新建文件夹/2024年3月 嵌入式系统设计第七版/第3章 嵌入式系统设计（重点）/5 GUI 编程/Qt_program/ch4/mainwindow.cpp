#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QString>
#include <QChar>
#include<QMouseEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->modifiers())
    {
        case Qt::ShiftModifier:
                   ui->statusBar->showMessage(tr("Key released : key=%1 modifiers=SHIFT").arg(QChar(event->key())),3000);
                   break;
        case Qt::ControlModifier:
                   ui->statusBar->showMessage(tr("Key released : key=%1 modifiers=CTRL").arg(QChar(event->key())),3000);
                   break;
         case Qt::AltModifier:
                   ui->statusBar->showMessage(tr("Key released : key=%1 modifiers=ALT").arg(QChar(event->key())),3000);
                   break;
         default:
                   ui->statusBar->showMessage(tr("Key released : key=%1 modifiers=Other").arg(QChar(event->key())),3000);
                   break;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->modifiers())
    {
        case Qt::ShiftModifier:
                   ui->statusBar->showMessage(tr("Key pressed : key=%1 modifiers=SHIFT").arg(QChar(event->key())),3000);
                   break;
        case Qt::ControlModifier:
                   ui->statusBar->showMessage(tr("Key pressed : key=%1 modifiers=CTRL").arg(QChar(event->key())),3000);
                   break;
         case Qt::AltModifier:
                   ui->statusBar->showMessage(tr("Key pressed : key=%1 modifiers=ALT").arg(QChar(event->key())),3000);
                   break;
         default:
                   ui->statusBar->showMessage(tr("Key pressed : key=%1 modifiers=Other").arg(QChar(event->key())),3000);
                   break;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    MouseX->setNum(event->x());
    MouseY->setNum(event->y());
}
