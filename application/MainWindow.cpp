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

void MainWindow::setup_vtk_pipeline()
{
  const double intensityCutoffThreshold = 254;

  auto cloud = DataConversion::create_poly_data(TestData::testData1());
  auto cloudActor = Visualization::create_threshold_actor(cloud, intensityCutoffThreshold);

  mRenderer = vtkSmartPointer<vtkRenderer>::New();
  mRenderer->AddActor(cloudActor);

  auto window = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
  window->AddRenderer(mRenderer);

  mQVtkWidget->setRenderWindow(window);
  mRenderer->ResetCamera();
}
