#include "testData.hpp"

#include <algorithm>
#include <cmath>
#include <random>

std::vector<Point> TestData::testData1()
{
    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<double> intensity(0.0, 255.0);

    std::vector<Point> points;
    for (int z = 0; z < 50; ++z)
    {
        for (int y = 0; y < 50; ++y)
        {
            for (int x = 0; x < 50; ++x)
            {
                Point p;
                p.x = x;
                p.y = y;
                p.z = z;
                p.Intensity = intensity(rng);
                points.push_back(p);
            }
        }
    }
    return points;
}

std::vector<Point> TestData::testData2(int cubeSize,
                                       double viaRadius,
                                       double ringWidth,
                                       double falloffLength,
                                       double peakIntensity,
                                       double baseMaxIntensity,
                                       int scatterDepth,
                                       double scatterDecayLength,
                                       double scatterMaxProbability)
{
    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<double> baseIntensity(0.0, baseMaxIntensity);

    const double center = (cubeSize - 1) / 2.0;
    const int lastPlane = cubeSize - 1;

    // Every voxel starts with a random base intensity; the model below overrides it.
    std::vector<Point> points;
    points.reserve(static_cast<size_t>(cubeSize) * cubeSize * cubeSize);
    for (int z = 0; z < cubeSize; ++z)
    {
        for (int y = 0; y < cubeSize; ++y)
        {
            for (int x = 0; x < cubeSize; ++x)
            {
                Point p;
                p.x = x;
                p.y = y;
                p.z = z;
                p.Intensity = static_cast<float>(baseIntensity(rng));
                points.push_back(p);
            }
        }
    }

    // Scatter near the top/bottom surfaces: bright random voxels whose probability decays quickly with depth.
    std::uniform_real_distribution<double> unit(0.0, 1.0);
    std::uniform_real_distribution<double> scatterIntensity(baseMaxIntensity, peakIntensity);
    for (int z = 1; z < cubeSize - 1; ++z)
    {
        const int distToSurface = std::min(z, lastPlane - z);
        if (distToSurface > scatterDepth)
        {
            continue;
        }
        const double probability = scatterMaxProbability * std::exp(-(distToSurface - 1) / scatterDecayLength);
        for (int y = 0; y < cubeSize; ++y)
        {
            for (int x = 0; x < cubeSize; ++x)
            {
                if (std::hypot(x - center, y - center) >= viaRadius && unit(rng) < probability)
                {
                    points[(static_cast<size_t>(z) * cubeSize + y) * cubeSize + x].Intensity =
                        static_cast<float>(scatterIntensity(rng));
                }
            }
        }
    }

    for (int z = 0; z < cubeSize; ++z)
    {
        const bool isSurface = (z == 0 || z == lastPlane);
        const double distToSurface = std::min(z, lastPlane - z);
        for (int y = 0; y < cubeSize; ++y)
        {
            for (int x = 0; x < cubeSize; ++x)
            {
                const double r = std::hypot(x - center, y - center);
                const bool insideVia = r < viaRadius;
                const double ringDist = r - viaRadius;

                Point& p = points[(static_cast<size_t>(z) * cubeSize + y) * cubeSize + x];
                double value;
                if (isSurface)
                {
                    value = insideVia ? 0.0 : peakIntensity;
                }
                else
                {
                    const double ring = peakIntensity * std::exp(-(ringDist * ringDist) / (2.0 * ringWidth * ringWidth));
                    // Surface glow exists only in material (outside the via) and peaks at the via edge.
                    double diffusion = 0.0;
                    if (!insideVia)
                    {
                        const double radial = std::exp(-ringDist / falloffLength);
                        diffusion = peakIntensity * std::exp(-distToSurface / falloffLength) * radial;
                    }
                    value = std::max({static_cast<double>(p.Intensity), ring, diffusion});
                }
                p.Intensity = static_cast<float>(std::clamp(value, 0.0, 255.0));
            }
        }
    }
    return points;
}
