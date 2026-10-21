#ifndef VISUALIZATION_HPP
#define VISUALIZATION_HPP

#include <vtkSmartPointer.h>

class vtkActor;
class vtkPolyData;

namespace Visualization {

// vtkThresholdPoints keeps points with Intensity >= intensityCutoffThreshold.
vtkSmartPointer<vtkActor> create_threshold_actor(vtkPolyData* cloud, double intensityCutoffThreshold);

}

#endif
