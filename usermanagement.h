#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QDialog>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquerymodel.h>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
namespace Ui {
class usermanagement;
}

class usermanagement : public QDialog
{
    Q_OBJECT

public:
    explicit usermanagement(QWidget *parent = 0);
    ~usermanagement();

private slots:
    void on_pushButton_6_clicked();


    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

private:
    void dbshow();
    Ui::usermanagement *ui;

    QString yonghu,mima,juese,shengfengzheng,zhiwen,renlianshibie;
};

#endif // USERMANAGEMENT_H
