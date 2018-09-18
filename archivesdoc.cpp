#include "archivesdoc.h"
#include "ui_archivesdoc.h"


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <Qdebug>
extern QSqlQuery query;
extern QSqlDatabase db;
extern QSqlQueryModel *model;
archivesdoc::archivesdoc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::archivesdoc)
{
    setWindowFlags(Qt::FramelessWindowHint);

    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(145,145,145)));


    ui->setupUi(this);
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->pushButton_2->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    dbshow();
}

archivesdoc::~archivesdoc()
{
    delete ui;
}
void archivesdoc::dbshow()
{

     db=QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("mys.db");
     bool ok=db.open();
     if(ok)
     {
        //QMessageBox::information(this,"Information","");
     }
     else
     {
        QMessageBox::information(this,"Information","数据库打开失败");
     }
    model = new QSqlQueryModel(this);

    QString Qfind;
    Qfind="SELECT * FROM mys";
    model->setQuery(Qfind);
    model->setHeaderData(0,Qt::Horizontal,tr("合同号"));
    model->setHeaderData(1,Qt::Horizontal,tr("委托部门"));
    model->setHeaderData(2,Qt::Horizontal,tr("委托人"));
    model->setHeaderData(3,Qt::Horizontal,tr("保管物品名"));
    model->setHeaderData(4,Qt::Horizontal,tr("保管物品号"));
    model->setHeaderData(5,Qt::Horizontal,tr("保管物总价值"));
    model->setHeaderData(6,Qt::Horizontal,tr("物品列表"));
    model->setHeaderData(7,Qt::Horizontal,tr("电子标签"));
    ui->tableView->setModel(model);
}
void archivesdoc::on_pushButton_clicked()//查询按钮
{
    //ui->tableView->resizeRowsToContents();
    //bool query_OK=0;
     db=QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("mys.db");
     bool ok=db.open();
     if(ok)
     {
        //QMessageBox::information(this,"Information","");
     }
     else
     {
        QMessageBox::information(this,"Information","数据库打开失败");
     }
    //   QString hetonhao1,weituobumen2,weituoren3,baoguanyapingming4,baoguanyapinghao5,baoguanwujiazhi6,wupingliebiao7,dianzibiaoqian8;
    //QSqlQuery query;
    model = new QSqlQueryModel(this);
    //model->setQuery("select * from mys");//"SELECT * FROM member WHERE (管理员姓名='%1')").arg(Menager::loginname)
    QString Qfind;
    if(ui->lineEdit->text().isEmpty())
    {
        Qfind="SELECT * FROM mys";
    }
    else
    {
        Qfind="SELECT * FROM mys WHERE (hetonhao1='"+ui->lineEdit->text()+"')"+
                "OR (weituobumen2='"+ui->lineEdit->text()+"') "+
                "OR (weituoren3='"+ui->lineEdit->text()+"')"+
                "OR (baoguanyapingming4='"+ui->lineEdit->text()+"')"+
                "OR (baoguanyapinghao5='"+ui->lineEdit->text()+"')"+
                "OR (baoguanwujiazhi6='"+ui->lineEdit->text()+"')"+
                "OR (wupingliebiao7='"+ui->lineEdit->text()+"')"+
                "OR (dianzibiaoqian8='"+ui->lineEdit->text()+"')";
    }

    model->setQuery(Qfind);
    model->setHeaderData(0,Qt::Horizontal,tr("合同号"));
    model->setHeaderData(1,Qt::Horizontal,tr("委托部门"));
    model->setHeaderData(2,Qt::Horizontal,tr("委托人"));
    model->setHeaderData(3,Qt::Horizontal,tr("保管物品名"));
    model->setHeaderData(4,Qt::Horizontal,tr("保管物品号"));
    model->setHeaderData(5,Qt::Horizontal,tr("保管物总价值"));
    model->setHeaderData(6,Qt::Horizontal,tr("物品列表"));
    model->setHeaderData(7,Qt::Horizontal,tr("电子标签"));

    ui->tableView->setModel(model);
}
