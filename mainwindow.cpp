/****************************************************************************\
 * Copyright (C) 2017 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#include "mainwindow.h"

// This is included here because it is forward declared in
// mainwindow.h
#include "ui_mainwindow.h"

#include <scandy.h>
#include <scandy/core/IScandyCore.h>
#include <scandy_license.h>

#include <vtkCommand.h>
#include <vtkCallbackCommand.h>

#include <iostream>

using namespace scandy::core;

std::shared_ptr<IScandyCore> scandycore;

void test_callback(vtkObject*, unsigned long eid, void* clientdata, void *calldata) {
  std::cout << "vtk render callback" << std::endl;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
  render_timer = nullptr;
  ui = new Ui::MainWindow;
  ui->setupUi(this);

  // output scandy core version
  int major, minor, patch;
  scandy::core::getVersion(major, minor, patch);
  std::cout << "Scandy Core Version: " << major << "." << minor << "." << patch << std::endl;

  // instantiate scandy core
  auto window_size = ui->qvtkWidget->size();
  scandycore = IScandyCore::factoryCreate(
    window_size.width(),
    window_size.height(),
    1,
    1,
    ui->qvtkWidget->GetRenderWindow(),
    dynamic_cast<vtkRenderWindowInteractor*>(ui->qvtkWidget->GetInteractor()));

  // We need to set the ScandyCore license to our internal license
  scandycore->setLicense(scandy_core_license);
  auto status = scandycore->setLicense(scandy_core_license);
  if(status != Status::SUCCESS) {
    std::cerr << "failed to validate the Scandy Core license. SLAM features will not be enabled" << std::endl;
  }

  // debug windows are not supported in qtvtk
  //scandycore->setEnableTrackingDebug(true);

  // set some callbacks
  vtkSmartPointer<vtkCallbackCommand> testCallback = vtkSmartPointer<vtkCallbackCommand>::New();
  testCallback->SetCallback(test_callback);
  ui->qvtkWidget->GetInteractor()->AddObserver(vtkCommand::RenderEvent, testCallback);

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

void MainWindow::slotRender()
{
  if(scandycore->getScanState() == ScanState::NONE) {
    return;
  }
  for(auto r: scandycore->getVisualizer()->m_viewports) {
    r->render();
  }
  ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_pushButtonInit_clicked()
{
  scandy::core::Status status;
  if(render_timer != nullptr) {
    render_timer->stop();
    delete render_timer;
    render_timer = nullptr;
  }
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

    auto scan_state = scandycore->getScanState();
    if(scan_state != scandy::core::ScanState::VIEWING) {
      scandycore->uninitializeScanner();
    }
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

      // get scan options

      // setup timer to update window every 25ms
      // remember vtk must be update in main ui thread
      if(render_timer != nullptr) {
        render_timer->stop();
        delete render_timer;
      }
      render_timer = new QTimer(this);
      connect(render_timer, SIGNAL(timeout()), this, SLOT(slotRender()));
      render_timer->start(25);
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

void MainWindow::on_pushButtonMesh_clicked()
{
  auto fileName = QFileDialog::getOpenFileName(
    this,
    tr("Open Mesh file"),
    QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
    tr("Mesh file (*.ply *.obj *.stl)"));

  auto status = scandycore->loadMesh(fileName.toStdString());
  if(status != scandy::core::Status::SUCCESS) {
    QMessageBox msgBox;
    msgBox.setText("ERROR: could not load mesh");
    msgBox.exec();
  }
  ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_checkBoxTrackingPyramid_stateChanged(int arg1)
{
    QMessageBox msgBox;
    msgBox.setText("ERROR: ScandyCore QtVTK does not support viewing pyramid windows");
    msgBox.exec();
}

void MainWindow::on_checkBoxFlexx_stateChanged(int arg1)
{
  // value checked in on_pushButtonInit_clicked
}

void MainWindow::on_sliderResolution_valueChanged(int value)
{
  if(scandycore) {
    ScanResolution new_resolution;
    auto scan_resolutions = scandycore->getAvailableScanResolutions();
    if(scan_resolutions.size() >= value ) {
        new_resolution = scan_resolutions[value];
    }
    auto status = scandycore->setResolution(new_resolution);
    if(status != scandy::core::Status::SUCCESS) {
      QMessageBox msgBox;
      msgBox.setText("ERROR: could not set resolution");
      msgBox.exec();
    }
  }
}

void MainWindow::on_sliderSize_valueChanged(int value)
{
  if(scandycore) {
    auto status = scandycore->setScanSize(scandy::utilities::scandy_make_float3(value, value, value));
    if(status != scandy::core::Status::SUCCESS) {
      QMessageBox msgBox;
      msgBox.setText("ERROR: could not set scan size");
      msgBox.exec();
    }
  }
}
