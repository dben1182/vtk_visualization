#include "Visualization.hpp"

#include <vtkActor.h>
#include <vtkLookupTable.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkThresholdPoints.h>

vtkSmartPointer<vtkActor> Visualization::create_threshold_actor(vtkPolyData* cloud, double intensityCutoffThreshold)
{
    auto threshold = vtkSmartPointer<vtkThresholdPoints>::New();
    threshold->SetInputData(cloud);
    threshold->SetUpperThreshold(intensityCutoffThreshold);
    threshold->SetThresholdFunction(vtkThresholdPoints::THRESHOLD_UPPER);

    auto lut = vtkSmartPointer<vtkLookupTable>::New();
    lut->SetRange(0.0, 255.0);
    lut->SetSaturationRange(0.0, 0.0);
    lut->SetValueRange(0.0, 1.0);
    lut->Build();

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(threshold->GetOutputPort());
    mapper->SetLookupTable(lut);
    mapper->SetScalarRange(0.0, 255.0);

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetPointSize(8.0);
    return actor;
}
