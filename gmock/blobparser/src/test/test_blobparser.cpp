#include <blobparser.h>
#include <gmock/gmock.h>

using namespace testing;

TEST(BlobParserBasics, Invalid)
{
    EXPECT_FALSE(isValid({}));
    EXPECT_THAT(isValid({}), Eq(false));
}

TEST(BlobParserBasics, CountElements)
{
    EXPECT_EQ(numElements({}), 0);
    EXPECT_EQ(0, numElements({}));
    EXPECT_THAT(numElements({}), Eq(0));
}

TEST(BlobParserBasics, ElementThreshold)
{
    EXPECT_LT(numElements({}), 100);
    EXPECT_THAT(numElements({}), Lt(100));
}

TEST(BlobParserBasics, Vendor)
{
    EXPECT_THAT(getVendor({0x0a}), Eq("Teradici"));
    // EXPECT_THAT( getVendor( { 0x0a } ).c_str(), Eq( "Teradici" ) ); // fails
    EXPECT_THAT(getVendor({0x0a}), StrEq("Teradici"));
    EXPECT_THAT(getVendor({0x0a}).c_str(), StrEq("Teradici"));
}
