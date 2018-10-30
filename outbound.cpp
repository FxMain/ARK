#include "outbound.h"
#include "ui_outbound.h"
#include <Qdebug>
#include <QStringList>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

extern QSqlDatabase db;
extern QSqlQueryModel *model;
extern QSqlQuery query;
extern QString CabinetCommunicationIp;//主机柜IP
extern QString CabinetCommunicationId;//主机柜当前通信ID
Server *server;

QByteArray CabinetCommunicationCdata;

QByteArray CabinetCommunicationTdata;
outbound::outbound(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::outbound)
{

    setWindowFlags(Qt::FramelessWindowHint);

    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(145,145,145)));

    ui->setupUi(this);



    server = new Server(this);
    timer=new QTimer(this);
    server->listen(QHostAddress::Any, 1994);

    connect(timer, SIGNAL(timeout()), this, SLOT(sendLoopMessage()));
    timer->start(1);

    socket = new QTcpSocket();
    //连接信号槽
    QObject::connect(socket, &QTcpSocket::readyRead, this, &outbound::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &outbound::socket_Disconnected);





    tableViewModel=new QStandardItemModel(this);
    tableViewModel->setColumnCount(2);
    tableViewModel->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("IP"));
    tableViewModel->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("ID"));
    ui->tableView->setModel(tableViewModel);



}

outbound::~outbound()
{
    delete ui;
    delete socket;
}

QString outbound::getHostIpAddress()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
               ipAddressesList.at(i).toIPv4Address()) {
               strIpAddress = ipAddressesList.at(i).toString();
               break;
           }
     }
     // 如果没有找到，则以本地IP地址为IP
     if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
     return strIpAddress;
}
void outbound::on_pushButton_clicked()
{
    QString _ip = getHostIpAddress();
    //qDebug>>_ip;
    qDebug()<<_ip;
    ui->lineEdit->setText(_ip);
}


void outbound::showConnection()//客户进入
{
    count++;
    //定义item
    QStandardItem* item;
    int _rowCount=tableViewModel->rowCount()-1;
    if(_rowCount<0){

        _rowCount=0;
    }else{
        _rowCount=tableViewModel->rowCount();
    }

    item = new QStandardItem(QString("%1").arg(server->socketList.last()));


    tableViewModel->setItem(_rowCount,1,item);
    ui->tableView->setModel(tableViewModel);
    ui->tableView->show();


}

void outbound::showDisconnection(int socketDescriptor)//客户退出
{
    count--;

    /* remove disconnect socketdescriptor from list */
    server->socketList.removeAll(socketDescriptor);

    /* reload combobox */
    tableViewModel->clear();//清空列表
    QStandardItem* item = 0;
    for (int i = 0; i < server->socketList.size(); i++) {

        item = new QStandardItem(QString("%1").arg(server->socketList.at(i)));
        tableViewModel->setItem(i,1,item);

    }
     ui->tableView->setModel(tableViewModel);

}



void outbound::sendMsg(QByteArray data, int id)//发送数据给指定一个客户
{
    emit sendData(data, id);

}
void outbound::IPIDtableView(QString peerAddr)
{
    QStandardItem* item;



    QString IPP=peerAddr.section('|',0,0);

    QString IDD=peerAddr.section('|',1);
    //qDebug() <<"IPP:"<<IPP<<"IDD:"<<IDD;
    for (int i = 0; i < server->socketList.size(); i++) {
        QString IDDD=QString("%1").arg(server->socketList.at(i));



        //QString nr = tableViewModel->data(index).toString();
        //tem = new QStandardItem(IDDD);
        //tableViewModel->setItem(i,1,item);
        if(IDDD==IDD){
            QModelIndex index = tableViewModel->index(i,0);//第I行第一列的数据
            QString IPPP=tableViewModel->data(index).toString();
            if(IPPP!=IPP)
            {
                item = new QStandardItem(IPP);
                tableViewModel->setItem(i,0,item);
                ui->tableView->setModel(tableViewModel);
            }

            return;
        }
    }


}

void outbound::revData(QString peerAddr, QByteArray data)//客户端数据到达
{

    //QString msg;
    qDebug() <<peerAddr<<":"<<data;
    IPIDtableView(peerAddr);

    QString CIP=peerAddr.section('|',0,0);//得到数据所属客户端IP
    QString CID=peerAddr.section('|',1);
    //qDebug() <<"CIP:" <<CIP<<"CID:" <<CID;
    if(CIP==CabinetCommunicationIp)//如果是主机柜发来的
    {
        CabinetCommunicationId=CID;
        if(data.size()>=3)
        {
            //QByteRef
            QByteArray c;
            c[0]=0xAA;
            c[1]=0xAF;
            if( data.count(c)>0)
            {
                //goto xtb;
            }

        }
        CabinetCommunicationCdata+=data;

        qDebug() <<"CabinetCommunicationCdata:"<<CabinetCommunicationCdata.toHex('/');
    }
//xtb:
    ;
    //qDebug() <<"IPP:"<<IPP<<"IDD:"<<IDD;

    //msg = QString::fromLocal8Bit(data);
    //peerAddr.insert(peerAddr.size(), ": ");
    //msg.prepend(peerAddr);

    //qDebug() << msg;

}

