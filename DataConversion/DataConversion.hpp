#ifndef DATACONVERSION_HPP
#define DATACONVERSION_HPP


#include <vector>
#include <vtkSmartPointer.h>
#include "Point.hpp"


class vtkPolyData;

namespace DataConversion {

// Point cloud: one vertex cell per Point, Intensity stored as the active point scalars.
vtkSmartPointer<vtkPolyData> create_poly_data(const std::vector<Point>& points);

}

#endif
