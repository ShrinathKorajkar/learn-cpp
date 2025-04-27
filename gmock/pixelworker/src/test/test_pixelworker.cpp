#include "pixelworker.h"
#include <memory>
#include <mockpixelstuff.h>
#include <gmock/gmock.h>

using namespace std;
using namespace testing;

class PixelCorrectness : public Test
{
public:
    PixelCorrectness()
      : m_pixelWorker([this] {
          unique_ptr<PixelStuffImpl> impl(new NiceMock<PixelStuffImpl>());
          m_pixelStuffImpl = impl.get();
          return unique_ptr<PixelStuff>(new PixelStuff(move(impl)));
      }())
    {
    }

protected:
    PixelStuffImpl* m_pixelStuffImpl;
    PixelWorker m_pixelWorker;
};

TEST_F(PixelCorrectness, QuickHashCollission)
{
    const vector<Pixel> pixelsA{123, 123, 123};
    const vector<Pixel> pixelsB{2, 2};

    ON_CALL(*m_pixelStuffImpl, quickHash(_)).WillByDefault(Return("f00"));
    ON_CALL(*m_pixelStuffImpl, expensiveHash(ElementsAreArray(pixelsA))).WillByDefault(Return("aa"));
    ON_CALL(*m_pixelStuffImpl, expensiveHash(ElementsAreArray(pixelsB))).WillByDefault(Return("bb"));

    m_pixelWorker.addPixels(pixelsA);
    m_pixelWorker.addPixels(pixelsB);
    EXPECT_THAT(m_pixelWorker.numUniqueBlobs(), Eq(2));
}

TEST_F(PixelCorrectness, DuplicatePixels)
{
    const vector<Pixel> pixels{123, 123, 123};

    ON_CALL(*m_pixelStuffImpl, quickHash(_)).WillByDefault(Return("f00"));
    ON_CALL(*m_pixelStuffImpl, expensiveHash(_)).WillByDefault(Return("aa"));

    m_pixelWorker.addPixels(pixels);
    m_pixelWorker.addPixels(pixels);
    EXPECT_THAT(m_pixelWorker.numUniqueBlobs(), Eq(1));
}
