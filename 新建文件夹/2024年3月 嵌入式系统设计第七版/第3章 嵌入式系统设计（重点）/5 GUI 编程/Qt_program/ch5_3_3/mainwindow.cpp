#include "mainwindow.h"
#include "ui_mainwindow.h"

 #include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();
    this->setCentralWidget(ui->graphicsView);
    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Open_triggered()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open Files"),"",tr("Image Files (*.png *.jpg *.h *.bmp)"));

    QPixmap myImage,myImage2;
    myImage.load(fileName);
    myImage2=myImage.scaled(ui->graphicsView->width(),ui->graphicsView->height(),Qt::KeepAspectRatio, Qt::FastTransformation);

    scene.clear();
    scene.addPixmap(myImage2);

}

void MainWindow::on_action_Close_triggered()
{
    close();
}
