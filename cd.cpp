#include "cd.h"
#include "ui_cd.h"

QSqlQuery query;
QSqlDatabase db;
QSqlQueryModel *model;
extern QString LandingRole;
cd::cd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cd)
{
    //git
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(140,140,140)));

    usenewdoc=new newdoc(this);
    usearchivesdoc=new archivesdoc(this);
    useoutbound=new outbound(this);
    useinventory=new inventory(this);

    usefileexport=new fileexport(this);
    usestatistical=new statistical(this);
    useusermanagement=new usermanagement(this);
    useorganizationmangement=new organizationmangement(this);

    usenewdoc->hide();
    usearchivesdoc->hide();
    useoutbound->hide();
    useinventory->hide();
    usefileexport->hide();
    usestatistical->hide();
    useusermanagement->hide();
    useorganizationmangement->hide();


    ui->setupUi(this);

    ui->pushButton_inventory->hide();
    ui->pushButton_export->hide();
    ui->pushButton_OrganizationMangement->hide();
    ui->pushButton_Statistical->hide();
     qDebug() <<"登陆角色:"+LandingRole;

}

cd::~cd()
{
    delete ui;
    db.close();
}
void cd::resizeEvent(QResizeEvent *event){

    int WM=ui->pushButton_newdoc->x()+ui->pushButton_newdoc->width();
    //WM=WM+0.04*WM;
    int HM=height()*0.04;

    int WS=width()-(ui->pushButton_newdoc->x()+ui->pushButton_newdoc->width());
    WM=WM+0.02*WS;
    WS=WS*(1.0-0.04);
    int HS=height()*(1.0-0.08);

    usenewdoc->move(WM,HM);             //移动位置
    usenewdoc->setFixedSize(WS,HS);  //设置窗体大小

    usearchivesdoc->move(WM,HM);             //移动位置
    usearchivesdoc->setFixedSize(WS,HS);  //设置窗体大小

    useoutbound->move(WM,HM);             //移动位置
    useoutbound->setFixedSize(WS,HS);  //设置窗体大小

    useinventory->move(WM,HM);             //移动位置
    useinventory->setFixedSize(WS,HS);  //设置窗体大小

    usefileexport->move(WM,HM);             //移动位置
    usefileexport->setFixedSize(WS,HS);  //设置窗体大小

    usestatistical->move(WM,HM);             //移动位置
    usestatistical->setFixedSize(WS,HS);  //设置窗体大小

    useusermanagement->move(WM,HM);             //移动位置
    useusermanagement->setFixedSize(WS,HS);  //设置窗体大小

    useorganizationmangement->move(WM,HM);             //移动位置
    useorganizationmangement->setFixedSize(WS,HS);  //设置窗体大小


    QWidget::resizeEvent(event);
}
void cd::on_pushButton_newdoc_clicked()// 1
{
    usenewdoc->show();
    usearchivesdoc->hide();
    useoutbound->hide();
    useinventory->hide();
    usefileexport->hide();
    usestatistical->hide();
    useusermanagement->hide();
    useorganizationmangement->hide();
}

void cd::on_pushButton_archiveManagement_clicked()// 2
{
    usenewdoc->hide();
    usearchivesdoc->show();
    useoutbound->hide();
    useinventory->hide();
    usefileexport->hide();
    usestatistical->hide();
    useusermanagement->hide();
    useorganizationmangement->hide();
}

void cd::on_pushButton_outbound_clicked()// 3
{
    usenewdoc->hide();
    usearchivesdoc->hide();
    useoutbound->show();
    useinventory->hide();
    usefileexport->hide();
    usestatistical->hide();
    useusermanagement->hide();
    useorganizationmangement->hide();
}

void cd::on_pushButton_inventory_clicked()// 4
{
    usenewdoc->hide();
    usearchivesdoc->hide();
    useoutbound->hide();
    useinventory->show();
    usefileexport->hide();
    usestatistical->hide();
    useusermanagement->hide();
    useorganizationmangement->hide();
}

void cd::on_pushButton_export_clicked()// 5
{
    usenewdoc->hide();
    usearchivesdoc->hide();
    useoutbound->hide();
    useinventory->hide();
    usefileexport->show();
    usestatistical->hide();
    useusermanagement->hide();
    useorganizationmangement->hide();
}

void cd::on_pushButton_Statistical_clicked()// 6
{
    usenewdoc->hide();
    usearchivesdoc->hide();
    useoutbound->hide();
    useinventory->hide();
    usefileexport->hide();
    usestatistical->show();
    useusermanagement->hide();
    useorganizationmangement->hide();
}

void cd::on_pushButton_userManagement_clicked()// 7
{
    if(LandingRole!="管理员")
    {
        QMessageBox::information(this,"警告!","您不是管理员！");
        return;
    }
    usenewdoc->hide();
    usearchivesdoc->hide();
    useoutbound->hide();
    useinventory->hide();
    usefileexport->hide();
    usestatistical->hide();
    useusermanagement->show();
    useorganizationmangement->hide();
}

void cd::on_pushButton_OrganizationMangement_clicked()// 8
{
    usenewdoc->hide();
    usearchivesdoc->hide();
    useoutbound->hide();
    useinventory->hide();
    usefileexport->hide();
    usestatistical->hide();
    useusermanagement->hide();
    useorganizationmangement->show();
}
