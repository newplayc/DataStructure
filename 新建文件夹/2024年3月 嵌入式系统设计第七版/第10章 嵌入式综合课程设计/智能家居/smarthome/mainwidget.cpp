#include <QDebug>
#include <QKeyEvent>
#include <QFile>
#include <unistd.h>
#include <math.h>
#include "api.h"
#include "mainwidget.h"
#include "ui_mainwidget.h"
int gprs_fg = 0;
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    //设置主界面背景
    QPalette palette1=this->palette();
    palette1.setBrush(QPalette::Window,QBrush(QPixmap(":/images/up_wsn_bg2.jpg")));
    this->setPalette(palette1);
    this->setAutoFillBackground(true);
//设置智能家居界面背景
    palette1.setBrush(QPalette::Window,QBrush(QPixmap(":/images/05.jpg")));
    ui->frame_10->setPalette(palette1);
    ui->frame_10->setAutoFillBackground(true);
//设置报警电话号码及内容的长度
    phone_data=(char*)malloc(39);
    phone_num=(char *)malloc(ui->number_value->text().length());

    {//for htu sensor 设置门磁、红外对射、烟雾传感器及电灯图标
        ui->pushButton_light->setStyleSheet("QPushButton{background-image: url(:/images/node_light.png);}"
        "QPushButton{background-color: rgba(255, 255, 255, 0);}"
        "QPushButton:hover{background-image: url(:/images/node_light.png);}"
        "QPushButton:pressed{background-image: url(:/images/node_light.png);}");
        ui->pushButton_light->setFlat(true);

        QPalette palette2=this->palette();
        palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning.png")));
        palette2.setColor(QPalette::WindowText,Qt::green);
        ui->label_warn->setPalette(palette2);
        ui->label_warn->setAutoFillBackground(true);

        int_label=new MyLabelHtu(ui->frame_11);
        int_label->setGeometry(QRect(260,350, 51, 51));
        int_label->setText(QString::fromUtf8("  门磁"));
        palette1.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_dir.png")));
        palette1.setColor(QPalette::WindowText,Qt::red);
        int_label->setPalette(palette1);
        int_label->setAutoFillBackground(true);

        smog_label=new MyLabelHtu(ui->frame_11);
        smog_label->setGeometry(QRect(500,280, 51, 51));
        smog_label->setText(QString::fromUtf8("  烟雾"));
        palette1.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_smog.png")));
        palette1.setColor(QPalette::WindowText,Qt::red);
        smog_label->setPalette(palette1);
        smog_label->setAutoFillBackground(true);

        irda_label=new MyLabelHtu(ui->frame_11);
        irda_label->setGeometry(QRect(20,250, 51, 51));
        irda_label->setText(QString::fromUtf8("  对射"));
        palette1.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_magt.png")));
        palette1.setColor(QPalette::WindowText,Qt::red);
        irda_label->setPalette(palette1);
        irda_label->setAutoFillBackground(true);

        int_flag=0;
        smog_flag=0;
        irda_flag=0;
        connect(int_label,SIGNAL(clicked()),this,SLOT(int_show()));
        connect(smog_label,SIGNAL(clicked()),this,SLOT(smog_show()));
        connect(irda_label,SIGNAL(clicked()),this,SLOT(irda_show()));
    }



    char *ipaddr="192.168.12.248";//连接本地服务器，端口号是7838
    int port=7838;
    cliect_thread = new Cliect();
    cliect_thread->GetConnect(ipaddr,port);
