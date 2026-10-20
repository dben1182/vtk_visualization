#ifndef DATACONVERSION_HPP
#define DATACONVERSION_HPP

#include <vtkSmartPointer.h>

class vtkImageData;

namespace DataConversion {

vtkSmartPointer<vtkImageData> create_image_data();

}

#endif