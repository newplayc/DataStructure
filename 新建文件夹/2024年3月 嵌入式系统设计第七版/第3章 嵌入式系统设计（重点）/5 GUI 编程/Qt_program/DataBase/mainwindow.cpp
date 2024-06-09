#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sql_table_set= tr("CREATE TABLE IF NOT EXISTS student (id int primary key, number int, name varchar(50), score float)");
    select_string_set = tr("select max(id) from student");
    delete_string_set= tr("DELETE  FROM student WHERE id IS ");
    clear_string_set =tr("DELETE FROM student");
    max_id = 0;
    // Create Database - MyDataBase
        MyDataBase = sql_create();
        // open MyDataBase and operation
        if(!MyDataBase.open())
        {
            qDebug() << "Error: Failed to connect database." << MyDataBase.lastError();
        }
        else
        {
            // create table if it's not available
            sql_table = sql_create_table(sql_table_set);
            // get max id
            max_id = sql_select_maxid(sql_table, select_string_set);
            // if table data is available do
            if(max_id>0)
            {
                // query max_id corresponding data
                QString select_all = "SELECT * from student WHERE id IS "+QString::number(max_id)+"";

                if(!sql_table.exec(select_all))
                {
                    qDebug()<<sql_table.lastError();
                }
                else
                {
                    while(sql_table.next())
                    {
                        QString number_string = sql_table.value(1).toString();
                        QString name_string = sql_table.value(2).toString();
                        QString score_string = sql_table.value(3).toString();
                        // output to corresponding lineEdit
                        ui->lineEdit_Item->setText(QString::number(max_id));
                        ui->lineEdit_Number->setText(number_string);
                        ui->lineEdit_Name->setText(name_string);
                        ui->lineEdit_Score->setText(score_string);
                    }
                }

            }
        }
        // close MyDataBase
        sql_close(MyDataBase);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Add_clicked()
{
    // open MyDataBase and operation
        if(!MyDataBase.open())
        {
            qDebug() << "Error: Failed to connect database." << MyDataBase.lastError();
        }
        else
        {
            // create table if it's not available
            sql_table = sql_create_table(sql_table_set);
            // get max id
            max_id = sql_select_maxid(sql_table, select_string_set);
            // add current lineEdit data to database table
             QString number_string = ui->lineEdit_Number->text();
            QString name_string = ui->lineEdit_Name->text();
            QString score_string = ui->lineEdit_Score->text();
            QString data_string = "INSERT INTO student VALUES("+QString::number(max_id+1)+", "+"\""+number_string+"\""+", "+"\""+name_string+"\""+", "+score_string+")";

            if(sql_insert_data(sql_table, data_string) < 0)
            {
                qDebug() << "Error: Failed to inseat data!";
            }
            else
            {
                // show latest data to corresponding lineEdit
                ui->lineEdit_Item->setText(QString::number(max_id+1));
                ui->lineEdit_Number->setText(number_string);
                ui->lineEdit_Name->setText(name_string);
                ui->lineEdit_Score->setText(score_string);
            }
        }
        // close MyDataBase
        sql_close(MyDataBase);
}

void MainWindow::on_pushButton_Pre_clicked()
{
    if(!MyDataBase.open())
       {
           qDebug() << "Error: Failed to connect database." << MyDataBase.lastError();
       }
    else
       {
           // get current id
           int current_id = ui->lineEdit_Item->text().toInt();

           // if table data is available do
           if(current_id > 1)
           {
               // query previous id corresponding data
               QString select_all = "SELECT * from student WHERE id IS "+QString::number(current_id-1);

               if(!sql_table.exec(select_all))
               {
                   qDebug()<<sql_table.lastError();
               }
               else
               {
                   while(sql_table.next())
                   {
                       QString number_string = sql_table.value(1).toString();
                       QString name_string = sql_table.value(2).toString();
                       QString score_string = sql_table.value(3).toString();
                       // output to corresponding lineEdit
                       ui->lineEdit_Item->setText(QString::number(current_id-1));
                        ui->lineEdit_Number->setText(number_string);
                       ui->lineEdit_Name->setText(name_string);
                       ui->lineEdit_Score->setText(score_string);
                   }
               }

           }
       }
       // close MyDataBase
       sql_close(MyDataBase);
}

