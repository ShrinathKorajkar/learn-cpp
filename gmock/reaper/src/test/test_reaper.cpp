#include "reaper.h"

#include <future>
#include <exception>
#include <gmock/gmock.h>

using namespace std;
using namespace testing;

namespace
{
size_t getNumber()
{
    return 42;
}
}  // anonymous namespace

#if 0
TEST(ExceptionTest, OutOfRangeGeneric)
{
    try {
        getItem(42);
    } catch(const exception&) {
        // What we expected
        return;
    }
    FAIL() << "No exception was thrown";
}

TEST(ExceptionTest, OutOfRangeSpecific)
{
    try {
        getItem(42);
    } catch(const out_of_range&) {
        // What we expected
        return;
    } catch(const exception& e) {
        FAIL() << "Unexpected exception: " << e.what();
    }
    FAIL() << "No exception was thrown";
}
#else
TEST(ExceptionTest, OutOfRangeGeneric)
{
    EXPECT_ANY_THROW(getItem(42));
}

TEST(ExceptionTest, OutOfRangeSpecific)
{
    EXPECT_THROW(getItem(42), out_of_range);
}
#endif

TEST(ExceptionTest, DISABLED_UncaughtException)
{
    throw runtime_error("GTest will fail this test due to an uncaught exception");
}

#if 0
TEST(ExceptionTest, MessageCheck)
{
    EXPECT_THROW(
      {
          try {
              getItem(42);
          } catch (const out_of_range& e) {
              EXPECT_THAT(e.what(), HasSubstr("important words"));
              throw;
          }
      },
      out_of_range);
}
#else
#define EXPECT_THROW_MSG(body, exception_type, msg_matcher) \
    EXPECT_THROW( \
      { \
          try { \
              body; \
          } catch (const exception_type& e) { \
              EXPECT_THAT(e.what(), msg_matcher); \
              throw; \
          } \
      }, \
      exception_type);

TEST(ExceptionTest, MessageCheck)
{
    EXPECT_THROW_MSG(getItem(42), out_of_range, HasSubstr("important words"));
}
#endif

TEST(ExampleDeathTest, Nullptr)
{
    EXPECT_DEATH(doStuff(nullptr), "input .* null");
}

TEST(ExampleDeathTest, ExitCode4WhenBadCommand)
{
    EXPECT_EXIT(parseCommand("bogus"), ExitedWithCode(4), ".*Time.*die.*");
}

TEST(ExampleDeathTest, NormalExit)
{
    EXPECT_EXIT(stop(), ExitedWithCode(0), "");
}

TEST(ExampleDeathTest, DISABLED_FunctionCalledExpectationOutside)
{
    MockFunction<void()> mockFn;
    EXPECT_CALL(mockFn, Call());  // Fails the test (never called in main process)

    EXPECT_DEATH(
      {
          mockFn.Call();
          abort();
      },
      "");
}

TEST(ExampleDeathTest, FunctionCalledExpectationInside)
{
    MockFunction<void()> mockFn;

    EXPECT_DEATH(
      {
          EXPECT_CALL(mockFn, Call());
          mockFn.Call();
          abort();
      },
      "");
}

TEST(ExampleDeathTest, FunctionCalledExpectationInsideNeverCalled)
{
    MockFunction<void()> mockFn;

    EXPECT_DEATH(
      {
          EXPECT_CALL(mockFn, Call());  // Does not fail the test - not asserted in main process
          // mockFn.Call();
          abort();
      },
      "");
}

TEST(ExampleDeathTest, DISABLED_Thread)
{
    auto worker = async(launch::async, getNumber);

    EXPECT_DEATH({ exit(42); }, "");

    auto answer = worker.get();
}
