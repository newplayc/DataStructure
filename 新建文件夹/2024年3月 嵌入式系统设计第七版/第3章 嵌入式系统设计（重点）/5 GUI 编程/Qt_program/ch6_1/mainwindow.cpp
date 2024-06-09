#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include<QFileDialog>
#include<QFontDialog>
#include<QInputDialog>
#include<QMessageBox>
#include<QPageSetupDialog>
#include<QPrinter>
#include<QPrintDialog>
#include<QPainter>
#include<QPrintPreviewDialog>
#include<QProgressDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QColor m_Color=QColorDialog::getColor(Qt::white,this,tr("color dialog"));
    ui->statusBar->showMessage(tr("You select color:red:%1 green:%2 blue:%3").arg(m_Color.red()).arg(m_Color.green()).arg(m_Color.blue()));
}

void MainWindow::on_pushButton_2_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("file open dialog"),tr(":/"),tr("*.*"));
    ui->statusBar->showMessage(tr("You select file name : ")+filename);
}

void MainWindow::on_pushButton_3_clicked()
{
    bool ok=true;
    QFont font=QFontDialog::getFont(&ok,this->font());
    ui->statusBar->showMessage(tr("You select font:%1").arg(font.family()));
}

void MainWindow::on_pushButton_4_clicked()
{
    bool ok=true;
    int inputValue=QInputDialog::getInt(this,tr("input integer"),tr("%"),25,0,100,1,&ok);
    ui->statusBar->showMessage(tr("You input:%1").arg(inputValue));
}

void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox::about(this,tr("About messageBox"),tr("****version 1.0"));
}

void MainWindow::on_pushButton_6_clicked()
{
    QPageSetupDialog m_pageSetupDlg;
    m_pageSetupDlg.exec();
    QPrinter *m_printer=m_pageSetupDlg.printer();
    if(m_printer->paperSize()==QPrinter::A4)
        ui->statusBar->showMessage(tr("You select A4"));
}

void MainWindow::on_pushButton_7_clicked()
{
    QPrintDialog m_PrintDlg;
    m_PrintDlg.exec();
    QPrinter *m_printer=m_PrintDlg.printer();
    QPainter painter;
    painter.begin(m_printer);
    for(int i=0;i<10;i++)
        painter.drawText(100,100+30*i,tr("print %1 line,").arg(i));
    painter.end();
}

void MainWindow::on_pushButton_8_clicked()
{
    QPrintPreviewDialog m_PrintPreviewDlg;
    connect(&m_PrintPreviewDlg,SIGNAL(paintRequested(QPrinter*)),SLOT(on_Print_page(QPrinter *)));
    m_PrintPreviewDlg.exec();
}

void MainWindow::on_Print_page(QPrinter * printer)
{
    QPainter painter;
    QFont printFont=this->font();
    printFont.setPointSize(30);
    painter.begin(printer);
    painter.setFont(printFont);

    for(int i=0;i<10;i++)
        painter.drawText(100,100+50*i,tr("print %1 line.").arg(i));

    painter.end();
}

void MainWindow::on_pushButton_9_clicked()
{
    QProgressDialog * progress=new QProgressDialog(tr("copying file ..."),tr("ok"),0,100,this);
    progress->setWindowTitle(tr("progress dialog"));
    progress->setWindowModality(Qt::WindowModal);
    for(int i=0;i<100;i++)
    {
       progress->setValue(i);
       progress->show();
       usleep(20000);
    }
}
