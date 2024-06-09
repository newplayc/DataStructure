#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLCDNumber>
#include<QLabel>
#include<QSystemTrayIcon>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QLCDNumber *myToolBarTime;
    void timerEvent(QTimerEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QSystemTrayIcon *myTrayIcon;

    QLabel *MouseX;
    QLabel *MouseY;

private slots:
    void on_actionO_triggered();
    void on_actionS_triggered();
    void on_actionE_triggered();
    void about();
    void mousePressEvent(QMouseEvent *event);
public slots:
    void activated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;
    QMenu *aboutMenu;
    QAction *aboutAct;
};

#endif // MAINWINDOW_H
