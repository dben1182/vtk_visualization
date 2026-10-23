#ifndef VISUALIZATION_HPP
#define VISUALIZATION_HPP

#include <vtkSmartPointer.h>

class vtkActor;
class vtkPolyData;
class vtkThresholdPoints;

namespace Visualization {

// Renders the cloud as soft Gaussian blobs (vtkPointGaussianMapper) whose opacity follows Intensity.
// vtkThresholdPoints keeps points with Intensity >= intensityCutoffThreshold.
// If outFilter is provided it receives the threshold filter so the cutoff can be updated later.
// opacity is in [0, 1] and scales the whole cloud; splatRadius is the blob radius in world units
// and can be changed later with vtkPointGaussianMapper::SafeDownCast(actor->GetMapper())->SetScaleFactor().
vtkSmartPointer<vtkActor> create_gaussian_cloud_actor(vtkPolyData* cloud, double intensityCutoffThreshold,
                                                      vtkSmartPointer<vtkThresholdPoints>* outFilter = nullptr,
                                                      double opacity = 1.0, double splatRadius = 1.0);

// Changes the overall cloud opacity (in [0, 1]) of an actor made by create_gaussian_cloud_actor.
// Use this instead of vtkProperty::SetOpacity, which makes the Gaussian mapper disappear below 1.
void set_cloud_opacity(vtkActor* cloudActor, double opacity);

}

#endif
