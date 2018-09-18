#ifndef ARCHIVESDOC_H
#define ARCHIVESDOC_H

#include <QDialog>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquerymodel.h>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QStandardItemModel>
namespace Ui {
class archivesdoc;
}

class archivesdoc : public QDialog
{
    Q_OBJECT

public:
    explicit archivesdoc(QWidget *parent = 0);
    ~archivesdoc();

private slots:
    void on_pushButton_clicked();

private:
    Ui::archivesdoc *ui;
    void dbshow();
    //QStandardItemModel  *model2;
};

#endif // ARCHIVESDOC_H
