#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myPushButton=new QPushButton(QIcon(":/stop.png")," &My PushButton",ui->centralWidget);
    myPushButton->setGeometry(QRect(270,280,151,31));
    myPushButton->setShortcut(Qt::Key_M);//快捷键为：Alt+M
            myPushButton->show();
    connect(myPushButton,SIGNAL(clicked()),this,SLOT(on_myPushButton_clicked()));
    ui->buttonGroup->setId(ui->radioButton,0);
    ui->buttonGroup->setId(ui->radioButton_2,1);
    ui->buttonGroup->setId(ui->radioButton_3,2);
    ui->radioButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->statusBar->showMessage(tr("You clicked :")+ui->pushButton->text());
}

void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    ui->statusBar->showMessage(tr("You clicked :")+button->text());
}

void MainWindow::on_myPushButton_clicked()
{
    ui->statusBar->showMessage(tr("You clicked:")+myPushButton->text());
    int a=ui->buttonGroup->checkedId();
    switch(a)
    {
        case 0:
                  QMessageBox::information(this,"RadioButton", "radioButton is selected");
                  break;
        case 1:
                   QMessageBox::information(this,"RadioButton_2", "radioButton_2 is selected");
                  break;
         case 2:
                   QMessageBox::information(this,"RadioButton_3", "radioButton_3 is selected");
                   break;
          default:
                    break;
    }
}
