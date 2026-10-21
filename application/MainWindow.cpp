#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DataConversion.hpp"
#include "Visualization.hpp"
#include "testData.hpp"

#include <vtkActor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyData.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkThresholdPoints.h>
MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  mQVtkWidget= new QVTKOpenGLNativeWidget(this);

  QGridLayout* layout = new QGridLayout(ui->frame);
  layout->addWidget(mQVtkWidget, 1, 1);
  ui->frame->setLayout(layout);

  setup_vtk_pipeline();

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_cutoff_threshold_slider_valueChanged(int value)
{
  if (!mThresholdFilter)
    return;

  mThresholdFilter->SetUpperThreshold(static_cast<double>(value));
  mQVtkWidget->renderWindow()->Render();
}

void MainWindow::setup_vtk_pipeline()
{
  const int intensityCutoffThreshold = 200;

  auto cloud = DataConversion::create_poly_data(TestData::testData1());
  auto cloudActor = Visualization::create_threshold_actor(cloud, intensityCutoffThreshold, &mThresholdFilter);

  mRenderer = vtkSmartPointer<vtkRenderer>::New();
  mRenderer->AddActor(cloudActor);

  auto window = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
  window->AddRenderer(mRenderer);

  mQVtkWidget->setRenderWindow(window);
  mRenderer->ResetCamera();

  ui->cutoff_threshold_slider->setRange(0, 255);
  ui->cutoff_threshold_slider->setValue(intensityCutoffThreshold);
}
