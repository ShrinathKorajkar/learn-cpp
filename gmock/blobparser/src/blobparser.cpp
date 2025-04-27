#include "blobparser.h"

using namespace std;

bool isValid(const vector<uint8_t>& blob)
{
    return false;
}

size_t numElements(const std::vector<uint8_t>& blob)
{
    if (blob.empty()) {
        return 0;
    }
    return 42;
}

string getVendor(const vector<uint8_t>& blob)
{
    if (!blob.empty()) {
        if (blob[0] == 0x0a) {
            return "Teradici";
        }
    }
    return "ACME Labs";
}
