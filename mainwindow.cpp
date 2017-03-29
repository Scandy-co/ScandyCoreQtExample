#include "mainwindow.h"

// This is included here because it is forward declared in
// mainwindow.h
#include "ui_mainwindow.h"

#include <scandy.h>
#include <scandy/core/IScandyCore.h>
#include <scandy/core/visualizer/TestViewport.h>

#include <iostream>

using namespace scandy::core;

std::shared_ptr<IScandyCore> scandycore;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
  ui = new Ui::MainWindow;
  ui->setupUi(this);

  // setup window size
  //QSizePolicy size_policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  //QSizePolicy size_policy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  //size_policy.setHorizontalStretch(0);
  //size_policy.setVerticalStretch(0);
  //ui->centralwidget->setSizePolicy(size_policy);
  //ui->qvtkWidget->setSizePolicy(size_policy);
  auto window_size = ui->qvtkWidget->size();

  // output scandy core version
  int major, minor, patch;
  scandy::core::getVersion(major, minor, patch);
  std::cout << "Scansy Core Version: " << major << "." << minor << "." << patch << std::endl;

  // instantiate scandy core
  scandycore = IScandyCore::factoryCreate(window_size.width(), window_size.height(), 1, 1, ui->qvtkWidget->GetRenderWindow());

  // Set up action signals and slots
  connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));

  // disable push buttons
  ui->pushButtonInit->setEnabled(true);
  ui->pushButtonPreview->setEnabled(false);
  ui->pushButtonStart->setEnabled(false);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::slotExit()
{
  qApp->exit();
}

void MainWindow::on_pushButtonInit_clicked()
{
  scandy::core::Status status;
  if(ui->checkBoxFlexx->isChecked()) {
    status = scandycore->initializeScanner(scandy::core::ScannerType::PICO_FLEXX);
    if(status != scandy::core::Status::SUCCESS) {
      QMessageBox msgBox;
      msgBox.setText("ERROR: could not initialize ScandyCore");
      msgBox.exec();
    }
  }
  else {
    auto fileName = QFileDialog::getOpenFileName(
      this,
      tr("Open Royale or Scandy file"),
      QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
      tr("3D Depth Streams (*.rrf *.spb *.spb2)"));

    status = scandycore->initializeScanner(scandy::core::ScannerType::FILE, fileName.toStdString());
    if(status != scandy::core::Status::SUCCESS) {
      QMessageBox msgBox;
      msgBox.setText("ERROR: could not initialize ScandyCore");
      msgBox.exec();
    }
  }
  if(status == scandy::core::Status::SUCCESS) {
    ui->pushButtonPreview->setEnabled(true);
    ui->pushButtonStart->setEnabled(false);
  }
  else {
    ui->pushButtonPreview->setEnabled(false);
    ui->pushButtonStart->setEnabled(false);
  }
}

void MainWindow::on_pushButtonPreview_clicked()
{
  auto scan_state = scandycore->getScanState();
  if(scan_state == scandy::core::ScanState::INITIALIZED) {
    auto status = scandycore->startPreview();
    if(status == scandy::core::Status::SUCCESS) {
      ui->pushButtonPreview->setEnabled(false);
      ui->pushButtonStart->setEnabled(true);
    }
    else {
      ui->pushButtonPreview->setEnabled(false);
      ui->pushButtonStart->setEnabled(false);
      QMessageBox msgBox;
      msgBox.setText("ERROR: could not start ScandyCore preview");
      msgBox.exec();
    }
  }
  else {
    ui->pushButtonPreview->setEnabled(false);
    ui->pushButtonStart->setEnabled(false);
    QMessageBox msgBox;
    msgBox.setText("ERROR: ScandyCore must be initialized before preview");
    msgBox.exec();
  }
}

void MainWindow::on_pushButtonStart_clicked()
{
  scandy::core::Status status;
  auto text = ui->pushButtonStart->text();

  if(text == "Start Scan") {
    status = scandycore->startScanning();

    if(status == scandy::core::Status::SUCCESS) {
      ui->pushButtonStart->setText("Stop Scan");
    }
    else {
      ui->pushButtonPreview->setEnabled(false);
      ui->pushButtonStart->setEnabled(false);
      QMessageBox msgBox;
      msgBox.setText("ERROR: could not start ScandyCore scanning");
      msgBox.exec();
    }
  }
  else if(text == "Stop Scan") {
    status = scandycore->stopScanning();

    if(status == scandy::core::Status::SUCCESS) {
      ui->pushButtonStart->setText("Start Scan");
    }
    else {
      ui->pushButtonPreview->setEnabled(false);
      ui->pushButtonStart->setEnabled(false);
      QMessageBox msgBox;
      msgBox.setText("ERROR: could not stop ScandyCore scanning");
      msgBox.exec();
    }
  }
}
