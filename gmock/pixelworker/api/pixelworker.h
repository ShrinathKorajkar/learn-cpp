#include <memory>
#include <set>
#include <string>
#include <vector>

class PixelStuff;
using Pixel = uint32_t;

class PixelWorker
{
public:
    PixelWorker(std::unique_ptr<PixelStuff> pixelStuff);
    ~PixelWorker();

    void addPixels(const std::vector<Pixel>& pixels);
    size_t numUniqueBlobs() const;

private:
    std::unique_ptr<PixelStuff> m_pixelStuff;

    std::set<std::string> m_quickHashesSeen;
    std::set<std::string> m_expensiveHashesSeen;
    size_t m_numUniqueBlobs = 0;
};