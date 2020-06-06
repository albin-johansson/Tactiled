#include "step_data.h"

#include <doctest.h>

#include "step_exception.h"
#include "step_test_utils.h"

using namespace step;
using namespace detail;

inline static const std::string prefix = "resource/data/";

TEST_SUITE("Data")
{
  TEST_CASE("CSV")
  {
    const auto data = test::make<Data>(prefix, "csv.json");
    CHECK_NOTHROW(data.as_gid());
    CHECK_THROWS_WITH_AS(
        data.as_base64(), "Data > Couldn't obtain Base64 data!", StepException);
  }

  TEST_CASE("Base64")
  {
    const auto data = test::make<Data>(prefix, "base64.json");
    CHECK_NOTHROW(data.as_base64());
    CHECK_THROWS_WITH_AS(
        data.as_gid(), "Data > Couldn't obtain GID data!", StepException);
  }
}