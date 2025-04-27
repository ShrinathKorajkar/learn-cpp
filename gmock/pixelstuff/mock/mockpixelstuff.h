#include "pixelstuff.h"
#include <gmock/gmock.h>

class PixelStuffImpl
{
public:
    PixelStuffImpl();
    virtual ~PixelStuffImpl();

    MOCK_METHOD1(addPixels, void(const std::vector<Pixel>&));
    MOCK_CONST_METHOD1(quickHash, std::string(const std::vector<Pixel>&));
    MOCK_CONST_METHOD1(expensiveHash, std::string(const std::vector<Pixel>&));
};
