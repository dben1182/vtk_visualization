#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DataConversion.hpp"
#include "Visualization.hpp"
#include "testData.hpp"

#include <vtkActor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPointGaussianMapper.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>
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
  // Update the cutoff threshold label with the new value
  ui->cutoff_threshold_label->setText(QString("cutoff threshold: %1").arg(value));

  // Update the threshold filter with the new value
  if (!mThresholdFilter)
    return; // If the threshold filter is not initialized, do nothing

  // Set the new upper threshold for the filter
  mThresholdFilter->SetUpperThreshold(static_cast<double>(value));
  mQVtkWidget->renderWindow()->Render();
}

void MainWindow::on_opacity_slider_valueChanged(int value)
{
  ui->opacity_label->setText(QString("opacity: %1%").arg(value));

  if (!mCloudActor)
    return;

  Visualization::set_cloud_opacity(mCloudActor, value / 100.0);
  mQVtkWidget->renderWindow()->Render();
}

void MainWindow::on_point_size_slider_valueChanged(int value)
{
  ui->point_size_label->setText(QString("splat size: %1%").arg(value));

  if (!mCloudActor)
    return;

  auto mapper = vtkPointGaussianMapper::SafeDownCast(mCloudActor->GetMapper());
  mapper->SetScaleFactor(value / 100.0 * kMaxSplatRadius);
  mQVtkWidget->renderWindow()->Render();
}

void MainWindow::on_reset_button_clicked()
{
  // Setting the sliders emits valueChanged, which updates labels and the render
  ui->cutoff_threshold_slider->setValue(kDefaultCutoffThreshold);
  ui->opacity_slider->setValue(kDefaultOpacityPercent);
  ui->point_size_slider->setValue(kDefaultPointSize);
}

void MainWindow::setup_vtk_pipeline()
{
  const int intensityCutoffThreshold = kDefaultCutoffThreshold;
  const double opacity = kDefaultOpacityPercent / 100.0;
  const int pointSize = kDefaultPointSize;

  auto cloud = DataConversion::create_poly_data(TestData::testData2());
  mCloudActor = Visualization::create_gaussian_cloud_actor(cloud, intensityCutoffThreshold, &mThresholdFilter,
                                                           opacity, pointSize / 100.0 * kMaxSplatRadius);

  mRenderer = vtkSmartPointer<vtkRenderer>::New();
  mRenderer->AddActor(mCloudActor);

  auto window = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
  window->AddRenderer(mRenderer);

  mQVtkWidget->setRenderWindow(window);
  mRenderer->ResetCamera();

  ui->cutoff_threshold_slider->setRange(0, 255);
  ui->cutoff_threshold_slider->setValue(intensityCutoffThreshold);

  ui->opacity_slider->setRange(0, 100);
  ui->opacity_slider->setValue(static_cast<int>(opacity * 100));

  ui->point_size_slider->setRange(1, 100);
  ui->point_size_slider->setValue(pointSize);
}
