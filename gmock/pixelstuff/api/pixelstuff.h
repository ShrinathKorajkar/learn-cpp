#include <memory>
#include <string>
#include <vector>

using Pixel = uint32_t;
class PixelStuffImpl;
class PixelStuff
{
public:
    PixelStuff();
    PixelStuff(std::unique_ptr<PixelStuffImpl> impl);
    ~PixelStuff();

    void addPixels(const std::vector<Pixel>& pixels);
    std::string quickHash(const std::vector<Pixel>& pixels) const;
    std::string expensiveHash(const std::vector<Pixel>& pixels) const;

private:
    std::unique_ptr<PixelStuffImpl> m_impl;
};
