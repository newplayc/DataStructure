#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setName(QString InputName)
{
    m_Name=InputName;
    ui->lineEdit->setText(m_Name);
    QPixmap m_photo(":/"+m_Name+".png");
    ui->label_4->setPixmap(m_photo);
}

void Dialog::setTel(QString InputTel)
{
    m_Tel=InputTel;
    ui->lineEdit_3->setText(m_Tel);
}

void Dialog::setDept(QString InputDept)
{
    m_Dept=InputDept;
    ui->lineEdit_2->setText(m_Dept);
}

void Dialog::on_pushButton_clicked()
{
    m_Name=ui->lineEdit->text();
    m_Tel=ui->lineEdit_3->text();
    m_Dept=ui->lineEdit_2->text();
    accept();
}

void Dialog::on_pushButton_2_clicked()
{
    reject();
}