//建立相关的信号槽
    connect(ui->pushButton_light,SIGNAL(clicked()),this,SLOT(pushButton_light_clicked()));//开关灯
    connect(cliect_thread,SIGNAL(sendMsgsignal(int )),this,SLOT(gprs_sendMsg(int)));//发送短信报警
    connect(cliect_thread,SIGNAL(Int_StateChanged_1()),this,SLOT(Int_change_1()));//门磁传感器异常
    connect(cliect_thread,SIGNAL(Irda_StateChanged_1()),this,SLOT(Irda_change_1()));//红外对射传感器异常
    connect(cliect_thread,SIGNAL(Smog_StateChanged_1()),this,SLOT(Smog_change_1()));//烟雾传感器异常
    connect(cliect_thread,SIGNAL(Int_StateChanged_0()),this,SLOT(Int_change_0()));//门磁传感器正常
    connect(cliect_thread,SIGNAL(Irda_StateChanged_0()),this,SLOT(Irda_change_0()));//红外对射传感器正常
    connect(cliect_thread,SIGNAL(Smog_StateChanged_0()),this,SLOT(Smog_change_0()));//烟雾传感器正常
    connect(cliect_thread,SIGNAL(sendTempHum(unsigned long )),this,SLOT(show_TempHum(unsigned long )));//显示温湿度
    connect(cliect_thread,SIGNAL(Sim(int )),this,SLOT(Set_Sim(int)));//
    connect(cliect_thread,SIGNAL(Send(int)),this,SLOT(Set_Send(int)));

    connect(this,SIGNAL(Int_StateChanged_1()),this,SLOT(Int_change_1()));
    connect(this,SIGNAL(Irda_StateChanged_1()),this,SLOT(Irda_change_1()));
    connect(this,SIGNAL(Smog_StateChanged_1()),this,SLOT(Smog_change_1()));
    connect(this,SIGNAL(Int_StateChanged_0()),this,SLOT(Int_change_0()));
    connect(this,SIGNAL(Irda_StateChanged_0()),this,SLOT(Irda_change_0()));
    connect(this,SIGNAL(Smog_StateChanged_0()),this,SLOT(Smog_change_0()));

    cliect_thread->start();
    zb_thread = new ZigbeeTopo();

    light_state=0;
    Sim_state=0;
    ui->state_sim->setText(QString::fromUtf8("未初始化"));
    cliect_thread->Api_Cliect_GetGPRSSignal();
    initPad();///初始化界面中的软键盘

}
MainWidget::~MainWidget()
{
  
}
	
void MainWidget::show_TempHum(unsigned long x){
	
		char temp[5],humi[5],data[4];
		char *pTemp,*pHumi;
		pTemp = temp;
		pHumi = humi;
		int return_t=0;
		data[0]=BREAK_UINT32( x,3 );
		data[1]=BREAK_UINT32( x,2 );
		data[2]=BREAK_UINT32( x,1 );
		data[3]=BREAK_UINT32( x,0 );
		return_t=getsht11(data, pTemp, pHumi);
    if(return_t){
			ui->label_temp_value->setText(pTemp);
      ui->label_hum_value->setText(pHumi);
      ui->label_temp_value->update();
      ui->label_hum_value->update();
    }
}


