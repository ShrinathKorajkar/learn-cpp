#include "videodriver_paramtest.h"

using namespace std;
using namespace testing;

VideoDriverConformance::VideoDriverConformance()
  : m_uut(GetParam()())
{
}

TEST_P(VideoDriverConformance, BasicTopology)
{
    EXPECT_THAT(m_uut->setTopology(640, 480), Eq(true));
}

TEST_P(VideoDriverConformance, AddMonitor)
{
    EXPECT_THAT(m_uut->addMonitor(), Eq(true));
}

TEST_P(VideoDriverConformance, AddTwoMonitors)
{
    EXPECT_THAT(m_uut->addMonitor(), Eq(true));
    EXPECT_THAT(m_uut->addMonitor(), Eq(true));
}
