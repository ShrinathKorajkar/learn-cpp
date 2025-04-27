
#include <gmock/gmock.h>
#include <topology.h>
#include "matchers.h"

using namespace std;
using namespace testing;

class TopologyTest : public Test
{
public:
    TopologyTest()
      : m_topology([this](size_t width, size_t height) { m_listener.Call(width, height); })
    {
    }

protected:
    NiceMock<MockFunction<void(size_t, size_t)>> m_listener;

    Topology m_topology;
};

TEST_F(TopologyTest, WidthRemainsEven)
{
    EXPECT_CALL(m_listener, Call(IsEven(), _));
    m_topology.requestTopology(1024, 2001);
}

TEST_F(TopologyTest, DISABLED_WidthRoundsToEven)
{
    EXPECT_CALL(m_listener, Call(IsEven(), _));
    m_topology.requestTopology(1023, 2001);
}

TEST_F(TopologyTest, DISABLED_HeightIsNotEven)
{
    EXPECT_CALL(m_listener, Call(_, Not(IsEven())));
    m_topology.requestTopology(1023, 2000);
}

TEST_F(TopologyTest, DISABLED_HeightIsMultipleOf8)
{
    EXPECT_CALL(m_listener, Call(_, IsMultipleOf(8)));
    m_topology.requestTopology(1023, 1062);
}

TEST_F(TopologyTest, DISABLED_HeightIsNotAMultipleOf12)
{
    EXPECT_CALL(m_listener, Call(_, Not(IsMultipleOf(12))));
    m_topology.requestTopology(1023, 1068);
}

TEST_F(TopologyTest, Modulo)
{
    EXPECT_THAT(124, Modulo2(Eq(0)));
    EXPECT_THAT(123, Modulo2(Not(Eq(0))));
    EXPECT_THAT(124, Modulo2(IsEven()));
    EXPECT_THAT(123, Modulo2(Not(IsEven())));

    EXPECT_THAT(121, Modulo(5, Lt(2)));
    EXPECT_THAT(125, Modulo(7, Not(Eq(5))));
    EXPECT_THAT(124, Modulo(11, Not(IsEven())));
    EXPECT_THAT(125, Modulo(13, IsMultipleOf(4)));
}

TEST_F(TopologyTest, DISABLED_ModuloUnhappy)
{
    EXPECT_THAT(123, Modulo2(Eq(0)));
    EXPECT_THAT(124, Modulo2(Not(Eq(0))));
    EXPECT_THAT(123, Modulo2(IsEven()));
    EXPECT_THAT(124, Modulo2(Not(IsMultipleOf(4))));
    EXPECT_THAT(123, Modulo(5, Lt(2)));
    EXPECT_THAT(124, Modulo(7, Not(Eq(5))));
    EXPECT_THAT(123, Modulo(11, Not(IsEven())));
    EXPECT_THAT(124, Modulo(13, IsMultipleOf(4)));
}
