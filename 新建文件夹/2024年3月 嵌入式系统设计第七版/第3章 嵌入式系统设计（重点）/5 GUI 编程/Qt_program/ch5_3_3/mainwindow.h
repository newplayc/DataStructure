#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGraphicsScene scene;
private slots:
    void on_action_Open_triggered();

    void on_action_Close_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
