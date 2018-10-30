//入库数据流：
//1、主机发X柜Y槽入库(bb bf....)，然后一直等待到4
//2、从机回复收到（X柜Y槽+状态）（从机打开响应柜门）
//3、（等待）人员插入文件
//4、从机发送X柜Y槽+ID号+进入
//5、主机收到，发送关X柜Y槽的指令
//6、从机回复收到，（等待人关门）


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
#include "newdoc.h"
#include "ui_newdoc.h"
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

#include "outbound.h"
extern QSqlDatabase db;
extern QSqlQueryModel *model;
extern QSqlQuery query;

extern QString CabinetCommunicationIp;//主机柜IP
extern QString CabinetCommunicationId;//主机柜当前通信ID

extern Server *server;
extern QByteArray CabinetCommunicationCdata;
extern QByteArray CabinetCommunicationTdata;

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
    weizi10="";
   // ui->tableView->clearFocus();
}
void ReadElectronicTags(unsigned int g,unsigned int k)//读取标签
{
    QByteArray temp;
    CabinetCommunicationTdata.clear();
    temp[0]=0xBB;//包头
    temp[1]=0xBE;//功能字 读取电子标签
    temp[2]=0x06;//长
    temp[3]=g;//柜
    temp[4]=0x00;//门
    temp[5]=k>>8;//卡槽
    temp[6]=k;
    temp[7]=temp[2]+temp[3]+temp[4]+temp[5]+temp[6];//和
    CabinetCommunicationTdata=temp;

}
void newdoc::on_pushButton_clicked()//读取标签按钮事件
{

    //把光标移到编辑框
    ui->lineEdit_9->setFocus();


}

