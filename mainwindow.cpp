#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <scandy.h>
#include <scandy/core/IScandyCore.h>
#include <scandy/core/visualizer/TestViewport.h>

#include <scandy_license.h>

#include <iostream>

using namespace scandy::core;

std::shared_ptr<IScandyCore> scandycore;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->do_thing_2->hide();
  int major, minor, patch;
  scandy::core::getVersion(major, minor, patch);
  std::cout << "Scandy Core Version: " << major << "." << minor << "." << patch << std::endl;

  scandycore = IScandyCore::factoryCreate(400,400);
  // We need to set the ScandyCore license to our internal license
  auto status = scandycore->setLicense(scandy_core_license);
  if(status != Status::SUCCESS) {
    std::cerr << "failed to validate the Scandy Core license. SLAM features will not be enabled" << std::endl;
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_do_thing_1_clicked()
{
  ui->do_thing_1->hide();
  ui->do_thing_2->show();

  // Get a reference to the ScandyCore Visualizer
  auto viz = scandycore->getVisualizer();
  // Create a scandy::core::TestViewport
  auto viewport = std::make_shared<TestViewport>();
  // Add the test view port to the visualizer
  viz->addViewport(*viewport);
  // Start the visualizer's event loop
  viz->start();
}

void MainWindow::on_do_thing_2_clicked()
{
  // Get a reference to the ScandyCore Visualizer
  auto viz = scandycore->getVisualizer();
  // Stop the visualizer's event loop and join its thread
  viz->stop();
  viz->join();
  // Reset the visualizer
  viz = nullptr;

  // And re-create the visualizer, but this time a random size
  int width = 100+(800 * ((std::rand() % 100 )/ 100.0));
  int height = 100+(800 * ((std::rand() % 100 )/ 100.0));
  scandycore->createVisualizer(width,height);

  // Switch the buttons back around
  ui->do_thing_1->show();
  ui->do_thing_2->hide();
}
