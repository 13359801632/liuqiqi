#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCheckbox>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QDateTime>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include "person.h"
Widget::Widget(QWidget *parent,QString sname) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //创建对象添加数据库
    this->sname=sname;
    //从数据库把数据读到qt
   shujutobiao("select * from student");
   displayclass();
   displaysno();
   connect(ui->tableWidget,QTableWidget::cellDoubleClicked,[=](int r,int c){
       //双击时，将person表和ui表连接并显示
       person * p= new person();
       p->init(ui->tableWidget->item(r,0)->text(),ui->tableWidget->item(r,1)->text());
       p->show();
   });



}
void Widget::displayclass()//按班级查找
{
    //把班级添加到combobox
    QSqlQuery q4;
    q4.exec("select distinct class from student");
    ui->comboBox->addItem("全部班级");
    while(q4.next())
    {
        ui->comboBox->addItem(q4.value(0).toString());
    }
    //点击选项，切换班级
    connect(ui->comboBox,QComboBox::currentTextChanged,[=](QString text){
        if(text=="全部班级")
        {
          shujutobiao("select * from student");
        }
        else
        {
        shujutobiao(QString("select * from student where class='%1'").arg(text));
        }
    });
}
void Widget::displaysno()
{
    //按学号查找
    connect(ui->pushButton,QPushButton::clicked,[=](){
        if(ui->lineEdit->text().isEmpty())
        {
            QMessageBox::warning(this,"warn","我想放假");
        }
        else
        {
            shujutobiao(QString("select * from student where sno like '%1'").arg(ui->lineEdit->text()));
        }
    });
}
void Widget::shujutobiao(QString sql)
{
    qDebug()<<this->sname;

    QSqlQuery q;
    q.exec(QString("select sno from student where sname='%1'").arg(this->sname));
    q.next();
    QString curSno =q.value(0).toString();

    if(q.exec(sql))
    {
        ui->tableWidget->setRowCount(q.size());//设置行数
        int i =0;
        while(q.next())//循环输出
        {
           QCheckBox *c = new QCheckBox("未签到");//创建一个按钮检查第四列是否签到，初始未签到
           QString sno= q.value(0).toString();//申明变量学号
           QSqlQuery q3;//签到状态设置
           q3.exec((QString("select qiandaotime from qiandao where sno=%1 and date(qiandaotime)=curdate()"
                            "order by qiandaotime desc").arg(sno)));

           q3.next();
           if(sno !=curSno)
           {
              c->setDisabled(true);
           }
           if(q3.size())
           {
               c->setText("已签到");
               c->setDisabled(true);//不可更改
               c->setChecked(true);
               ui->tableWidget->setItem(i,4,new QTableWidgetItem(q3.value(0).toString()));
           }
           ui->tableWidget->setItem(i,0,new QTableWidgetItem(sno));
           ui->tableWidget->setItem(i,1,new QTableWidgetItem(q.value(1).toString()));
           ui->tableWidget->setItem(i,2,new QTableWidgetItem(q.value(2).toString()));
           ui->tableWidget->setCellWidget(i,3,c);
           connect(c,QCheckBox::clicked,[=](){
               //1.修改控件本身的状态
               c->setText("已签到");
               c->setDisabled(true);//按钮不可修改
               //2.向表中添加签到时间
               ui->tableWidget->setItem(i,4,new QTableWidgetItem(QDateTime::currentDateTime().toString()));
               //3.把这个人添加到签到表中
               QSqlQuery q1;
               qDebug()<<q1.exec(QString("insert into qiandao values(%1,now())").arg(sno));
           });
           i++;
        }
    }
}
Widget::~Widget()
{
    delete ui;
}
