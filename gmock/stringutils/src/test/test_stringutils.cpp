
#include "stringutils.h"
#include <gmock/gmock.h>

using namespace std;
using namespace testing;

class TrimTest : public TestWithParam<tuple<string, string>>
{
public:
    const string& value() const
    {
        return get<0>(GetParam());
    }

    static string name(const TestParamInfo<tuple<string, string>>& param)
    {
        return get<1>(param.param);
    }
};

TEST_P(TrimTest, Whitespace)
{
    ASSERT_THAT(stringutils::trim(value()), StrEq("trimmed"));
}

INSTANTIATE_TEST_CASE_P(
  Trim, TrimTest,
  Values(
    make_tuple("  trimmed     ", "spaces"), make_tuple("trimmed", "nothingToTrim"),
    make_tuple("trimmed ", "trailingSpace"), make_tuple(" trimmed", "leadingSpace"),
    make_tuple("\ntrimmed", "leadingNewline"), make_tuple("trimmed\n", "trailingNewline"),
    make_tuple("\ttrimmed", "leadingTab"), make_tuple("trimmed\t", "trailingTab"), make_tuple("\rtrimmed", "leadingCR"),
    make_tuple("trimmed\r", "trailingCR"), make_tuple("\r\t\n trimmed \r\t\n", "mixedWhitespace"),
    make_tuple("\r\rtrimmed\n\n", "repeatedCRandLF")),
  TrimTest::name);
