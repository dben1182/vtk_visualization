#include "DataConversion.hpp"

#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>

vtkSmartPointer<vtkPolyData> DataConversion::create_poly_data(const std::vector<Point>& points)
{
    // Create the points
    auto vtkPts = vtkSmartPointer<vtkPoints>::New();

    //Create Intensity Array
    auto vertices = vtkSmartPointer<vtkCellArray>::New();
    auto intensity = vtkSmartPointer<vtkFloatArray>::New();
    intensity->SetName("Intensity");

    for (const Point& p : points)
    {
        const vtkIdType id = vtkPts->InsertNextPoint(p.x, p.y, p.z);
        vertices->InsertNextCell(1, &id);
        intensity->InsertNextValue(p.Intensity);
    }

    auto polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(vtkPts);
    polyData->SetVerts(vertices);
    polyData->GetPointData()->SetScalars(intensity);
    return polyData;
}
