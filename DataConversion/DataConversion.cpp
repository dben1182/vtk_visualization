#include "DataConversion.hpp"

#include <vtkImageData.h>

#include <algorithm>

namespace {

vtkSmartPointer<vtkImageData> testData()
{
    constexpr int width = 100;
    constexpr int height = 100;
    constexpr int depth = 1;

    auto image = vtkSmartPointer<vtkImageData>::New();
    image->SetDimensions(width, height, depth);
    image->SetOrigin(0.0, 0.0, 0.0);
    image->SetSpacing(1.0, 1.0, 1.0);
    image->AllocateScalars(VTK_UNSIGNED_CHAR, 1);

    for (int z = 0; z < depth; ++z)
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                image->SetScalarComponentFromDouble(
                    x, y, z, 0, std::min(x, 255));
            }
        }
    }

    return image;
}

}

vtkSmartPointer<vtkImageData> DataConversion::create_image_data()
{
    return testData();
}