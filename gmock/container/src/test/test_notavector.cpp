#include "notavector.h"

#include <gmock/gmock.h>

using namespace std;
using namespace testing;

namespace
{
struct Blob {
    int A;
    int B;
};
}  // namespace

template<typename T>
class NotAVectorTest : public Test
{
public:
    NotAVector<T> m_uut;
};

using ContentTypes = Types<char, size_t, Blob>;
TYPED_TEST_CASE(NotAVectorTest, ContentTypes);

TYPED_TEST(NotAVectorTest, StoreSingle)
{
    // TypeParam is the type for this run of the test
    TypeParam obj;

    // The base class is a template, so we must use this-> to access stuff from it.
    EXPECT_THAT(this->m_uut, IsEmpty());
    this->m_uut.push_back(obj);
    EXPECT_THAT(this->m_uut.size(), Eq(1));
}

TYPED_TEST(NotAVectorTest, StoreMultiple)
{
    TypeParam obj;

    EXPECT_THAT(this->m_uut, IsEmpty());
    this->m_uut.push_back(obj);
    EXPECT_THAT(this->m_uut.size(), Eq(1));
    this->m_uut.push_back(obj);
    EXPECT_THAT(this->m_uut.size(), Eq(2));
}
