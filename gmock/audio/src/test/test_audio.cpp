#include "audio.h"

#include <gmock/gmock.h>

using namespace std;
using namespace testing;

const chrono::milliseconds TwentyMsFrame(20);

#if 0
class ADPCMEncoderQualityTest : public TestWithParam<tuple<float, uint32_t, float, unsigned>>
{
public:
    float bandwidthActive()
    {
        return get<0>(GetParam());
    }
    uint32_t bandwidthLimit()
    {
        return get<1>(GetParam());
    }
    float queueFillRatio()
    {
        return get<2>(GetParam());
    }
    unsigned expectedCompressedSize()
    {
        return get<3>(GetParam());
    }
};

TEST_P(ADPCMEncoderQualityTest, calculatesCorrectQuality)
{
    ADPCMEncoder e(TwentyMsFrame);
    EXPECT_THAT(e.adjustQuality(bandwidthActive(), bandwidthLimit(), queueFillRatio()), Eq(true));
    EXPECT_THAT(e.getCompressedSize(), Eq(expectedCompressedSize()));
}
#else
class ADPCMEncoderQualityTest : public TestWithParam<tuple<float, uint32_t, float, unsigned>>
{
public:
    ADPCMEncoderQualityTest()
      : m_uut(TwentyMsFrame)
      , m_bandwidthActive(get<0>(GetParam()))
      , m_bandwidthLimit(get<1>(GetParam()))
      , m_queueFillRatio(get<2>(GetParam()))
      , m_expectedCompressedSize(get<3>(GetParam()))
    {
    }

    ADPCMEncoder m_uut;
    const float m_bandwidthActive;
    const uint32_t m_bandwidthLimit;
    const float m_queueFillRatio;
    const unsigned m_expectedCompressedSize;
};

TEST_P(ADPCMEncoderQualityTest, AdjustQuality)
{
    EXPECT_THAT(m_uut.adjustQuality(m_bandwidthActive, m_bandwidthLimit, m_queueFillRatio), Eq(true));
}
TEST_P(ADPCMEncoderQualityTest, calculatesCorrectQuality)
{
    EXPECT_THAT(m_uut.adjustQuality(m_bandwidthActive, m_bandwidthLimit, m_queueFillRatio), Eq(true));
    EXPECT_THAT(m_uut.getCompressedSize(), Eq(m_expectedCompressedSize));
}
#endif

INSTANTIATE_TEST_CASE_P(
  ADPCMEncoder, ADPCMEncoderQualityTest,
  Values(
    make_tuple(10.0, 450, 0, 970), make_tuple(10.0, 449, 0, 165), make_tuple(10.0, 90, 0, 165),
    make_tuple(10.0, 89, 0, 85), make_tuple(1.12, 500, 0, 970), make_tuple(1.11, 500, 0, 165),
    make_tuple(0.71, 500, 0, 165), make_tuple(0.69, 500, 0, 85), make_tuple(10.0, 500, 0.6, 85)));

using EncoderFrameSize = TestWithParam<uint32_t>;
TEST_P(EncoderFrameSize, FrameSizeOkay)
{
    EXPECT_NO_THROW(ADPCMEncoder(chrono::milliseconds(GetParam())));
}

INSTANTIATE_TEST_CASE_P(ADPCMEncoder, EncoderFrameSize, Values(1, 5, 10, 20), PrintToStringParamName());
