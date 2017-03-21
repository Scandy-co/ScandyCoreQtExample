#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <thread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->do_thing_2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_do_thing_1_clicked()
{
    ui->do_thing_1->hide();
    ui->do_thing_2->show();
}

void MainWindow::on_do_thing_2_clicked()
{
    ui->do_thing_1->show();
    ui->do_thing_2->hide();
}
