#include "fileexport.h"
#include "ui_fileexport.h"

fileexport::fileexport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fileexport)
{
    setWindowFlags(Qt::FramelessWindowHint);

    setAutoFillBackground(true);//必须有这条语句
    setPalette(QPalette(QColor(150,50,100)));
    ui->setupUi(this);
}

fileexport::~fileexport()
{
    delete ui;
}
