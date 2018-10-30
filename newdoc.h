#ifndef NEWDOC_H
#define NEWDOC_H

#include <QDialog>

#include <QStandardItemModel>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquerymodel.h>
#include <QSqlQuery>
#include <QSqlQueryModel>



namespace Ui {
class newdoc;
}
class Server;
class newdoc : public QDialog
{
    Q_OBJECT

public:
    explicit newdoc(QWidget *parent = 0);
    ~newdoc();
signals:
    void sendDatanewdoc(QByteArray data, int id);

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
     Ui::newdoc *ui;
     QString hetonhao1,weituobumen2,weituoren3,baoguanyapingming4,baoguanyapinghao5,baoguanwujiazhi6,wupingliebiao7,dianzibiaoqian8,rq9;
     QString weizi10;
     QString name,sex,number;
     QStandardItemModel  *tableViewModel;


};

#endif // NEWDOC_H
