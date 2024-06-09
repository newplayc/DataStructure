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

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    int FontSize=arg1.toInt();
    QFont myFont=ui->textEdit->currentFont();
    myFont.setPointSize(FontSize);
    ui->textEdit->setCurrentFont(myFont);
}

void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    QFont myFont=ui->textEdit->currentFont();
    myFont.setCapitalization(f.capitalization());
    myFont.setFamily(f.family());
    ui->textEdit->setCurrentFont(myFont);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->plainTextEdit_2->appendPlainText("size is:"+ui->comboBox->currentText()+"\n");
    ui->plainTextEdit_2->appendPlainText("font is:"+ui->fontComboBox->currentText()+"\n");
    ui->plainTextEdit_2->appendPlainText("lineEdit is:"+ui->lineEdit->text()+"\n");
    ui->plainTextEdit_2->appendPlainText("SpinBox is:"+tr("%1").arg(ui->spinBox->value())+"\n");
    ui->plainTextEdit_2->appendPlainText("doubleSpinBox is:"+tr("%1").arg(ui->doubleSpinBox->value())+"\n");
    QDateTime myDateTime=ui->dateTimeEdit->dateTime();
    ui->plainTextEdit_2->appendPlainText("date and time are:"+myDateTime.toString("yyyy-MM-dd hh:mm:ss")+"\n");
}


