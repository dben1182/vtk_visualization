#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DataConversion.hpp"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkImageData.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
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

  // One vertex cell per voxel so VTK draws points instead of a filled image.
  auto points = vtkSmartPointer<vtkPoints>::New();
  auto vertices = vtkSmartPointer<vtkCellArray>::New();
  const vtkIdType numPoints = image->GetNumberOfPoints();
  points->SetNumberOfPoints(numPoints);
  for (vtkIdType i = 0; i < numPoints; ++i)
  {
    points->SetPoint(i, image->GetPoint(i));
    vertices->InsertNextCell(1, &i);
  }

  auto cloud = vtkSmartPointer<vtkPolyData>::New();
  cloud->SetPoints(points);
  cloud->SetVerts(vertices);
  cloud->GetPointData()->SetScalars(image->GetPointData()->GetScalars());

  auto lut = vtkSmartPointer<vtkLookupTable>::New();
  lut->SetRange(0.0, 255.0);
  lut->SetValueRange(0.0, 1.0);
  lut->SetSaturationRange(0.0, 0.0);
  lut->Build();

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(cloud);
  mapper->SetLookupTable(lut);
  mapper->SetScalarRange(0.0, 255.0);

  auto cloudActor = vtkSmartPointer<vtkActor>::New();
  cloudActor->SetMapper(mapper);
  cloudActor->GetProperty()->SetPointSize(3.0);

  mRenderer = vtkSmartPointer<vtkRenderer>::New();
  mRenderer->AddActor(cloudActor);

  vtkSmartPointer<vtkGenericOpenGLRenderWindow> window =
    vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
  window->AddRenderer(mRenderer);

  mQVtkWidget->setRenderWindow(window);
  mRenderer->ResetCamera();
}
