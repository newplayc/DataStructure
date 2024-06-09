#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "signalandslot.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int x;
    signalandslot a,b;
private slots:

    void on_spinBox_valueChanged(const QString &arg1);

    void on_actionAaa_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
