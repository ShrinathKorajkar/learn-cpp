
#include <chrono>

class ADPCMEncoder
{
public:
    ADPCMEncoder(std::chrono::milliseconds frameSize);

    bool adjustQuality(float bandwidthActive, uint32_t bandwidthLimit, float queueFillRatio);
    size_t getCompressedSize() const;

private:
    float m_bandwidthActive;
    uint32_t m_bandwidthLimit;
    float m_queueFillRatio;
};
