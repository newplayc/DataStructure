#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLCDNumber>
#include<QLabel>

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

    QLabel *MouseX;
    QLabel *MouseY;

private slots:
    void on_action_Open_triggered();
    void on_action_Save_triggered();
    void on_action_Exit_triggered();
    void about();
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    QMenu *aboutMenu;
    QAction *aboutAct;
};

#endif // MAINWINDOW_H
