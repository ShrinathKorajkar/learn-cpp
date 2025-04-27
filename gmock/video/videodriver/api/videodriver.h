#pragma once

#include <cstddef>

class VideoDriver
{
public:
    virtual ~VideoDriver() = default;

    virtual bool setTopology(size_t width, size_t height) = 0;
    virtual bool addMonitor() = 0;
};
