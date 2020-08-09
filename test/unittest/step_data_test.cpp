#include "step_data.hpp"

#include <doctest.h>

#include "step_exception.hpp"
#include "step_utils.hpp"

using namespace step;
using namespace detail;

TEST_SUITE("Data")
{
  TEST_CASE("CSV")
  {
    const Data data{parse_json("resource/data/csv.json")};
    CHECK_NOTHROW(data.as_gid());
    CHECK_THROWS_WITH_AS(data.as_base64(),
                         "Data > Couldn't obtain Base64 data!",
                         step_exception);
  }

  TEST_CASE("Base64")
  {
    const Data data{parse_json("resource/data/base64.json")};
    CHECK_NOTHROW(data.as_base64());
    CHECK_THROWS_WITH_AS(
        data.as_gid(), "Data > Couldn't obtain GID data!", step_exception);
  }
}