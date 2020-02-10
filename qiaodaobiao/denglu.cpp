#include "denglu.h"
#include "ui_denglu.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include "widget.h"
#include <QDebug>
#include <QSqlQuery>
denglu::denglu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::denglu)
{
    ui->setupUi(this);

    QSqlDatabase db =QSqlDatabase::addDatabase("QMYSQL");
    //输入数据库的信息，打开数据库
    db.setDatabaseName("20_qiandao");
    db.setUserName("root");
    db.setPassword("123456");
    if(db.open())
    {
        qDebug()<<"打开数据库成功";
    }
    else
    {
        qDebug()<<"打开数据库失败";
    }
}

denglu::~denglu()
{
    delete ui;
}

void denglu::on_pushButton_clicked()
{
    QString sname=ui->lineEdit->text();
    QString pwd=ui->lineEdit_2->text();

    QSqlQuery q;
    q.exec(QString("select * from student where sname='%1'").arg(sname));
    if(q.size()>0)
    {
        q.exec(QString("select * from student where sname='%1' and pwd='%2'").arg(sname).arg(pwd));
        if(q.size()>0)
        {
            Widget *w=new Widget(NULL,sname);
            w->show();
            this->close();
        }
        else
        {
            QMessageBox::warning(this,"warn","密码错误");
        }
    }
    else
    {
         QMessageBox::warning(this,"warn","用户不存在");
    }

}