void MainWidget::int_show(){
        if(int_flag)
                {
                        QPalette palette2=this->palette();
                        palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning_selected.png")));
                        ui->label_warn->setPalette(palette2);
                        ui->label_warn->setAutoFillBackground(true);

                        ui->weizhi_value->setText(QString::fromUtf8("门口"));
                        ui->style_value_3->setText(QString::fromUtf8("门磁传感器"));
                        ui->state_value->setText(QString::fromUtf8("报警"));


                        ui->label_warn->update();
                        ui->weizhi_value->update();
                        ui->style_value_3->update();
                        ui->state_value->update();
                        }
                else
                        {
                                QPalette palette2=this->palette();
                                palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning.png")));
                                ui->label_warn->setPalette(palette2);
                                ui->label_warn->setAutoFillBackground(true);

                                ui->weizhi_value->setText(QString::fromUtf8("门口"));
                                ui->style_value_3->setText(QString::fromUtf8("门磁传感器"));
                                ui->state_value->setText(QString::fromUtf8("正常"));


                                ui->label_warn->update();
                                ui->weizhi_value->update();
                                ui->style_value_3->update();
                                ui->state_value->update();
                                }
}
void MainWidget::smog_show(){
        if(smog_flag)
                {
                        ui->weizhi_value->setText(QString::fromUtf8("厨房"));
                        ui->style_value_3->setText(QString::fromUtf8("烟雾传感器"));
                        ui->state_value->setText(QString::fromUtf8("报警"));

                        QPalette palette2=this->palette();
                        palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning_selected.png")));
                        ui->label_warn->setPalette(palette2);
                        ui->label_warn->setAutoFillBackground(true);


                        ui->label_warn->update();
                        ui->weizhi_value->update();
                        ui->style_value_3->update();
                        ui->state_value->update();
                        }
                else
                        {
                                ui->weizhi_value->setText(QString::fromUtf8("厨房"));
                                ui->style_value_3->setText(QString::fromUtf8("烟雾传感器"));
                                ui->state_value->setText(QString::fromUtf8("正常"));

                                QPalette palette2=this->palette();
                                palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning.png")));
                                ui->label_warn->setPalette(palette2);
                                ui->label_warn->setAutoFillBackground(true);


                                ui->label_warn->update();
                                ui->weizhi_value->update();
                                ui->style_value_3->update();
                                ui->state_value->update();
                                }
}
void MainWidget::irda_show(){
        if(irda_flag)
                {
                        QPalette palette2=this->palette();
                        palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning_selected.png")));
                        ui->label_warn->setPalette(palette2);
                        ui->label_warn->setAutoFillBackground(true);

                        ui->weizhi_value->setText(QString::fromUtf8("阳台"));
                        ui->style_value_3->setText(QString::fromUtf8("红外对射传感器"));
                        ui->state_value->setText(QString::fromUtf8("报警"));



                        ui->label_warn->update();
                        ui->weizhi_value->update();
                        ui->style_value_3->update();
                        ui->state_value->update();
                        }
                else
                        {
                                QPalette palette2=this->palette();
                                palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning.png")));
                                ui->label_warn->setPalette(palette2);
                                ui->label_warn->setAutoFillBackground(true);

                                ui->weizhi_value->setText(QString::fromUtf8("阳台"));
                                ui->style_value_3->setText(QString::fromUtf8("红外对射传感器"));
                                ui->state_value->setText(QString::fromUtf8("正常"));



                                ui->label_warn->update();
                                ui->weizhi_value->update();
                                ui->style_value_3->update();
                                ui->state_value->update();
                                }
}
void MainWidget::Int_change_1(){
        int_flag=1;
        //printf("-------------------------------Int_change 1----------------------------------\n");

        QPalette palette1=this->palette();
        palette1.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_dir_selected.png")));
        palette1.setColor(QPalette::WindowText,Qt::red);
        int_label->setPalette(palette1);
        int_label->setAutoFillBackground(true);

        QPalette palette2=this->palette();
        palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning_selected.png")));
        ui->label_warn->setPalette(palette2);
        ui->label_warn->setAutoFillBackground(true);

        ui->weizhi_value->setText(QString::fromUtf8("门口"));
        ui->style_value_3->setText(QString::fromUtf8("门磁传感器"));
        ui->state_value->setText(QString::fromUtf8("报警"));

        int_label->update();
        ui->label_warn->update();
        ui->weizhi_value->update();
        ui->style_value_3->update();
        ui->state_value->update();
        //Api_Cliect_ClearIntlock();
}
void MainWidget::Smog_change_1(){
        smog_flag=1;

        //printf("-------------------------------Smog_change 1----------------------------------\n");
        QPalette palette1=this->palette();
        palette1.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_smog_selected.png")));
        palette1.setColor(QPalette::WindowText,Qt::red);
        smog_label->setPalette(palette1);
        smog_label->setAutoFillBackground(true);

        ui->weizhi_value->setText(QString::fromUtf8("厨房"));
        ui->style_value_3->setText(QString::fromUtf8("烟雾传感器"));
        ui->state_value->setText(QString::fromUtf8("报警"));

        QPalette palette2=this->palette();
        palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning_selected.png")));
        ui->label_warn->setPalette(palette2);
        ui->label_warn->setAutoFillBackground(true);

        smog_label->update();
        ui->label_warn->update();
        ui->weizhi_value->update();
        ui->style_value_3->update();
        ui->state_value->update();
//Api_Cliect_ClearIntlock();
}
void MainWidget::Irda_change_1(){
        irda_flag=1;
        //printf("-------------------------------Irda_change 1----------------------------------\n");

        QPalette palette1=this->palette();
        palette1.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_magt_selected.png")));
        palette1.setColor(QPalette::WindowText,Qt::red);
        irda_label->setPalette(palette1);
        irda_label->setAutoFillBackground(true);

        QPalette palette2=this->palette();
        palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning_selected.png")));
        ui->label_warn->setPalette(palette2);
        ui->label_warn->setAutoFillBackground(true);

        ui->weizhi_value->setText(QString::fromUtf8("阳台"));
        ui->style_value_3->setText(QString::fromUtf8("红外对射传感器"));
        ui->state_value->setText(QString::fromUtf8("报警"));


        irda_label->update();
        ui->label_warn->update();
        ui->weizhi_value->update();
        ui->style_value_3->update();
        ui->state_value->update();
//Api_Cliect_ClearIntlock();

}

