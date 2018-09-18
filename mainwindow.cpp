#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cd.h"
#include "newdoc.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button_DL_clicked()
{
    cd d;
    this->hide();//隐藏主窗口
    d.exec();


}

void MainWindow::on_Button_TC_clicked()
{
    qApp->quit();

}
