#include "DataConversion.hpp"

#include "testData.hpp"

vtkSmartPointer<vtkImageData> DataConversion::create_image_data()
{
    return TestData::testData1();
}
