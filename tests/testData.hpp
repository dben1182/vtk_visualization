#ifndef TESTDATA_HPP
#define TESTDATA_HPP

#include <vtkSmartPointer.h>

class vtkImageData;

namespace TestData {

// 100 x 100 x 1 plane; intensity equals the x index.
vtkSmartPointer<vtkImageData> testData1();

// 100 x 100 x 100 volume of identical planes; intensity equals the x index.
vtkSmartPointer<vtkImageData> testData2();

}

#endif