void outbound::sendLoopMessage()
{
   if(CabinetCommunicationTdata.size()<=0)
   {

       return;
   }

   emit sendData(CabinetCommunicationTdata,CabinetCommunicationId.toInt());
    qDebug()<<"T";
   CabinetCommunicationTdata.clear();
}

void outbound::stopLoopSend()
{
    timer->stop();
}


void outbound::on_pushButton_3_clicked()//刷新/查询
{
    QString send="send";

    qDebug()<<"刷新/查询";
    int _row=ui->tableView->currentIndex().row();//选中
    qDebug()<<"刷新/查询"<<_row;
    if(_row==-1){
      return;
    }
    QModelIndex index = tableViewModel->index(_row,1);
    QString _id = tableViewModel->data(index).toString();
    qDebug()<<"_id"<<_id;
    sendMsg(send.toLocal8Bit(),_id.toInt());
}
/**********************************************客户端部分*******************************************************/
void outbound::onConnect_clicked(QString Connect)
{
    if(Connect == tr("连接"))
    {
        QString IP;
        int port=1994;

        //获取IP地址
        IP = ui->lineEdit_2->text();



        //取消已有的连接
        socket->abort();
        //连接服务器
        socket->connectToHost(IP, port);

        //等待连接成功
        if(!socket->waitForConnected(30000))
        {
            qDebug() << "Connection failed!";
            return;
        }
        qDebug() << "Connect successfully!";
    }
    else
    {
        //断开连接
        socket->disconnectFromHost();
        qDebug() << "断开连接";

    }
}


void outbound::socket_Read_Data()//服务器数据到达
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
        QString str = tr(buffer);
        //qDebug() << buffer.data();

    }
    /*char *cbuf;
    int i=socket->read(cbuf,1);
    qDebug() <<i;
    i=socket->read(cbuf,1);
    qDebug() <<i;
    i=socket->read(cbuf,1);
    qDebug() <<i;*/

}

void outbound::socket_Disconnected()
{
    //发送按键失能

    qDebug() << "Disconnected!";
}

void outbound::on_pushButton_2_clicked()
{
    onConnect_clicked("连接");
}

void outbound::on_pushButton_5_clicked()//设置主机柜IP
{


    //查询有没有该条类型数据，有先删除再添加-----------------------
    QString Qfind="SELECT * FROM socket WHERE type='cabinet'";
    query = QSqlQuery(db);
    if(!query.exec(Qfind))
    {
        qDebug()<<query.lastError();
    }
    else
    {
        QString ip="";
        QString type="";
        QString other="";
        while(query.next())
        {
            ip = query.value(0).toString();
            type = query.value(1).toString();
            other = query.value(2).toString();


        }
        if(ip.isEmpty()||type.isEmpty()||other.isEmpty())
        {
            //QMessageBox::warning(this,"提示","还没有该数据");
            //return;
        }else {

            query.prepare(QString("delete from socket where type = ?"));
            query.addBindValue("cabinet");
            if(! query.exec())
            {
                  qDebug() << query.lastError();
            }
            else
            {
                  //qDebug() << "inserted Wang!";
                    QMessageBox::warning(this,"提示","删除原来数据，添加新的数据");

            }
        }

    }


    //添加数据---------------------------------------
    QString insert_buf;
    insert_buf=QString("insert into socket values('%1','%2','%3')").arg(ui->lineEdit_4->text(),"cabinet","|");
    //qDebug()<<insert_buf;

    if(ui->lineEdit_4->text().isEmpty())
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
          CabinetCommunicationIp=ui->lineEdit_4->text();
          QMessageBox::warning(this,"提示","设置成功");

    }
}

void outbound::on_pushButton_4_clicked()//查询主机柜IP
{


     QString Qfind="SELECT * FROM socket WHERE type='cabinet'";
     query = QSqlQuery(db);
     if(!query.exec(Qfind))
     {
         qDebug()<<query.lastError();
     }
     else
     {
         QString ip="";
         QString type="";
         QString other="";
         while(query.next())
         {
             ip = query.value(0).toString();
             type = query.value(1).toString();
             other = query.value(2).toString();
             //qDebug()<<QString("用户名:%1,密码:%2,角色:%3").arg(u).arg(p).arg(s);

         }
         if(ip.isEmpty()||type.isEmpty()||other.isEmpty())
         {
              QMessageBox::warning(this,"提示","还没有该数据");
             return;
         }else {

             ui->lineEdit_4->setText(ip);
         }

     }
}
