#ifndef VISUALIZATION_HPP
#define VISUALIZATION_HPP

#include <vtkSmartPointer.h>

class vtkActor;
class vtkPolyData;
class vtkThresholdPoints;

namespace Visualization {

// vtkThresholdPoints keeps points with Intensity >= intensityCutoffThreshold.
// If outFilter is provided it receives the threshold filter so the cutoff can be updated later.
vtkSmartPointer<vtkActor> create_threshold_actor(vtkPolyData* cloud, double intensityCutoffThreshold,
                                                 vtkSmartPointer<vtkThresholdPoints>* outFilter = nullptr);

}

#endif