void MainWidget::Int_change_0(){
        int_flag=0;
        printf("Int_change 0\n");
        QPalette palette1=this->palette();
        palette1.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_dir.png")));
        palette1.setColor(QPalette::WindowText,Qt::red);
        int_label->setPalette(palette1);
        int_label->setAutoFillBackground(true);


        QPalette palette2=this->palette();
        palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning.png")));
        ui->label_warn->setPalette(palette2);
        ui->label_warn->setAutoFillBackground(true);

        ui->weizhi_value->setText(QString::fromUtf8("门口"));
        ui->style_value_3->setText(QString::fromUtf8("门磁传感器"));
        ui->state_value->setText(QString::fromUtf8("正常"));

        int_label->update();
        ui->label_warn->update();
        ui->weizhi_value->update();
        ui->style_value_3->update();
        ui->state_value->update();
        //Api_Cliect_ClearIntlock();
        //ui->send_msg->setText("Not send!");

}

void MainWidget::Smog_change_0(){
printf("Smog_change 0\n");
        smog_flag=0;
  QPalette palette1=this->palette();
  palette1.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_smog.png")));
        palette1.setColor(QPalette::WindowText,Qt::red);
  smog_label->setPalette(palette1);
  smog_label->setAutoFillBackground(true);

  QPalette palette2=this->palette();
  palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning.png")));
  ui->label_warn->setPalette(palette2);
  ui->label_warn->setAutoFillBackground(true);

  ui->weizhi_value->setText(QString::fromUtf8("厨房"));
        ui->style_value_3->setText(QString::fromUtf8("烟雾传感器"));
        ui->state_value->setText(QString::fromUtf8("正常"));


        smog_label->update();
        ui->label_warn->update();

        ui->weizhi_value->update();
        ui->style_value_3->update();
        ui->state_value->update();
        //Api_Cliect_ClearIntlock();
        //ui->send_msg->setText("Not send!");
}
void MainWidget::Irda_change_0(){
        printf("Irda_change 0\n");
        irda_flag=0;
  QPalette palette1=this->palette();
  palette1.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_magt.png")));
        palette1.setColor(QPalette::WindowText,Qt::red);
  irda_label->setPalette(palette1);
  irda_label->setAutoFillBackground(true);

  QPalette palette2=this->palette();
  palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning.png")));
  ui->label_warn->setPalette(palette2);
  ui->label_warn->setAutoFillBackground(true);

  ui->weizhi_value->setText(QString::fromUtf8("阳台"));
        ui->style_value_3->setText(QString::fromUtf8("红外对射传感器"));
        ui->state_value->setText(QString::fromUtf8("正常"));

        irda_label->update();
        ui->label_warn->update();

        ui->weizhi_value->update();
        ui->style_value_3->update();
        ui->state_value->update();
        //ui->send_msg->setText("Not send!");
        //Api_Cliect_ClearIntlock();
}
void MainWidget::Set_Sim(int sim)
{
    if(sim==0)
    {
        ui->state_sim->setText(QString::fromUtf8("初始化..."));
        Sim_state=0;
    }
    else if(sim==1)
    {
        ui->state_sim->setText(QString::fromUtf8("初始化成功"));
        Sim_state=1;
    }
}
void MainWidget::Set_Send(int sim)
{
    if(sim==1)
        ui->send_msg->setText(QString::fromUtf8("发送成功"));
                sim=0;
}
void MainWidget::pushButton_light_clicked(){
        NodeInfo *pSensorDesp=pNodeInfo2;
        while(pSensorDesp)
        {
                if(pSensorDesp->devinfo->status)
                if(pSensorDesp->devinfo->sensortype == 0x5)
                break;
                pSensorDesp=pSensorDesp->next;
        }
        //SensorDesp *pSensorDesp=Api_Cliect_GetSensorStatus(ui->saddr_value->text().toInt());
        if(pSensorDesp)
        {

   if(light_state==0)
   {
        cliect_thread->Api_Cliect_SetSensorStatus(pSensorDesp->devinfo->nwkaddr,1);
        ui->pushButton_light->setStyleSheet("QPushButton{background-image: url(:/images/node_light_selected.png);}"
        "QPushButton{background-color: rgba(255, 255, 255, 0);}"
"QPushButton:hover{background-image: url(:/images/node_light_selected.png);}"
"QPushButton:pressed{background-image: url(:/images/node_light_selected.png);}");
                ui->pushButton_light->setFlat(true);


    QPalette palette2=this->palette();
    palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning_selected.png")));

    ui->label_warn->setPalette(palette2);
    ui->label_warn->setAutoFillBackground(true);

    ui->weizhi_value->setText(QString::fromUtf8("客厅"));
                ui->style_value_3->setText(QString::fromUtf8("电灯"));
                ui->state_value->setText(QString::fromUtf8("开灯"));
                ui->pushButton_light->update();
                ui->label_warn->update();
                ui->weizhi_value->update();
                ui->style_value_3->update();
                ui->state_value->update();


  }
        else
                {
                cliect_thread->Api_Cliect_SetSensorStatus(pSensorDesp->devinfo->nwkaddr,0);

                ui->pushButton_light->setStyleSheet("QPushButton{background-image: url(:/images/node_light.png);}"
                "QPushButton{background-color: rgba(255, 255, 255, 0);}"
"QPushButton:hover{background-image: url(:/images/node_light.png);}"
"QPushButton:pressed{background-image: url(:/images/node_light.png);}");
                        ui->pushButton_light->setFlat(true);


      QPalette palette2=this->palette();
      palette2.setBrush(QPalette::Window,QBrush(QPixmap(":/images/node_warning.png")));
      ui->label_warn->setPalette(palette2);
      ui->label_warn->setAutoFillBackground(true);

      ui->weizhi_value->setText(QString::fromUtf8("客厅"));
                        ui->style_value_3->setText(QString::fromUtf8("电灯"));
                        ui->state_value->setText(QString::fromUtf8("关灯"));
                        ui->pushButton_light->update();
                        ui->label_warn->update();
                        ui->weizhi_value->update();
                        ui->style_value_3->update();
                        ui->state_value->update();


        }

    light_state++;
    if(light_state>1)
        light_state=0;
        }

}


