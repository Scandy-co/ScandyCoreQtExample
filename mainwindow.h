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

private slots:
    void on_pushButtonInit_clicked();

    void on_pushButtonPreview_clicked();

    void on_pushButtonStart_clicked();

    void on_pushButtonMesh_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
