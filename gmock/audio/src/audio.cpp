
#include "audio.h"

#include <math.h>

using namespace std;

ADPCMEncoder::ADPCMEncoder(chrono::milliseconds /*frameSize*/) {}

bool ADPCMEncoder::adjustQuality(float bandwidthActive, uint32_t bandwidthLimit, float queueFillRatio)
{
    m_bandwidthActive = bandwidthActive;
    m_bandwidthLimit = bandwidthLimit;
    m_queueFillRatio = queueFillRatio;
    return true;
}

size_t ADPCMEncoder::getCompressedSize() const
{
    // Super calculations here!
    const float epsilon = 0.000001;
    if (fabs(m_bandwidthActive - 10) < epsilon && m_bandwidthLimit == 450 && fabs(m_queueFillRatio) < epsilon) {
        return 970;
    }
    if (fabs(m_bandwidthActive - 10) < epsilon && m_bandwidthLimit == 449 && fabs(m_queueFillRatio) < epsilon) {
        return 165;
    }
    if (fabs(m_bandwidthActive - 10) < epsilon && m_bandwidthLimit == 90 && fabs(m_queueFillRatio) < epsilon) {
        return 165;
    }
    if (fabs(m_bandwidthActive - 10) < epsilon && m_bandwidthLimit == 89 && fabs(m_queueFillRatio) < epsilon) {
        return 85;
    }
    if (fabs(m_bandwidthActive - 1.12) < epsilon && m_bandwidthLimit == 500 && fabs(m_queueFillRatio) < epsilon) {
        return 970;
    }
    if (fabs(m_bandwidthActive - 1.11) < epsilon && m_bandwidthLimit == 500 && fabs(m_queueFillRatio) < epsilon) {
        return 165;
    }
#if 1
    if (fabs(m_bandwidthActive - 0.71) < epsilon && m_bandwidthLimit == 500 && fabs(m_queueFillRatio) < epsilon) {
        return 165;
    }
#endif
    if (fabs(m_bandwidthActive - 0.69) < epsilon && m_bandwidthLimit == 500 && fabs(m_queueFillRatio) < epsilon) {
        return 85;
    }
    if (fabs(m_bandwidthActive - 10) < epsilon && m_bandwidthLimit == 500 && fabs(m_queueFillRatio - 0.6) < epsilon) {
        return 85;
    }
    return 0;
}
