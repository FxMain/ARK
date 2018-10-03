#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cd.h"
#include "newdoc.h"
#include <QtSql>
extern QSqlDatabase db;
extern QSqlQueryModel *model;
extern QSqlQuery query;
QString LandingRole;//登陆的角色，方便权限管理
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //打开数据库
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("ManagementSystemSatabase.db");
    bool ok=db.open();
    if(ok)
    {
       QMessageBox::information(this,"提示","数据库已准备可以进行相关操作");
    }
    else
    {
       QMessageBox::information(this,"提示","数据库打开失败");
    }
    ui->lineEdit->setEchoMode(QLineEdit::Password);
//    query = QSqlQuery(db);
//    //   QString yonghu,mima,juese,shengfengzheng,zhiwen,renlianshibie;
//    bool query_OK= query.exec("create table use(yonghu vchar primary key,mima vchar ,juese vchar ,shengfengzheng vchar ,zhiwen vchar ,renlianshibie vchar )");
//    if(query_OK)
//    {
//        qDebug()<< "create table success!";
//    }
//    else
//    {
//        qDebug()<< "create table fail!"  << db.lastError();

//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button_DL_clicked()
{
    LandingRole="";
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty()){
        QMessageBox::information(this,"警告","请填写人完整!");
        return;
    }
    QString Qfind="SELECT * FROM use WHERE yonghu='"+ui->lineEdit_2->text()+"'";
    query = QSqlQuery(db);
    if(!query.exec(Qfind))
    {
        qDebug()<<query.lastError();
    }
    else
    {
        QString u="";
        QString p="";
        QString s="";
        while(query.next())
        {
            u = query.value(0).toString();
            p = query.value(1).toString();
            s = query.value(2).toString();
            qDebug()<<QString("用户名:%1,密码:%2,角色:%3").arg(u).arg(p).arg(s);

        }
        if(u.isEmpty()||p.isEmpty()||s.isEmpty())
        {
            return;
        }else if(u==ui->lineEdit_2->text()&&p==ui->lineEdit->text()){
            LandingRole=s;
            cd d;
            this->hide();//隐藏主窗口
            d.exec();
            qDebug()<<"可以登录";
        }

    }



}

void MainWindow::on_Button_TC_clicked()
{
    qApp->quit();

}
