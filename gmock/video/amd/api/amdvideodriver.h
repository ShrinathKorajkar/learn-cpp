
#include "videodriver.h"

class AMDVideoDriver : public VideoDriver
{
public:
    bool setTopology(size_t width, size_t height) override;
    bool addMonitor() override;
};
