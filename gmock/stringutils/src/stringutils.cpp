
#include "stringutils.h"

using namespace std;

string stringutils::trim(const string& str)
{
    auto start = str.find_first_not_of(" \n\r\t");
    auto end = str.find_last_not_of(" \n\r\t") + 1;
    return string(str.begin() + start, str.begin() + end);
}
