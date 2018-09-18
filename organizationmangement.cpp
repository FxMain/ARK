#include "organizationmangement.h"
#include "ui_organizationmangement.h"

organizationmangement::organizationmangement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::organizationmangement)
{
    setWindowFlags(Qt::FramelessWindowHint);

    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(1,250,100)));
    ui->setupUi(this);
}

organizationmangement::~organizationmangement()
{
    delete ui;
}
