#ifndef OUTBOUND_H
#define OUTBOUND_H

#include <QDialog>

#include "QtNetwork/qnetworkinterface.h"
#include <QList>


#include<QTcpServer>
#include<QTcpSocket>
#include<QMessageBox>
#include<QDataStream>
#include<QString>
#include<QByteArray>

#include <QTimer>

#include "server.h"

#include <QStandardItemModel>

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquerymodel.h>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class outbound;
}
class Server;
class outbound : public QDialog
{
    Q_OBJECT

public:
    explicit outbound(QWidget *parent = 0);
    ~outbound();
    void IPIDtableView(QString peerAddr);

signals:
    void sendData(QByteArray data, int id);

public slots:

    void revData(QString peerHost, QByteArray data);
    void sendMsg(QByteArray data, int id);

private slots:
    void on_pushButton_clicked();

    void showConnection();
    void showDisconnection(int socketDescriptor);

    //void clearMsg();
    void sendLoopMessage();
    void stopLoopSend();

    void on_pushButton_3_clicked();




    void onConnect_clicked(QString Connect);
    void socket_Read_Data();
    void socket_Disconnected();


    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::outbound *ui;
    QString getHostIpAddress();

    int count;
    //Server *server;
    QTimer *timer;

    QStandardItemModel  *tableViewModel;

    QTcpSocket *socket;

};

#endif // OUTBOUND_H
