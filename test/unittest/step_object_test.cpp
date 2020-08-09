#include "step_object.hpp"

#include <doctest.h>

#include <string>

#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/object/";

TEST_SUITE("Object")
{
  TEST_CASE("Parsing normal object")
  {
    const Object object{detail::parse_json("resource/object/object.json")};

    CHECK(object.id() == 1);
    CHECK(object.x() == 56);
    CHECK(object.y() == 32);
    CHECK(object.width() == 88);
    CHECK(object.height() == 92);
    CHECK(object.rotation() == 5);
    CHECK(object.name() == "villager");
    CHECK(object.type() == "npc");
    CHECK(object.visible());

    CHECK(object.tile_gid() == 5_gid);

    CHECK(object.is_tile());
    CHECK(!object.is_ellipse());
    CHECK(!object.is_point());
    CHECK(!object.is_polygon());
    CHECK(!object.is_polyline());
    CHECK(!object.is_template());
    CHECK(!object.is_text());

    SUBCASE("Check properties")
    {
      const auto* props = object.properties();
      REQUIRE(props);

      REQUIRE(props->has("hp"));
      const auto& prop = props->get("hp");
      CHECK(prop.is<int>());
      CHECK(prop.get<int>() == 12);
    }
  }

  TEST_CASE("Parsing ellipse object")
  {
    const Object ellipseObject{
        detail::parse_json("resource/object/ellipse.json")};

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
    CHECK(!ellipseObject.is_polygon());
    CHECK(!ellipseObject.is_polyline());
    CHECK(!ellipseObject.is_template());
    CHECK(!ellipseObject.is_text());
    CHECK(!ellipseObject.is_tile());
  }

  TEST_CASE("Parsing rectangle object")
  {
    const Object rectObject{
        detail::parse_json("resource/object/rectangle.json")};

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
    CHECK(!rectObject.is_polygon());
    CHECK(!rectObject.is_polyline());
    CHECK(!rectObject.is_ellipse());
    CHECK(!rectObject.is_template());
    CHECK(!rectObject.is_text());
    CHECK(!rectObject.is_tile());
  }

  TEST_CASE("Parsing point object")
  {
    const Object pointObject{detail::parse_json("resource/object/point.json")};

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
    CHECK(!pointObject.is_polygon());
    CHECK(!pointObject.is_polyline());
    CHECK(!pointObject.is_ellipse());
    CHECK(!pointObject.is_template());
    CHECK(!pointObject.is_text());
    CHECK(!pointObject.is_tile());
  }

  TEST_CASE("Parsing polygon object")
  {
    const Object polygonObject{detail::parse_json("resource/object/polygon.json")};

    CHECK(polygonObject.id() == 15);
    CHECK(polygonObject.x() == -176);
    CHECK(polygonObject.y() == 432);
    CHECK(polygonObject.width() == 0);
    CHECK(polygonObject.height() == 0);
    CHECK(polygonObject.rotation() == 0);
    CHECK(polygonObject.name().empty());
    CHECK(polygonObject.type().empty());
    CHECK(polygonObject.visible());

    CHECK(polygonObject.is_polygon());
    CHECK(!polygonObject.is_polyline());
    CHECK(!polygonObject.is_ellipse());
    CHECK(!polygonObject.is_point());
    CHECK(!polygonObject.is_template());
    CHECK(!polygonObject.is_text());
    CHECK(!polygonObject.is_tile());

    SUBCASE("Check polygon stuff")
    {
      const auto polygon = polygonObject.polygon();
      REQUIRE(polygon);
      REQUIRE(polygon->points.size() == 5);

      const auto& points = polygon->points;
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
    const Object polylineObject{detail::parse_json("resource/object/polyline.json")};

    CHECK(polylineObject.id() == 16);
    CHECK(polylineObject.x() == 240);
    CHECK(polylineObject.y() == 88);
    CHECK(polylineObject.width() == 0);
    CHECK(polylineObject.height() == 0);
    CHECK(polylineObject.rotation() == 0);
    CHECK(polylineObject.name().empty());
    CHECK(polylineObject.type().empty());
    CHECK(polylineObject.visible());

    CHECK(polylineObject.is_polyline());
    CHECK(!polylineObject.is_tile());
    CHECK(!polylineObject.is_ellipse());
    CHECK(!polylineObject.is_point());
    CHECK(!polylineObject.is_polygon());
    CHECK(!polylineObject.is_template());
    CHECK(!polylineObject.is_text());

    SUBCASE("Check polyline stuff")
    {
      const auto polyline = polylineObject.polyline();
      REQUIRE(polyline);
      REQUIRE(polyline->points.size() == 6);

      const auto& points = polyline->points;
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
    const Object textObject{detail::parse_json("resource/object/text.json")};

    CHECK(textObject.id() == 15);
    CHECK(textObject.x() == 48);
    CHECK(textObject.y() == 136);
    CHECK(textObject.width() == 248);
    CHECK(textObject.height() == 19);
    CHECK(textObject.rotation() == 0);
    CHECK(textObject.name().empty());
    CHECK(textObject.type().empty());
    CHECK(textObject.visible());

    CHECK(textObject.is_text());
    CHECK(!textObject.is_polyline());
    CHECK(!textObject.is_tile());
    CHECK(!textObject.is_ellipse());
    CHECK(!textObject.is_point());
    CHECK(!textObject.is_polygon());
    CHECK(!textObject.is_template());

    SUBCASE("Text related properties")
    {
      const auto text = textObject.get_text();
      REQUIRE(text);
      CHECK(text->get_text() == "Hello World");
      CHECK(text->wrap());
    }
  }
}