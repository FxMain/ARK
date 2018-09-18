#include "usermanagement.h"
#include "ui_usermanagement.h"
//extern QSqlQuery query;
extern QSqlDatabase db;
extern QSqlQueryModel *model;
usermanagement::usermanagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usermanagement)
{
    setWindowFlags(Qt::FramelessWindowHint);

    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(145,145,145)));
    ui->setupUi(this);
    ui->comboBox->addItem(tr("管理员"));
    ui->comboBox->addItem(tr("库管员"));
    ui->comboBox->addItem(tr("主管"));

    dbshow();


}

usermanagement::~usermanagement()
{
    delete ui;
}
void usermanagement::dbshow()
{
    bool query_OK=0;
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
    QSqlQuery query;
    //   QString yonghu,mima,juese,shengfengzheng,zhiwen,renlianshibie;
    query_OK= query.exec("create table use(yonghu vchar primary key,mima vchar ,juese vchar ,shengfengzheng vchar ,zhiwen vchar ,renlianshibie vchar )");
    if(query_OK)
    {
        qDebug()<< "create table success!";
    }
    else
    {
        qDebug()<< "create table fail!"  << db.lastError();

    }

    model = new QSqlQueryModel(this);

    QString Qfind;
    Qfind="SELECT * FROM use";


    model->setQuery(Qfind);
    model->setHeaderData(0,Qt::Horizontal,tr("用户名"));
    model->setHeaderData(1,Qt::Horizontal,tr("密码"));
    model->setHeaderData(2,Qt::Horizontal,tr("角色"));
    model->setHeaderData(3,Qt::Horizontal,tr("身份证"));
    model->setHeaderData(4,Qt::Horizontal,tr("指纹"));
    model->setHeaderData(5,Qt::Horizontal,tr("人脸数据"));
    ui->tableView->setModel(model);
    //db.close();
}
void usermanagement::on_pushButton_6_clicked()//新增按钮事件
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
    //   QString yonghu,mima,juese,shengfengzheng,zhiwen,renlianshibie;
    yonghu              =ui->lineEdit_2->text();
    mima                =ui->lineEdit_3->text();
    juese               =ui->comboBox->currentText();
    QSqlQuery query;
    QString insert_buf;
    insert_buf=QObject::tr("insert into use values('%1','%2','%3','%4','%5','%6')").arg(yonghu,mima,juese,shengfengzheng,zhiwen,renlianshibie);
    //qDebug()<<insert_buf;

    if(yonghu.isEmpty() || mima.isEmpty() || juese.isEmpty())
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

    }

    dbshow();
    //usedb.close();

}

void usermanagement::on_pushButton_5_clicked()
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

    int _row=ui->tableView->currentIndex().row();
    if(_row==-1){
        return;
    }
    QModelIndex index = model->index(_row,0);
    QString nr = model->data(index).toString();
    QSqlQuery query(db);
    qDebug()<<nr;
    QString insert_buf=QObject::tr("delete from use where yonghu = %1").arg(nr);
    qDebug()<<insert_buf;



    query.prepare(QString("delete from use where yonghu = ?"));
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
