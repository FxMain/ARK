#include "newdoc.h"
#include "ui_newdoc.h"
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

extern QSqlDatabase db;
extern QSqlQueryModel *model;
extern QSqlQuery query;
newdoc::newdoc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newdoc)
{
    //setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setWindowFlags(Qt::FramelessWindowHint);

    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(145,145,145)));
    ui->setupUi(this);
    tableViewModel=new QStandardItemModel(this);
    tableViewModel->setColumnCount(2);

    //model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("序号"));
    tableViewModel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("代保管物品名称"));
    tableViewModel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("代保管物品号码"));

    //背景网格线设置
    //显示
    ui->tableView->setShowGrid(true);
    //取消
    //ui->tableView->setShowGrid(false);
    ui->tableView->setModel(tableViewModel);



}

newdoc::~newdoc()
{
    delete ui;
}



void newdoc::on_pushButton_4_clicked()//清空列表按钮单击事件
{
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();

    tableViewModel->clear();//清空列表
   // ui->tableView->clearFocus();
}

void newdoc::on_pushButton_clicked()//读取标签按钮事件
{

    //connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT( show_list() ));



    //qDebug()<<wupingliebiao7;

}

void newdoc::on_pushButton_3_clicked()//录入按钮事件
{

    query = QSqlQuery(db);
    bool query_OK= query.exec("create table mys(hetonhao1 vchar primary key,weituobumen2 vchar ,weituoren3 vchar ,baoguanyapingming4 vchar ,baoguanyapinghao5 vchar ,baoguanwujiazhi6 vchar ,wupingliebiao7 vchar ,dianzibiaoqian8 vchar,rq9 vchar)");
    if(query_OK)
    {
        qDebug()<< "create table success!";
    }
    else
    {
        qDebug()<< "create table fail!"  << db.lastError();

    }


    hetonhao1           =ui->lineEdit_1->text();
    weituobumen2        =ui->lineEdit_2->text();
    weituoren3          =ui->lineEdit_3->text();
    baoguanyapingming4  =ui->lineEdit_4->text();
    baoguanyapinghao5   =ui->lineEdit_5->text();
    baoguanwujiazhi6    =ui->lineEdit_6->text();
    rq9                 =ui->lineEditrq->text();

    int NumberRow = ui->tableView->model()->rowCount();//获取总行数
    int NumberColumn = ui->tableView->model()->columnCount();//获取总列数


    wupingliebiao7="";
    if(NumberRow>0&&NumberColumn>0)
    {
        for(int h=0;h<NumberRow;h++)
        {

                //h1l1+&h1l2|h2l1+&h2l2
                //遍历第row行的所有信息
                 QModelIndex index = tableViewModel->index(h,0);
                 QString nr = tableViewModel->data(index).toString();

                 index = tableViewModel->index(h,1);
                 nr = nr+","+tableViewModel->data(index).toString();
                 if(h<NumberRow-1)nr+="|";
                 wupingliebiao7+=nr;


        }
    }

   // wupingliebiao7      =ui->lineEdit_7->text();//分割符做
    dianzibiaoqian8     =ui->lineEdit_9->text();

    QString insert_buf;
    insert_buf=QObject::tr("insert into mys values('%1','%2','%3','%4','%5','%6','%7','%8','%9')").arg(hetonhao1,weituobumen2,weituoren3,baoguanyapingming4,baoguanyapinghao5,baoguanwujiazhi6,wupingliebiao7,dianzibiaoqian8,rq9);
    //qDebug()<<insert_buf;

    if(hetonhao1.isEmpty() || weituobumen2.isEmpty() || weituoren3.isEmpty()|| baoguanyapingming4.isEmpty()||
       baoguanyapinghao5.isEmpty()|| baoguanwujiazhi6.isEmpty()|| wupingliebiao7.isEmpty()|| dianzibiaoqian8.isEmpty()|| rq9.isEmpty())
    {
        QMessageBox::warning(this,"Incomplete information","error");
        return;
    }

    if(! query.exec(insert_buf))
    {
          qDebug() << query.lastError();
    }
    else
    {
          qDebug() << "inserted Wang!";
          on_pushButton_2_clicked();
    }



}

void newdoc::on_pushButton_2_clicked()//取消按钮事件
{
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();

    ui->lineEditrq->clear();

    tableViewModel->clear();//清空列表
}

void newdoc::on_pushButton_5_clicked()//添加表单
{

        //定义item
        QStandardItem* item;


        int _rowCount=tableViewModel->rowCount()-1;
        //ui->tableView->row
        if(_rowCount<0){

            _rowCount=0;
        }else{
            _rowCount=tableViewModel->rowCount();
        }


        item = new QStandardItem(ui->lineEdit_7->text());
        tableViewModel->setItem(_rowCount,0,item);

        item = new QStandardItem(ui->lineEdit_8->text());
        tableViewModel->setItem(_rowCount,1,item);

        ui->tableView->setModel(tableViewModel);

        ui->tableView->show();
}

void newdoc::on_pushButton_6_clicked()//表单删除
{
    int _row=ui->tableView->currentIndex().row();
    if(_row!=-1){
      tableViewModel->removeRow(_row);//删除表项
    }
}
