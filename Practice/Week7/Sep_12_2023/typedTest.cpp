#include <gtest/gtest.h>

template <typename T>
T Add(T a, T b)
{
    return a + b;
}

template <typename T>
class AddTest : public ::testing::Test
{
};

using TestTypes = ::testing::Types<int, double, float>;

TYPED_TEST_SUITE(AddTest, TestTypes);

TYPED_TEST(AddTest, TestAddition)
{
    TypeParam result = Add<TypeParam>(2, 3);
    EXPECT_EQ(result, 5);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
