#pragma once

#include "videodriver.h"

#include <gmock/gmock.h>

#include <functional>
#include <memory>

using VideoDriverCreator = std::function<std::unique_ptr<VideoDriver>()>;

class VideoDriverConformance : public ::testing::TestWithParam<VideoDriverCreator>
{
public:
    VideoDriverConformance();

    std::unique_ptr<VideoDriver> m_uut;
};