void MainWindow::on_pushButton_Next_clicked()
{
    if(!MyDataBase.open())
        {
            qDebug() << "Error: Failed to connect database." << MyDataBase.lastError();
        }
    else
        {
            // get current id and max id
            int current_id = ui->lineEdit_Item->text().toInt();
            max_id = sql_select_maxid(sql_table, select_string_set);
            // if table data is available do
            if(current_id < max_id)
            {
                // query next id corresponding data
                QString select_all = "SELECT * from student WHERE id IS "+QString::number(current_id+1);

                if(!sql_table.exec(select_all))
                {
                    qDebug()<<sql_table.lastError();
                }
                else
                {
                    while(sql_table.next())
                    {
                        QString number_string = sql_table.value(1).toString();
                        QString name_string = sql_table.value(2).toString();
                        QString score_string = sql_table.value(3).toString();
                        // output to corresponding lineEdit
                        ui->lineEdit_Item->setText(QString::number(current_id+1));
                        ui->lineEdit_Number->setText(number_string);
                        ui->lineEdit_Name->setText(name_string);
                        ui->lineEdit_Score->setText(score_string);
                    }
                }

            }
        }
        // close MyDataBase
        sql_close(MyDataBase);
}

void MainWindow::on_pushButton_Del_clicked()
{
    if(!MyDataBase.open())
        {
            qDebug() << "Error: Failed to connect database." << MyDataBase.lastError();
        }
    else
        {
            // get current id and max id
            int current_id = ui->lineEdit_Item->text().toInt();
            int max_id_before = sql_select_maxid(sql_table, select_string_set);

            // if table data is available do
            if(current_id > 0)
            {
                if(sql_delete_data(sql_table,delete_string_set,current_id)<0)
                {
                    qDebug() << "Delete error!";
                }
             else
                {
                    max_id = sql_select_maxid(sql_table, select_string_set);
                    if(max_id > 0)
                    {
                        if((current_id-1)>0)
                        {
                            QString select_all = "SELECT * FROM student WHERE id IS "+QString::number(current_id-1);

                            if(!sql_table.exec(select_all))
                            {
                            qDebug()<<sql_table.lastError();
                            }
                            else
                            {
                                while(sql_table.next())
                                {
                                    QString number_string = sql_table.value(1).toString();
                                    QString name_string = sql_table.value(2).toString();
                                    QString score_string = sql_table.value(3).toString();
                                    // output to corresponding lineEdit
                                    ui->lineEdit_Item->setText(QString::number(current_id-1));
                                    ui->lineEdit_Number->setText(number_string);
                                    ui->lineEdit_Name->setText(name_string);
                                    ui->lineEdit_Score->setText(score_string);
                                }
                            }
                            // re-order database, modify all items with ids > id deleted
                            for(int i=0;i<(max_id_before-current_id);i++)
                            {
                                QString update_all = "UPDATE student set id = "+QString::number(current_id+i)+" WHERE id = "+QString::number(current_id+i+1);

                                if(!sql_table.exec(update_all))
                                {
                                    qDebug() << sql_table.lastError();
                                }

                            }



                        }
                        else
                        {
                            // re-order database, modify all items with ids > id deleted
                            for(int i=0;i<(max_id_before-current_id);i++)
                            {
                                QString update_all = "UPDATE student set id = "+QString::number(current_id+i)+" WHERE id = "+QString::number(current_id+i+1);

                                if(!sql_table.exec(update_all))
                                {
                                    qDebug() << sql_table.lastError();
                                }

                            }

                            // query max_id corresponding data
                            QString select_all = "SELECT * from student WHERE id IS "+QString::number(max_id-1);

                            if(!sql_table.exec(select_all))
                            {
                                qDebug()<<sql_table.lastError();
                            }
                            else
                            {
                                while(sql_table.next())
                                {
                                    QString number_string = sql_table.value(1).toString();
                                    QString name_string = sql_table.value(2).toString();
                                    QString score_string = sql_table.value(3).toString();
                                    // output to corresponding lineEdit
                                    ui->lineEdit_Item->setText(QString::number(max_id-1));
                                    ui->lineEdit_Number->setText(number_string);
                                    ui->lineEdit_Name->setText(name_string);
                                    ui->lineEdit_Score->setText(score_string);
                                }
                            }
                        }
                    }
                    else
                    {
                        ui->lineEdit_Item->setText("");
                        ui->lineEdit_Number->setText("");
                        ui->lineEdit_Name->setText("");
                        ui->lineEdit_Score->setText("");
                    }
                }

            }
        }
        // close MyDataBase
        sql_close(MyDataBase);
}

void MainWindow::on_pushButton_Clear_clicked()
{
    if(!MyDataBase.open())
        {
            qDebug() << "Error: Failed to connect database." << MyDataBase.lastError();
        }
     else
        {
            max_id = sql_select_maxid(sql_table, select_string_set);
            if(max_id > 0)
            {
                if(sql_clear_table(sql_table,clear_string_set) < 0 )
                {
                    qDebug() << "clear table error!";
                }
                else
                {
                    qDebug() << "clear successfully!";
                    ui->lineEdit_Item->setText("");
                     ui->lineEdit_Number->setText("");
                    ui->lineEdit_Name->setText("");
                    ui->lineEdit_Score->setText("");
                }

            }
        }
}
