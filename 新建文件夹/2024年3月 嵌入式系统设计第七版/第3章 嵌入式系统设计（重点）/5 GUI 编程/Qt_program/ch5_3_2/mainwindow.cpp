#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
 #include <QFileDialog>
 #include <QtCore/QTextStream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textBrowser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Open_triggered()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open Files"),"",tr("Files(*.txt *.cpp *.h *.html *.htm)"));
    QFile myFile(fileName);
    if(!myFile.open(QIODevice::ReadOnly|QIODevice::Text))
        return;

    QTextStream in(&myFile);
    QString m_Text=in.readAll();
    if(fileName.endsWith("htm")||fileName.endsWith("html"))
    {
        ui->textBrowser->setHtml(m_Text);
    }
    else
        ui->textBrowser->setPlainText(m_Text);
    ui->statusBar->showMessage("file name:"+fileName);
}

void MainWindow::on_action_Close_triggered()
{
    close();
}
