#include "amdvideodriver.h"

#include <ostream>
#include <videodriver_paramtest.h>

using namespace std;
using namespace testing;

namespace
{
unique_ptr<VideoDriver> createDriver()
{
    return unique_ptr<VideoDriver>(new AMDVideoDriver());
}

ostream& operator<<(ostream& os, const VideoDriverCreator& /* videodriver */)
{
    return os << "factory function for a Video Driver";
}
}  // namespace

// This is required to defeat optimizing compilers; I.e. this makes it clear to the compiler
// that VideoDriverConformance IS used and shouldn't be cut out.
TEST_P(VideoDriverConformance, ForceSuiteToLoad) {}

INSTANTIATE_TEST_CASE_P(AMD, VideoDriverConformance, Values(createDriver));
INSTANTIATE_TEST_CASE_P(Nvidia, VideoDriverConformance, Values(createDriver));
