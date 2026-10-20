#include "DataConversion.hpp"

#include <gtest/gtest.h>

#include <vtkImageData.h>

TEST(DataConversionTest, CreatesSinglePlaneImageWithIntensityBasedOnXPosition)
{
    constexpr int expectedDimensions[3] = {100, 100, 1};
    constexpr int sampleX = 37;
    constexpr int sampleY = 42;
    constexpr int sampleZ = 0;

    const auto image = DataConversion::create_image_data();

    ASSERT_NE(image, nullptr);

    int dimensions[3];
    image->GetDimensions(dimensions);
    EXPECT_EQ(dimensions[0], expectedDimensions[0]);
    EXPECT_EQ(dimensions[1], expectedDimensions[1]);
    EXPECT_EQ(dimensions[2], expectedDimensions[2]);
    EXPECT_EQ(image->GetScalarComponentAsDouble(sampleX, sampleY, sampleZ, 0), sampleX);
}
