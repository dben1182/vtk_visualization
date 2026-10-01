#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkSmartPointer.h>
#include <vtkConeSource.h>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  void setup_vtk_pipeline();
  Ui::MainWindow *ui;
  QVTKOpenGLNativeWidget* mQVtkWidget;

  vtkSmartPointer<vtkConeSource> mConeSource;
  vtkSmartPointer<vtkRenderer> mRenderer;
};

#endif // MAINWINDOW_H
