#include <gtest/gtest.h>
#include <stdexcept>

#include "largestNo.h"

TEST(LargestNumber, WhenNonEmptyArrayIsPassed_ReturnsLargestNumber)
{
    int array[] = {1, 2, 3, 4, 5, 6, 7};
    int largestNumber = getLargestNumber(array, 7);

    EXPECT_EQ(largestNumber, 7);
}

TEST(LargestNumber, WhenEmptyArrayIsPassed_ThrowsException)
{
    int array[] = {};

    EXPECT_THROW(
        {
            getLargestNumber(array, 0);
        },
        std::runtime_error);
}
