#include "step_chunk.h"

#include <doctest.h>

#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/chunk/";

//TEST_SUITE("Chunk")
//{
//  TEST_CASE("Parse chunk with CSV data")
//  {
//    const auto chunk = test::make<Chunk>(prefix, "chunk_csv.json");
//
//    SUBCASE("Test obtaining data")
//    {
//      const auto& data = chunk.data();
//      CHECK_NOTHROW(data.as_gid());
//      CHECK_THROWS(data.as_base64());
//    }
//    CHECK(chunk.x() == 7);
//    CHECK(chunk.y() == -18);
//    CHECK(chunk.width() == 16);
//    CHECK(chunk.height() == 22);
//  }
//
//  TEST_CASE("Parse chunk with Base64 data")
//  {
//    const auto chunk = test::make<Chunk>(prefix, "chunk_base64.json");
//
//    SUBCASE("Test obtaining data")
//    {
//      const auto& data = chunk.data();
//      CHECK_NOTHROW(data.as_base64());
//      CHECK_THROWS(data.as_gid());
//    }
//    CHECK(chunk.x() == 45);
//    CHECK(chunk.y() == 77);
//    CHECK(chunk.width() == 31);
//    CHECK(chunk.height() == 29);
//  }
//}
