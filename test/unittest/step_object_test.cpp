#include "step_object.hpp"

#include <doctest.h>

#include <string>

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
    const step::object ellipseObject{
        step::detail::parse_json("resource/object/ellipse.json")};

    REQUIRE(ellipseObject.is_ellipse());

    CHECK(ellipseObject.id() == 13);
    CHECK(ellipseObject.x() == 560);
    CHECK(ellipseObject.y() == 808);
    CHECK(ellipseObject.width() == 248);
    CHECK(ellipseObject.height() == 152);
    CHECK(ellipseObject.rotation() == 0);
    CHECK(ellipseObject.name().empty());
    CHECK(ellipseObject.type().empty());
    CHECK(ellipseObject.visible());

    CHECK(ellipseObject.is_ellipse());
    CHECK(!ellipseObject.is_point());
    CHECK(!ellipseObject.has<step::polygon>());
    CHECK(!ellipseObject.has<step::polyline>());
    CHECK(!ellipseObject.has<step::template_object>());
    CHECK(!ellipseObject.has<step::text>());
    CHECK(!ellipseObject.has<step::global_id>());
  }

  TEST_CASE("Parsing rectangle object")
  {
    const step::object rectObject{
        step::detail::parse_json("resource/object/rectangle.json")};

    CHECK(rectObject.id() == 14);
    CHECK(rectObject.x() == 576);
    CHECK(rectObject.y() == 584);
    CHECK(rectObject.width() == 368);
    CHECK(rectObject.height() == 184);
    CHECK(rectObject.rotation() == 0);
    CHECK(rectObject.name().empty());
    CHECK(rectObject.type().empty());
    CHECK(rectObject.visible());

    CHECK(!rectObject.is_point());
    CHECK(!rectObject.is_ellipse());
    CHECK(!rectObject.has<step::polygon>());
    CHECK(!rectObject.has<step::polyline>());
    CHECK(!rectObject.has<step::template_object>());
    CHECK(!rectObject.has<step::text>());
    CHECK(!rectObject.has<step::global_id>());
  }

  TEST_CASE("Parsing point object")
  {
    const step::object pointObject{
        step::detail::parse_json("resource/object/point.json")};

    CHECK(pointObject.id() == 20);
    CHECK(pointObject.x() == 220);
    CHECK(pointObject.y() == 350);
    CHECK(pointObject.width() == 0);
    CHECK(pointObject.height() == 0);
    CHECK(pointObject.rotation() == 0);
    CHECK(pointObject.name().empty());
    CHECK(pointObject.type().empty());
    CHECK(pointObject.visible());

    CHECK(pointObject.is_point());
    CHECK(!pointObject.is_ellipse());
    CHECK(!pointObject.has<step::polygon>());
    CHECK(!pointObject.has<step::polyline>());
    CHECK(!pointObject.has<step::template_object>());
    CHECK(!pointObject.has<step::text>());
    CHECK(!pointObject.has<step::global_id>());
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

    SUBCASE("Text related properties")
    {
      const auto& text = textObject.as<step::text>();
      CHECK(text.get_text() == "Hello World");
      CHECK(text.wrap());
    }
  }
}