int MainWidget::calc_sth11(float *p_humidity ,float *p_temperature)
{
        int ret= 0;

        const float C1=-4.0; // for 12 Bit
        const float C2= 0.0405; // for 12 Bit
        const float C3=-0.0000028; // for 12 Bit
        const float T1=0.01; // for 14 Bit @ 5V
        const float T2=0.00008; // for 14 Bit @ 5V

        float rh=*p_humidity; // rh: Humidity [Ticks] 12 Bit
        float t=*p_temperature; // t: Temperature [Ticks] 14 Bit
        float rh_lin; // rh_lin: Humidity linear
        float rh_true; // rh_true: Temperature compensated humidity
        float t_C; // t_C : Temperature [C]
        t_C=t*0.01 - 42; //calc. Temperature from ticks to [C]
        rh_lin=C3*rh*rh + C2*rh + C1; //calc. Humidity from ticks to [%RH]
        rh_true=(t_C-25)*(T1+T2*rh)+rh_lin; //calc. Temperature compensated humidity [%RH]
        if(rh_true>100)rh_true=100; //cut if the value is outside of
        if(rh_true<0.1)rh_true=0.1; //the physical possible range
        *p_temperature=t_C; //return temperature [C]
        *p_humidity=rh_true; //return humidity[%RH]

        if (t_C>0)return ret = 1;
        return ret;
}

