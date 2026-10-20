#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DataConversion.hpp"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkImageProperty.h>
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
  vtkSmartPointer<vtkImageData> image = DataConversion::create_image_data();

  vtkSmartPointer<vtkImageActor> imageActor =
    vtkSmartPointer<vtkImageActor>::New();
  imageActor->SetInputData(image);
  imageActor->GetProperty()->SetColorWindow(255.0);
  imageActor->GetProperty()->SetColorLevel(127.5);

  mRenderer = vtkSmartPointer<vtkRenderer>::New();
  mRenderer->AddActor(imageActor);

  vtkSmartPointer<vtkGenericOpenGLRenderWindow> window =
    vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
  window->AddRenderer(mRenderer);

  mQVtkWidget->setRenderWindow(window);
  mRenderer->ResetCamera();
}
