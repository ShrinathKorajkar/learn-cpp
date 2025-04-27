#include "samePosDiv.h"

#include <gtest/gtest.h>

class CountPositiveDivisorsTest : public ::testing::TestWithParam<std::pair<int, int>>
{
};

TEST_P(CountPositiveDivisorsTest, WhenIntegerIsPassed_ThenReturnTotalDivisorsOfIt)
{
    auto param = GetParam();
    int input = param.first;
    int expected = param.second;
    EXPECT_EQ(countPositiveDivisors(input), expected);
}

INSTANTIATE_TEST_SUITE_P(
    CountPositiveDivisorsTests,
    CountPositiveDivisorsTest,
    ::testing::Values(
        std::make_pair(1, 1),  // 1 has 1 divisor (1)
        std::make_pair(2, 2),  // 2 has 2 divisors (1, 2)
        std::make_pair(3, 2),  // 3 has 2 divisors (1, 3)
        std::make_pair(4, 3),  // 4 has 3 divisors (1, 2, 4)
        std::make_pair(6, 4),  // 6 has 4 divisors (1, 2, 3, 6)
        std::make_pair(12, 6), // 12 has 6 divisors (1, 2, 3, 4, 6, 12)
        std::make_pair(25, 3)  // 25 has 3 divisors (1, 5, 25)
        ));

TEST(PopulateDivisorCountsTest, WhenEmptyDivisorArrayIsPassed_ThenPopulateItWithCorrectDivisorCounts)
{
    int len = 10;
    int divisorCounts[len];
    populateDivisorCounts(divisorCounts, len);

    EXPECT_EQ(divisorCounts[1], 1); // 1 has 1 divisor (1)
    EXPECT_EQ(divisorCounts[2], 2); // 2 has 2 divisors (1, 2)
    EXPECT_EQ(divisorCounts[3], 2); // 3 has 2 divisors (1, 3)
    EXPECT_EQ(divisorCounts[4], 3); // 4 has 3 divisors (1, 2, 4)
    EXPECT_EQ(divisorCounts[5], 2); // 5 has 2 divisors (1, 5)
    EXPECT_EQ(divisorCounts[6], 4); // 6 has 4 divisors (1, 2, 3, 6)
    EXPECT_EQ(divisorCounts[7], 2); // 7 has 2 divisors (1, 7)
    EXPECT_EQ(divisorCounts[8], 4); // 8 has 4 divisors (1, 2, 4, 8)
    EXPECT_EQ(divisorCounts[9], 3); // 9 has 3 divisors (1, 3, 9)
}

class CountSameAdjacentPositiveDivisorsTest : public ::testing::TestWithParam<std::pair<std::vector<int>, int>>
{
};

TEST_P(CountSameAdjacentPositiveDivisorsTest, WhenArrayOfPositiveDivisorCountsPassed_ThenReturnSumOfSameAdjacentPairs)
{
    auto param = GetParam();
    std::vector<int> input = param.first;
    int expected = param.second;
    EXPECT_EQ(countSameAdjacentPositiveDivisors(input.data(), input.size()), expected);
}

INSTANTIATE_TEST_SUITE_P(
    CountSameAdjacentPositiveDivisorsTests,
    CountSameAdjacentPositiveDivisorsTest,
    ::testing::Values(
        std::make_pair(std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 0), // No pair
        std::make_pair(std::vector<int>{0, 1, 2, 2, 3, 2, 4, 2, 4, 3}, 1), // 2-2
        std::make_pair(std::vector<int>{0, 1, 2, 2, 3, 3, 4, 4, 4, 3}, 4)  // 2-2, 3-3, 4-4, 4-4
        ));

class SameAdjacentPositiveDivisorsTest : public ::testing::TestWithParam<std::pair<int, int>>
{
};

TEST_P(SameAdjacentPositiveDivisorsTest, GivenValue_ReturnCountOfSameAdjacentPositiveDivisorsTillValue)
{
    auto param = GetParam();
    int input = param.first;
    int expected = param.second;
    EXPECT_EQ(sameAdjacentPositiveDivisors(input), expected);
}

INSTANTIATE_TEST_SUITE_P(
    SameAdjacentPositiveDivisorsTests,
    SameAdjacentPositiveDivisorsTest,
    ::testing::Values(
        std::make_pair(1, 0),  // No pairs
        std::make_pair(2, 1),  // One pair: (2, 3) -> (1-2, 1-3)
        std::make_pair(3, 1),  // One pair: (2, 3) -> (1-2, 1-3)
        std::make_pair(10, 1), // One pair: (2, 3) -> (1-2, 1-3)
        std::make_pair(20, 2)  // Two Pairs: (2, 3) -> (1-2, 1-3),   (14, 15) ->(1-2-7-14, 1-3-5-15)
        ));
