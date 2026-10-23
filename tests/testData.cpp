#include "testData.hpp"

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
