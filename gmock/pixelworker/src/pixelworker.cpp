#include "pixelworker.h"

#include <pixelstuff.h>
#include <vector>

using namespace std;

PixelWorker::PixelWorker(unique_ptr<PixelStuff> pixelStuff)
  : m_pixelStuff(move(pixelStuff))
{
}

PixelWorker::~PixelWorker() = default;

void PixelWorker::addPixels(const vector<Pixel>& pixels)
{
    // inefficient -- we're always doing the expensive hash.  Time to refactor.
    auto quickHash = m_pixelStuff->quickHash(pixels);
    if (m_quickHashesSeen.find(quickHash) == m_quickHashesSeen.end()) {
        m_quickHashesSeen.insert(quickHash);
        m_expensiveHashesSeen.insert(m_pixelStuff->expensiveHash(pixels));
        ++m_numUniqueBlobs;
        return;
    }

    auto expensiveHash = m_pixelStuff->expensiveHash(pixels);
    if (m_expensiveHashesSeen.find(expensiveHash) == m_expensiveHashesSeen.end()) {
        m_expensiveHashesSeen.insert(expensiveHash);
        ++m_numUniqueBlobs;
        return;
    }
}

size_t PixelWorker::numUniqueBlobs() const
{
    return m_numUniqueBlobs;
}
