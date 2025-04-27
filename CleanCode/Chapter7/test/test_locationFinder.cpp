#include <gtest/gtest.h>
#include "locationFinder.h"

class LocationFinderTest : public ::testing::Test
{
protected:
    LocationFinder location_finder;
};

TEST_F(LocationFinderTest, ValidAddress_LocationReceived)
{
    Location location = location_finder.find_location("Silkboard Bangalore");

    EXPECT_NEAR(location.latitude, 12.9173312, 0.0001);
    EXPECT_NEAR(location.longitude, 77.6212483, 0.0001);
}

TEST_F(LocationFinderTest, InvalidAddress_LocationNotReceived)
{
    EXPECT_THROW(location_finder.find_location("Invalid Address"), InvalidAddressException);
}
