#include "mockpixelstuff.h"

PixelStuffImpl::PixelStuffImpl() = default;
PixelStuffImpl::~PixelStuffImpl() = default;

PixelStuff::PixelStuff(std::unique_ptr<PixelStuffImpl> impl)
  : m_impl(move(impl))
{
}
PixelStuff::~PixelStuff() = default;

void PixelStuff::addPixels(const std::vector<Pixel>& pixels)
{
    m_impl->addPixels(pixels);
}
std::string PixelStuff::quickHash(const std::vector<Pixel>& pixels) const
{
    return m_impl->quickHash(pixels);
}
std::string PixelStuff::expensiveHash(const std::vector<Pixel>& pixels) const
{
    return m_impl->expensiveHash(pixels);
}
