#include "Visualization.hpp"

#include <vtkActor.h>
#include <vtkLookupTable.h>
#include <vtkPiecewiseFunction.h>
#include <vtkPointGaussianMapper.h>
#include <vtkPolyData.h>
#include <vtkThresholdPoints.h>

vtkSmartPointer<vtkActor> Visualization::create_gaussian_cloud_actor(vtkPolyData* cloud, double intensityCutoffThreshold,
                                                                     vtkSmartPointer<vtkThresholdPoints>* outFilter,
                                                                     double opacity, double splatRadius)
{
    // Step 1: drop every point below the cutoff before it reaches the GPU
    auto threshold = vtkSmartPointer<vtkThresholdPoints>::New();
    threshold->SetInputData(cloud);
    threshold->SetUpperThreshold(intensityCutoffThreshold);
    threshold->SetThresholdFunction(vtkThresholdPoints::THRESHOLD_UPPER);

    // Step 2: intensity -> grayscale color
    auto lut = vtkSmartPointer<vtkLookupTable>::New();
    lut->SetRange(0.0, 255.0);
    lut->SetSaturationRange(0.0, 0.0);
    lut->SetValueRange(0.0, 1.0);
    lut->Build();

    // Step 3: intensity -> per-point opacity, so dim points fade out and bright points form the dense cloud.
    // The overall opacity lives here (the curve's maximum), not in vtkProperty::SetOpacity: an actor opacity
    // below 1 pushes this mapper into VTK's translucent pass, where it draws nothing.
    auto opacityFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();

    // Step 4: draw each remaining point as a soft Gaussian blob instead of a hard dot
    auto mapper = vtkSmartPointer<vtkPointGaussianMapper>::New();
    mapper->SetInputConnection(threshold->GetOutputPort());
    mapper->SetLookupTable(lut);
    mapper->SetScalarRange(0.0, 255.0);
    mapper->SetScaleFactor(splatRadius);
    mapper->SetOpacityArray("Intensity");
    mapper->SetScalarOpacityFunction(opacityFunction);
    mapper->EmissiveOn();

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    set_cloud_opacity(actor, opacity);
    if (outFilter)
        *outFilter = threshold;
    return actor;
}

void Visualization::set_cloud_opacity(vtkActor* cloudActor, double opacity)
{
    auto mapper = vtkPointGaussianMapper::SafeDownCast(cloudActor->GetMapper());
    auto* opacityFunction = mapper->GetScalarOpacityFunction();
    opacityFunction->RemoveAllPoints();
    opacityFunction->AddPoint(0.0, 0.0);
    opacityFunction->AddPoint(255.0, opacity);
}
