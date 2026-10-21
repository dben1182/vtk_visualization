#ifndef TESTDATA_HPP
#define TESTDATA_HPP

#include "Point.hpp"

#include <vector>

namespace TestData {

// 3 planes (z = 0, 1, 2) of 3x3 points with random Intensity in [0, 255].
std::vector<Point> testData1();

}

#endif
