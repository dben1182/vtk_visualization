#include "testData.hpp"

#include <vtkImageData.h>

#include <algorithm>

namespace {

vtkSmartPointer<vtkImageData> createPlanes(int depth)
{
    constexpr int width = 100;
    constexpr int height = 100;

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

vtkSmartPointer<vtkImageData> TestData::testData1()
{
    return createPlanes(1);
}

vtkSmartPointer<vtkImageData> TestData::testData2()
{
    return createPlanes(100);
}
