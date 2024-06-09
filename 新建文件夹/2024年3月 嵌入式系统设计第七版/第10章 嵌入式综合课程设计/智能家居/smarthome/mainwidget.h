#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include <QList>
#include <QPushButton>
#include <QMessageBox>
#include "zigbeetopo.h"
#include "mylabelhtu.h"
#include"cliect_td.h"

namespace Ui {
    class MainWidget;
}
typedef signed   char   int8;
typedef unsigned char   uint8;
typedef unsigned char   byte;
typedef signed   short  int16;
typedef unsigned short  uint16;

typedef signed   long   int32;
typedef unsigned long   uint32;
#define BREAK_UINT32( var, ByteNum ) \
          (byte)((uint32)(((var) >>((ByteNum) * 8)) & 0x00FF))

class MainWidget : public QWidget {
    Q_OBJECT
public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void initPad();
    void SaveTelNum();


    Ui::MainWidget *ui;
    char *phone_num,*phone_data;  
    int calc_sth11(float *p_humidity ,float *p_temperature);
    int getsht11(char *rData, char *&pTemp, char *&pHumi);
        MyLabelHtu *smog_label,*int_label,*irda_label;
    ZigbeeTopo *zb_thread;
    Cliect *cliect_thread;

    int int_flag,smog_flag,irda_flag,light_state;
    int Sim_state;
    QSignalMapper *signalMapper;
    QList<QPushButton *> allNumButtons;
signals:
    void Irda_StateChanged_1(void);//duishe
    void Smog_StateChanged_1(void);//
    void Int_StateChanged_1(void);//door
    void Irda_StateChanged_0(void);//duishe
    void Smog_StateChanged_0(void);//
    void Int_StateChanged_0(void);//door

public slots:
    void on_btn_Back_clicked();
    void onBtn_clicked(int btn);

    void pushButton_light_clicked();
    void gprs_sendMsg(int sensor);
   
    void Smog_change_1();
    void Int_change_1();
    void Irda_change_1();
    void Smog_change_0();
    void Int_change_0();
    void Irda_change_0();
    void int_show();
    void smog_show();
    void irda_show();
    void show_TempHum(unsigned long x);

    void Set_Sim(int sim);
    void Set_Send(int sim);
  
};

#endif // MAINWIDGET_H
