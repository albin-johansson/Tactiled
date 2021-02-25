#include <doctest.h>

#include <string>

#include "object.hpp"
#include "step_test_utils.h"

TEST_SUITE("object")
{
  using step::operator""_gid;
  TEST_CASE("Parsing normal object")
  {
    const step::object object{
        step::detail::parse_json("resource/object/object.json")};

    CHECK(object.id() == 1);
    CHECK(object.x() == 56);
    CHECK(object.y() == 32);
    CHECK(object.width() == 88);
    CHECK(object.height() == 92);
    CHECK(object.rotation() == 5);
    CHECK(object.name() == "villager");
    CHECK(object.type() == "npc");
    CHECK(object.visible());

    CHECK(object.as<step::global_id>() == 5_gid);

    CHECK(!object.is_ellipse());
    CHECK(!object.is_point());
    CHECK(object.has<step::global_id>());
    CHECK(!object.has<step::polygon>());
    CHECK(!object.has<step::polyline>());
    CHECK(!object.has<step::template_object>());
    CHECK(!object.has<step::text>());

    CHECK(object.try_as<step::global_id>());              // NOLINT
    CHECK_FALSE(object.try_as<step::polygon>());          // NOLINT
    CHECK_FALSE(object.try_as<step::polyline>());         // NOLINT
    CHECK_FALSE(object.try_as<step::text>());             // NOLINT
    CHECK_FALSE(object.try_as<step::template_object>());  // NOLINT

    SUBCASE("Check properties")
    {
      const auto* props = object.get_properties();
      REQUIRE(props);

      REQUIRE(props->has("hp"));
      const auto& prop = props->get("hp");
      CHECK(prop.is<int>());
      CHECK(prop.get<int>() == 12);
    }
  }

  TEST_CASE("Parsing ellipse object")
  {
    const step::object ellipse{
        step::detail::parse_json("resource/object/ellipse.json")};

    REQUIRE(ellipse.is_ellipse());

    CHECK(ellipse.id() == 13);
    CHECK(ellipse.x() == 560);
    CHECK(ellipse.y() == 808);
    CHECK(ellipse.width() == 248);
    CHECK(ellipse.height() == 152);
    CHECK(ellipse.rotation() == 0);
    CHECK(ellipse.name().empty());
    CHECK(ellipse.type().empty());
    CHECK(ellipse.visible());

    CHECK(ellipse.is_ellipse());
    CHECK(!ellipse.is_point());
    CHECK(!ellipse.has<step::polygon>());
    CHECK(!ellipse.has<step::polyline>());
    CHECK(!ellipse.has<step::template_object>());
    CHECK(!ellipse.has<step::text>());
    CHECK(!ellipse.has<step::global_id>());

    CHECK_FALSE(ellipse.try_as<step::global_id>());        // NOLINT
    CHECK_FALSE(ellipse.try_as<step::polygon>());          // NOLINT
    CHECK_FALSE(ellipse.try_as<step::polyline>());         // NOLINT
    CHECK_FALSE(ellipse.try_as<step::text>());             // NOLINT
    CHECK_FALSE(ellipse.try_as<step::template_object>());  // NOLINT
  }

  TEST_CASE("Parsing rectangle object")
  {
    const step::object rect{
        step::detail::parse_json("resource/object/rectangle.json")};

    CHECK(rect.id() == 14);
    CHECK(rect.x() == 576);
    CHECK(rect.y() == 584);
    CHECK(rect.width() == 368);
    CHECK(rect.height() == 184);
    CHECK(rect.rotation() == 0);
    CHECK(rect.name().empty());
    CHECK(rect.type().empty());
    CHECK(rect.visible());

    CHECK(!rect.is_point());
    CHECK(!rect.is_ellipse());
    CHECK(!rect.has<step::polygon>());
    CHECK(!rect.has<step::polyline>());
    CHECK(!rect.has<step::template_object>());
    CHECK(!rect.has<step::text>());
    CHECK(!rect.has<step::global_id>());

    CHECK_FALSE(rect.try_as<step::global_id>());        // NOLINT
    CHECK_FALSE(rect.try_as<step::polygon>());          // NOLINT
    CHECK_FALSE(rect.try_as<step::polyline>());         // NOLINT
    CHECK_FALSE(rect.try_as<step::text>());             // NOLINT
    CHECK_FALSE(rect.try_as<step::template_object>());  // NOLINT
  }

  TEST_CASE("Parsing point object")
  {
    const step::object point{
        step::detail::parse_json("resource/object/point.json")};

    CHECK(point.id() == 20);
    CHECK(point.x() == 220);
    CHECK(point.y() == 350);
    CHECK(point.width() == 0);
    CHECK(point.height() == 0);
    CHECK(point.rotation() == 0);
    CHECK(point.name().empty());
    CHECK(point.type().empty());
    CHECK(point.visible());

    CHECK(point.is_point());
    CHECK(!point.is_ellipse());
    CHECK(!point.has<step::polygon>());
    CHECK(!point.has<step::polyline>());
    CHECK(!point.has<step::template_object>());
    CHECK(!point.has<step::text>());
    CHECK(!point.has<step::global_id>());

    CHECK_FALSE(point.try_as<step::global_id>());        // NOLINT
    CHECK_FALSE(point.try_as<step::polygon>());          // NOLINT
    CHECK_FALSE(point.try_as<step::polyline>());         // NOLINT
    CHECK_FALSE(point.try_as<step::text>());             // NOLINT
    CHECK_FALSE(point.try_as<step::template_object>());  // NOLINT
  }

  TEST_CASE("Parsing polygon object")
  {
    const step::object polygonObject{
        step::detail::parse_json("resource/object/polygon.json")};

    CHECK(polygonObject.id() == 15);
    CHECK(polygonObject.x() == -176);
    CHECK(polygonObject.y() == 432);
    CHECK(polygonObject.width() == 0);
    CHECK(polygonObject.height() == 0);
    CHECK(polygonObject.rotation() == 0);
    CHECK(polygonObject.name().empty());
    CHECK(polygonObject.type().empty());
    CHECK(polygonObject.visible());

    CHECK(!polygonObject.is_ellipse());
    CHECK(!polygonObject.is_point());
    CHECK(polygonObject.has<step::polygon>());
    CHECK(!polygonObject.has<step::polyline>());
    CHECK(!polygonObject.has<step::template_object>());
    CHECK(!polygonObject.has<step::text>());
    CHECK(!polygonObject.has<step::global_id>());

    CHECK(polygonObject.try_as<step::polygon>());                // NOLINT
    CHECK_FALSE(polygonObject.try_as<step::global_id>());        // NOLINT
    CHECK_FALSE(polygonObject.try_as<step::polyline>());         // NOLINT
    CHECK_FALSE(polygonObject.try_as<step::text>());             // NOLINT
    CHECK_FALSE(polygonObject.try_as<step::template_object>());  // NOLINT

    SUBCASE("Check polygon stuff")
    {
      const auto& polygon = polygonObject.as<step::polygon>();
      REQUIRE(polygon.points.size() == 5);

      const auto& points = polygon.points;
      CHECK(points.at(0).x() == 0);
      CHECK(points.at(0).y() == 0);

      CHECK(points.at(1).x() == 152);
      CHECK(points.at(1).y() == 88);

      CHECK(points.at(2).x() == 136);
      CHECK(points.at(2).y() == -128);

      CHECK(points.at(3).x() == 80);
      CHECK(points.at(3).y() == -280);

      CHECK(points.at(4).x() == 16);
      CHECK(points.at(4).y() == -288);
    }
  }

  TEST_CASE("Parsing polyline object")
  {
    const step::object polylineObject{
        step::detail::parse_json("resource/object/polyline.json")};

    CHECK(polylineObject.id() == 16);
    CHECK(polylineObject.x() == 240);
    CHECK(polylineObject.y() == 88);
    CHECK(polylineObject.width() == 0);
    CHECK(polylineObject.height() == 0);
    CHECK(polylineObject.rotation() == 0);
    CHECK(polylineObject.name().empty());
    CHECK(polylineObject.type().empty());
    CHECK(polylineObject.visible());

    CHECK(!polylineObject.is_ellipse());
    CHECK(!polylineObject.is_point());
    CHECK(polylineObject.has<step::polyline>());
    CHECK(!polylineObject.has<step::global_id>());
    CHECK(!polylineObject.has<step::polygon>());
    CHECK(!polylineObject.has<step::template_object>());
    CHECK(!polylineObject.has<step::text>());

    CHECK(polylineObject.try_as<step::polyline>());               // NOLINT
    CHECK_FALSE(polylineObject.try_as<step::polygon>());          // NOLINT
    CHECK_FALSE(polylineObject.try_as<step::global_id>());        // NOLINT
    CHECK_FALSE(polylineObject.try_as<step::text>());             // NOLINT
    CHECK_FALSE(polylineObject.try_as<step::template_object>());  // NOLINT

    SUBCASE("Check polyline stuff")
    {
      const auto& polyline = polylineObject.as<step::polyline>();
      REQUIRE(polyline.points.size() == 6);

      const auto& points = polyline.points;
      CHECK(points.at(0).x() == 0);
      CHECK(points.at(0).y() == 0);

      CHECK(points.at(1).x() == 248);
      CHECK(points.at(1).y() == -32);

      CHECK(points.at(2).x() == 376);
      CHECK(points.at(2).y() == 72);

      CHECK(points.at(3).x() == 544);
      CHECK(points.at(3).y() == 288);

      CHECK(points.at(4).x() == 656);
      CHECK(points.at(4).y() == 120);

      CHECK(points.at(5).x() == 512);
      CHECK(points.at(5).y() == 0);
    }
  }

  TEST_CASE("Parsing text object")
  {
    const step::object textObject{
        step::detail::parse_json("resource/object/text.json")};

    CHECK(textObject.id() == 15);
    CHECK(textObject.x() == 48);
    CHECK(textObject.y() == 136);
    CHECK(textObject.width() == 248);
    CHECK(textObject.height() == 19);
    CHECK(textObject.rotation() == 0);
    CHECK(textObject.name().empty());
    CHECK(textObject.type().empty());
    CHECK(textObject.visible());

    CHECK(!textObject.is_ellipse());
    CHECK(!textObject.is_point());
    CHECK(textObject.has<step::text>());
    CHECK(!textObject.has<step::polyline>());
    CHECK(!textObject.has<step::global_id>());
    CHECK(!textObject.has<step::polygon>());
    CHECK(!textObject.has<step::template_object>());

    CHECK(textObject.try_as<step::text>());                   // NOLINT
    CHECK_FALSE(textObject.try_as<step::polyline>());         // NOLINT
    CHECK_FALSE(textObject.try_as<step::polygon>());          // NOLINT
    CHECK_FALSE(textObject.try_as<step::global_id>());        // NOLINT
    CHECK_FALSE(textObject.try_as<step::template_object>());  // NOLINT

    SUBCASE("Text related properties")
    {
      const auto& text = textObject.as<step::text>();
      CHECK(text.get_text() == "Hello World");
      CHECK(text.wrap());
    }
  }
}