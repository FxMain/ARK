#include "archivesdoc.h"
#include "ui_archivesdoc.h"


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <Qdebug>

#include "outbound.h"
extern QSqlQuery query;
extern QSqlDatabase db;
extern QSqlQueryModel *model;


extern QString CabinetCommunicationIp;//主机柜IP
extern QString CabinetCommunicationId;//主机柜当前通信ID

extern Server *server;
extern QByteArray CabinetCommunicationCdata;
extern QByteArray CabinetCommunicationTdata;
extern void delay_ms(int msec);
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
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    dbshow();
}

archivesdoc::~archivesdoc()
{
    delete ui;
}
void archivesdoc::dbshow()
{


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
    model->setHeaderData(8,Qt::Horizontal,tr("日期"));
    model->setHeaderData(9,Qt::Horizontal,tr("位置"));
    ui->tableView->setModel(model);
}
void archivesdoc::on_pushButton_clicked()//查询按钮
{
    //ui->tableView->resizeRowsToContents();
    //bool query_OK=0;

    model = new QSqlQueryModel(this);
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
    model->setHeaderData(8,Qt::Horizontal,tr("日期"));
    model->setHeaderData(9,Qt::Horizontal,tr("位置"));
    ui->tableView->setModel(model);
}
//出库数据流：
//1、主机发X柜Y槽出库，然后一直等待到4
//2、从机回复收到（X柜Y槽+状态）（从机打开响应柜门）
//3、人员拔出文件
//4、从机发送X柜Y槽+ID号+离开
//5、主机收到，发送关X柜Y槽的指令
//6、从机回复收到，（等待人关门）

//主机查询槽详情流程：
//1、主机发查询X柜Y槽
//2、从机回复X柜Y槽+ID（空为全0）
void archivesdoc::on_pushButton_2_clicked()//修改
{

}
void OutboundOpendDoor(unsigned int g,unsigned int k)
{
    QByteArray temp;
    CabinetCommunicationTdata.clear();
    temp[0]=0xBB;//包头
    temp[1]=0xB0;//功能字
    temp[2]=0x06;//长
    temp[3]=g;//柜
    temp[4]=0x00;//门
    temp[5]=k>>8;//卡槽
    temp[6]=k;
    temp[7]=temp[2]+temp[3]+temp[4]+temp[5]+temp[6];//和
    CabinetCommunicationTdata=temp;

}
void archivesdoc::on_pushButton_3_clicked()//出库
{




     query = QSqlQuery(db);
     int _row=ui->tableView->currentIndex().row();
     if(_row==-1){
         QMessageBox::warning(this,"提示","请选择出库对象");
         return;
     }
     QModelIndex index = model->index(_row,9);
     QString nr = model->data(index).toString();

     QString gh=nr.section('|',0,0);//柜号
     QString kch=nr.section('|',1);//卡槽号

     QString dzbq=model->data(model->index(_row,7)).toString();

     qDebug()<<"出库位置："<<nr<<"-"<<gh<<"-"<<kch<<"电子标签："<<dzbq;
     OutboundOpendDoor((unsigned int)gh.toInt(),(unsigned int)kch.toInt());//发送指令到单片机
     //等待回复
     int mscount=50000;
     while(mscount--)
     {

         if(CabinetCommunicationCdata.size()>3)
         {
             QByteArray buf;
             int i=0;
             buf[i++]=0xAA;
             buf[i++]=0xA0;//有文件出库
             if( CabinetCommunicationCdata.count(buf)>0&&CabinetCommunicationCdata.size()>=CabinetCommunicationCdata[2])//检测到包头
             {
                 int sum=0;
                 for(int ii=2;ii<CabinetCommunicationCdata[2]-1;ii++){
                     sum+=CabinetCommunicationCdata[ii];
                 }
                 if(sum==CabinetCommunicationCdata[CabinetCommunicationCdata[2]+1]){//校验和成功
                     //if()ID号相等
                     qDebug()<<"文件插入成功";

                 }
             }

         }
         delay_ms(1);//让循环不堵塞其他线程
     }

     query.prepare(QString("delete from mys where hetonhao1 = ?"));
     query.addBindValue(nr);
     if(! query.exec())
     {
           qDebug() << query.lastError();
     }
     else
     {
           qDebug() << "inserted Wang!";

     }
     dbshow();

}


