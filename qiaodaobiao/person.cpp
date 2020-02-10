#include "person.h"
#include "ui_person.h"
#include <QSqlQuery>
#include <QTextCharFormat>
person::person(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::person)
{
    ui->setupUi(this);
}

void person::init(QString sno,QString sname)//由签到表界面跳转到个人信息界面
{
    //将学生信息传入person表
    ui->label->setText("学号"+sno);
    ui->label_2->setText("姓名"+sname);
    //获取签到次数
    QSqlQuery q;
    q.exec(QString("select qiandaotime from qiandao where sno=%1 and date_format(qiandaotime,'%Y-%m')=date_format(curdate(),'%Y-%m')").arg(sno));
    ui->label_3->setText("签到次数"+QString::number(q.size() ));
     //设置本月签到日期的格式
    QTextCharFormat f;
    f.setForeground(Qt::green);
    f.setBackground(Qt::red);
    while(q.next())
    {
        ui->calendarWidget->setDateTextFormat(q.value(0).toDate(),f);
    }
}
person::~person()
{
    delete ui;
}