void newdoc::on_pushButton_3_clicked()//录入按钮事件
{





    query = QSqlQuery(db);
    bool query_OK= query.exec("create table mys(hetonhao1 vchar primary key,weituobumen2 vchar ,weituoren3 vchar ,baoguanyapingming4 vchar ,baoguanyapinghao5 vchar ,baoguanwujiazhi6 vchar ,wupingliebiao7 vchar ,dianzibiaoqian8 vchar,rq9 vchar,weizhi10 vchar)");
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
    insert_buf=QObject::tr("insert into mys values('%1','%2','%3','%4','%5','%6','%7','%8','%9'").arg(hetonhao1,weituobumen2,weituoren3,baoguanyapingming4,baoguanyapinghao5,baoguanwujiazhi6,wupingliebiao7,dianzibiaoqian8,rq9);
    insert_buf+=QObject::tr(",'%1')").arg(weizi10);
    //qDebug()<<insert_buf;

    if(hetonhao1.isEmpty() || weituobumen2.isEmpty() || weituoren3.isEmpty()|| baoguanyapingming4.isEmpty()||
       baoguanyapinghao5.isEmpty()|| baoguanwujiazhi6.isEmpty()|| wupingliebiao7.isEmpty()|| dianzibiaoqian8.isEmpty()||
            rq9.isEmpty()|| weizi10.isEmpty())
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
          QMessageBox::warning(this,"提示","录入完成");
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
    weizi10="";


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
int guimenN=12;
int danchengkacaoN=12;
void OpenCupboardDoor(unsigned int g,unsigned int k)
{
    QByteArray temp;
    CabinetCommunicationTdata.clear();
    temp[0]=0xBB;//包头
    temp[1]=0xBF;//功能字
    temp[2]=0x06;//长
    temp[3]=g;//柜
    temp[4]=0x00;//门
    temp[5]=k>>8;//卡槽
    temp[6]=k;
    temp[7]=temp[2]+temp[3]+temp[4]+temp[5]+temp[6];//和
    CabinetCommunicationTdata=temp;

}
void delay_ms(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void newdoc::on_pushButton_7_clicked()//打开柜门
{

    int guihao=-1;
    int kacao=-1;

    query = QSqlQuery(db);
    for(int j=0;j<12;j++)
    {
        for(int i=0;i<672;i++)
        {
            QString weizhitemp;
            QString Qfind="SELECT * FROM mys WHERE weizhi10='"+QString::number(j)+"|"+QString::number(i)+"'";
             qDebug()<<Qfind;
            if(!query.exec(Qfind))
            {
                QSqlError error=query.lastError();
                qDebug()<<error;
                if(error.text()==QSqlError::TransactionError)
                {

                }
            }
            else{


                    while(query.next())
                    {
                        weizhitemp = query.value(9).toString();

                        //qDebug()<<"weizhitemp"<<weizhitemp;

                    }
                    if(weizhitemp.isEmpty())
                    {
                        weizi10=QString::number(j)+"|"+QString::number(i);//如果不存在，就可打开柜门
                        guihao=j;
                        kacao=i;
                        QMessageBox::warning(this,"可放入位置",QString::number(guihao)+"|"+QString::number(kacao));
                        goto OpenCupboard;
                    }else {
                         //qDebug()<<"gui:"<<j<<"ka:"<<i<<"weizhitemp:"<<weizhitemp;
                    }
            }

        }
    }
OpenCupboard:

    OpenCupboardDoor(guihao,kacao);

    CabinetCommunicationCdata.clear();
    int mscount=5000;
    while(mscount--)
    {
        if(CabinetCommunicationCdata.size()>4)
        {
            QByteArray c;
            char i=0;
            //char sum=0;
            c[i++]=0xAA;
            c[i++]=0xAD;
            c[i++]=0x05;
            c[i++]=0x01;
            //c[i++]=0x30;
            //c[i++]=0x21;
            /*for(int j=0;j<i;j++)
            {
                sum+=c[j];
            }
            c[i++]=sum;*/
            //qDebug()<<"gmdk";
            if( CabinetCommunicationCdata.count(c)>0&&CabinetCommunicationCdata.size()==7)
            {
                qDebug()<<"gmdk";
                goto gmdk;
            }

        }
        delay_ms(1);//让循环不堵塞其他线程
    }

    QMessageBox::warning(this,"超时","柜门打开失败");
    return;
 gmdk:
    CabinetCommunicationCdata.clear();
    qDebug()<<"柜门打开成功，等待文件插入";
    mscount=50000;
    unsigned int Container_Number;//柜号
    unsigned int door_Number;//门号
    unsigned int slot_Number;//卡槽号
    while(mscount--)
    {

        if(CabinetCommunicationCdata.size()>3)
        {
            QByteArray buf;
            int i=0;
            buf[i++]=0xAA;
            buf[i++]=0xAC;//有文件入库
            if( CabinetCommunicationCdata.count(buf)>0&&CabinetCommunicationCdata.size()>=CabinetCommunicationCdata[2])//检测到包头
            {
                int sum=0;
                for(int ii=2;ii<CabinetCommunicationCdata[2]-1;ii++){
                    sum+=CabinetCommunicationCdata[ii];
                }
                if(sum==CabinetCommunicationCdata[CabinetCommunicationCdata[2]+1]){//校验和成功
                    //if()ID号相等
                    qDebug()<<"文件插入成功";
                    Container_Number=CabinetCommunicationCdata[3];
                    door_Number=CabinetCommunicationCdata[4];
                    slot_Number=CabinetCommunicationCdata[5]<<8&0xFF00+CabinetCommunicationCdata[6];
                    goto lrcg;
                }
            }

        }
        delay_ms(1);//让循环不堵塞其他线程
    }
 lrcg:
    QByteArray temp;
    CabinetCommunicationTdata.clear();
    temp[0]=0xBB;//包头
    temp[1]=0xBC;//功能字 收到刚刚录入文件位置
    temp[2]=0x03;//长
    temp[3]=0x01;//成功 1 失败 0，无实际意义，满足协议
    temp[4]=0x04;//和
    CabinetCommunicationTdata=temp;
    //录入成功，写进数据库
    weizi10=QString::number(Container_Number)+"|"+QString::number(slot_Number);
    QMessageBox::warning(this,"提示","文件已放好,请点击录入完成操作");


}
