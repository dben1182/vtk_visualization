#ifndef TESTDATA_HPP
#define TESTDATA_HPP

#include "Point.hpp"

#include <vector>

namespace TestData {

// 3 planes (z = 0, 1, 2) of 3x3 points with random Intensity in [0, 255].
std::vector<Point> testData1();

// Defaults for testData2().
constexpr int kCubeSize = 50;
constexpr double kViaRadius = 8;      // via diameter 16 px
constexpr double kRingWidth = 1.5;       // Gaussian sigma of the via-wall ring
constexpr double kFalloffLength = 4.0;   // exponential decay length of surface diffusion
constexpr double kPeakIntensity = 255.0;
constexpr double kBaseMaxIntensity = 128.0;  // every voxel starts uniform random in [0, this]
constexpr int kScatterDepth = 8;             // planes within this distance of a surface get extra scatter
constexpr double kScatterDecayLength = 2.0;  // scatter probability decays as exp(-(d-1)/this)
constexpr double kScatterMaxProbability = 0.5;  // fraction of voxels scattered on the plane next to a surface

// 50x50x50 simulated confocal scan. Every voxel is first given a random intensity in
// [0, baseMaxIntensity]. Planes within scatterDepth of a surface then get bright random
// scatter outside the via, strongest next to the surface and decaying quickly with depth.
// Surfaces (z = 0, 49) are then overwritten: bright outside a
// central cylindrical through-via and 0 inside it. Interior planes take the max of the
// random base, a bright ring at the via wall, and surface-diffusion glow decaying into
// the interior. Intensity is in [0, 255]; points are ordered z-major, then y, then x.
std::vector<Point> testData2(int cubeSize = kCubeSize,
                             double viaRadius = kViaRadius,
                             double ringWidth = kRingWidth,
                             double falloffLength = kFalloffLength,
                             double peakIntensity = kPeakIntensity,
                             double baseMaxIntensity = kBaseMaxIntensity,
                             int scatterDepth = kScatterDepth,
                             double scatterDecayLength = kScatterDecayLength,
                             double scatterMaxProbability = kScatterMaxProbability);

}

#endif
