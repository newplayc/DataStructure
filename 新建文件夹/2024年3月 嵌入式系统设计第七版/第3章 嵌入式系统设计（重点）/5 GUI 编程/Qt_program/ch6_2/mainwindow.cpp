#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    Dialog m_Dlg;
    m_Dlg.setName(tr("Marry"));
    m_Dlg.setDept(tr("second"));
    m_Dlg.setTel(tr("01012345678"));
    m_Dlg.exec();
    ui->statusBar->showMessage(tr("name:%1 dept:%2 tel:%3").arg(m_Dlg.m_Name).arg(m_Dlg.m_Dept).arg(m_Dlg.m_Tel));
}
