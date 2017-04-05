/****************************************************************************\
 * Copyright (C) 2017 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QVTKWidget.h>

// Forward Qt class declarations
namespace Ui {
  class MainWindow;
}

/**
 * [MainWindow description]
 * @see http://www.vtk.org/Wiki/VTK/Examples/Cxx/Qt/RenderWindowUISingleInheritance
 * @param  parent [description]
 * @return        [description]
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    virtual void slotExit();
    void slotRender();

private slots:
    void on_pushButtonInit_clicked();

    void on_pushButtonPreview_clicked();

    void on_pushButtonStart_clicked();

    void on_pushButtonMesh_clicked();

    void on_checkBoxTrackingPyramid_stateChanged(int arg1);

    void on_checkBoxFlexx_stateChanged(int arg1);

    void on_sliderResolution_valueChanged(int value);

    void on_sliderSize_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QTimer* render_timer;
};

#endif // MAINWINDOW_H
