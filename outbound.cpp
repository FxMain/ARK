#include "outbound.h"
#include "ui_outbound.h"
#include <Qdebug>
outbound::outbound(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::outbound)
{

    setWindowFlags(Qt::FramelessWindowHint);

    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(145,145,145)));

    ui->setupUi(this);



    server = new Server(this);
    server->listen(QHostAddress::Any, 1994);
    //connect(timer, SIGNAL(timeout()), this, SLOT(sendLoopMessage()));


    socket = new QTcpSocket();
    //连接信号槽
    QObject::connect(socket, &QTcpSocket::readyRead, this, &outbound::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &outbound::socket_Disconnected);



    model=new QStandardItemModel(this);
    model->setColumnCount(1);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("ID"));
    ui->tableView->setModel(model);



}

outbound::~outbound()
{
    delete ui;
    delete this->socket;
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


void outbound::showConnection()
{
    count++;
    //定义item
    QStandardItem* item = 0;
    int _rowCount=model->rowCount()-1;
    if(_rowCount<0){

        _rowCount=0;
    }else{
        _rowCount=model->rowCount();
    }

    item = new QStandardItem(QString("%1").arg(server->socketList.last()));
    model->setItem(_rowCount,0,item);
    ui->tableView->setModel(model);
    ui->tableView->show();


}

void outbound::showDisconnection(int socketDescriptor)
{
    count--;

    /* remove disconnect socketdescriptor from list */
    server->socketList.removeAll(socketDescriptor);

    /* reload combobox */
    model->clear();//清空列表
    QStandardItem* item = 0;
    for (int i = 0; i < server->socketList.size(); i++) {

        item = new QStandardItem(QString("%1").arg(server->socketList.at(i)));
        model->setItem(i,0,item);

    }
     ui->tableView->setModel(model);

}



void outbound::sendMsg()
{

    QString send="send";


    int _row=ui->tableView->currentIndex().row();
    if(_row==-1){
      return;
    }
    QModelIndex index = model->index(_row,0);
    QString _id = model->data(index).toString();

    emit sendData(send.toLocal8Bit(), _id.toInt());

}


void outbound::revData(QString peerAddr, QByteArray data)
{

    QString msg;

    msg = QString::fromLocal8Bit(data);
    peerAddr.insert(peerAddr.size(), ": ");
    msg.prepend(peerAddr);

    qDebug() << msg;

}

void outbound::sendLoopMessage()
{
    QString send="send2";

    int _row=ui->tableView->currentIndex().row();
    if(_row==-1){
      return;
    }
    QModelIndex index = model->index(_row,0);
    QString _id = model->data(index).toString();

   emit sendData(send.toLocal8Bit(), _id.toInt());
}

void outbound::stopLoopSend()
{
    timer->stop();
}


void outbound::on_pushButton_3_clicked()//刷新/查询
{
    sendMsg();
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


void outbound::socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
        QString str = tr(buffer);
        qDebug() << str;

    }
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
