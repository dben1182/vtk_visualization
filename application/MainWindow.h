#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkSmartPointer.h>

namespace Ui {
  class MainWindow;
}

class vtkRenderer;
class vtkThresholdPoints;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_cutoff_threshold_slider_valueChanged(int value);

private:
  void setup_vtk_pipeline();
  Ui::MainWindow *ui;
  QVTKOpenGLNativeWidget* mQVtkWidget;

  vtkSmartPointer<vtkRenderer> mRenderer;
  vtkSmartPointer<vtkThresholdPoints> mThresholdFilter;
};

#endif // MAINWINDOW_H
