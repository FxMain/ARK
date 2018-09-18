#include "statistical.h"
#include "ui_statistical.h"

statistical::statistical(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistical)
{
    setWindowFlags(Qt::FramelessWindowHint);

    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(250,250,250)));
    ui->setupUi(this);
}

statistical::~statistical()
{
    delete ui;
}
