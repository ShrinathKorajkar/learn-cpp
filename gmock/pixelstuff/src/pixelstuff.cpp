#include "pixelstuff.h"

using namespace std;

class PixelStuffImpl
{
public:
    PixelStuffImpl() = default;
    ~PixelStuffImpl() = default;
};

PixelStuff::PixelStuff() = default;
PixelStuff::PixelStuff(unique_ptr<PixelStuffImpl> /*impl*/) {}
PixelStuff::~PixelStuff() = default;