int MainWidget:: getsht11(char *rData, char *&pTemp, char *&pHumi)
{
                int i=0,j=0;
                float temp,humi;
                uint8 tlen,hlen;
                int calcret=0;
                char Temp_t[16];


                i = rData[1] * 256 + rData[0];
                j = rData[3] * 256 + rData[2];


                temp = (float)j;
                humi = (float)i;
                calcret = calc_sth11(&humi,&temp);
                //qDebug("\rtemp=%f\t humi=%f\r",temp,humi);
                if( ((int)temp) > 0  && 0 <= humi <= 100 && calcret) {
                        tlen = sprintf(pTemp, "%d.%d",(int)temp,(int)((temp-(int)temp)*10));
                        hlen = sprintf(pHumi, "%d.%d",(int)humi,(int)((humi-(int)humi)*10));
                        //qDebug("\rTEMP=%s\tHUMI=%s\r",pTemp,pHumi);
                        return 1;
                }
                return 0;

}



/********************************************************************************
// gprs moudle handle
*********************************************************************************/
void MainWidget::initPad()
{
    // use for button pad
    signalMapper = new QSignalMapper(this);
    allNumButtons = ui->frame_13->findChildren<QPushButton *>();
    for (int i=0 ; i<allNumButtons.count() ; i++) {
        connect(allNumButtons.at(i), SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(allNumButtons.at(i), i);
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(onBtn_clicked(int)));
}

void MainWidget::onBtn_clicked(int btn)
{
    QString strKeyId;
    strKeyId = allNumButtons.at(btn)->accessibleName();
    //qDebug() << "num= " << btn << "id= "<<strKeyId;
    bool isOk;
    int keyId = strKeyId.toInt(&isOk, 16);
    //if (strKeyId.isEmpty() || !isOk) {
    //    QMessageBox::information(0,0,"Key Not Found");
    //    return;
    //}
    //qDebug() << "text= " << allNumButtons.at(btn)->text();
    QString ch = allNumButtons.at(btn)->text().trimmed();
    //qDebug() << "text= " << allNumButtons.at(btn)->text().trimmed();
    QKeyEvent keyEvent(QEvent::KeyPress, keyId, Qt::NoModifier, ch, false, 1);
    if(btn !=0 && btn !=4)
    QApplication::sendEvent(ui->number_value, &keyEvent);

    if(btn == 0){
        SaveTelNum();
    }

}
void MainWidget::gprs_sendMsg(int sensor)
{
    if(ui->frame_10->isVisible())
    {
        int len = 12;
        qDebug()<<"***********************gprs_sendMsg handle.******************\n";

        if((ui->number_value->text().length()) != 11){
        QMessageBox::information(0,0,QString::fromUtf8("电话号码长度错误"));
        return;
        }
        sprintf(phone_num,"%s",ui->number_value->text().toLocal8Bit().data());
        if(Sim_state==1)
        {
            if(sensor==1)
            {
                ui->send_msg->setText("send rfid...");
                cliect_thread->Api_Cliect_SendGprsMessage(phone_num,1);


            }
            else if(sensor==2)
            {
                ui->send_msg->setText("send smog...");
                cliect_thread->Api_Cliect_SendGprsMessage(phone_num,2);

            }
            else if(sensor==3)
            {
                ui->send_msg->setText("send int...");
                cliect_thread->Api_Cliect_SendGprsMessage(phone_num,3);

            }
        }
    }
}

void MainWidget::SaveTelNum()
{

    if((ui->number_value->text().length()) != 11){
        QMessageBox::information(0,0,QString::fromUtf8("电话号码长度错误!请重新设置电话号码"));
        return;
    }

    QFile file( "./phoneNumber.txt" );

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug()<<"Open phoneNumber.txt file failed.";
        exit(-1);
    }
    QTextStream out(&file);
    out<<(ui->number_value->text().toLocal8Bit());
    qDebug()<<(ui->number_value->text().toLocal8Bit());
    file.close();

    QMessageBox infoBox;
    infoBox.information(0,0,QString::fromUtf8("成功保存电话号码"));

}
void MainWidget::on_btn_Back_clicked()
{
    ui->number_value->backspace();
}
