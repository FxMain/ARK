#include "inventory.h"
#include "ui_inventory.h"

inventory::inventory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inventory)
{
    setWindowFlags(Qt::FramelessWindowHint);

    setAutoFillBackground(true);//必须有这条语句

    setPalette(QPalette(QColor(50,50,50)));
    ui->setupUi(this);
}

inventory::~inventory()
{
    delete ui;
}
