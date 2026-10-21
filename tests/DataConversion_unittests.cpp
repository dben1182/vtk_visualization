#include "DataConversion.hpp"

#include "testData.hpp"

#include <gtest/gtest.h>

TEST(TestDataExists, CreatingTestDataResultsInNonEmptyVector)
{
    auto points = TestData::testData1();
    ASSERT_FALSE(points.empty());
}


