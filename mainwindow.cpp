#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <scandy.h>
#include <scandy/core/logging.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->do_thing_2->hide();
    int major, minor, patch;
    scandy::core::getVersion(major, minor, patch);
    scandy::core::logging::debug("hello from scandy!\nVersion: %d.%d.%d", major, minor, patch);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_do_thing_1_clicked()
{
    ui->do_thing_1->hide();
    ui->do_thing_2->show();
    scandy::core::logging::info("did thing1!");
}

void MainWindow::on_do_thing_2_clicked()
{
    ui->do_thing_1->show();
    ui->do_thing_2->hide();
    scandy::core::logging::warn("did thing2!");
}
