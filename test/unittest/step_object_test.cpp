#include "step_object.h"

#include <doctest.h>

#include <string>

#include "step_test_utils.h"

using namespace step;

inline static const std::string prefix = "resource/object/";

TEST_SUITE("Object")
{
  TEST_CASE("Parsing normal object")
  {
    const auto object = test::make<Object>(prefix, "object.json");

    CHECK(object.id() == 1);
    CHECK(object.x() == 56);
    CHECK(object.y() == 32);
    CHECK(object.width() == 88);
    CHECK(object.height() == 92);
    CHECK(object.rotation() == 5);
    CHECK(object.name() == "villager");
    CHECK(object.type() == "npc");
    CHECK(object.visible());

    CHECK(object.tile_gid() == 5);

    SUBCASE("Check properties")
    {
      const auto& props = object.properties();
      REQUIRE(props.has("hp"));
      const auto prop = props.get("hp");
      CHECK(prop.is_int());
      CHECK(*prop.as_int() == 12);
    }
  }

  TEST_CASE("Parsing ellipse object")
  {
    const auto ellipseObject = test::make<Object>(prefix, "ellipse.json");

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
  }

  TEST_CASE("Parsing rectangle object")
  {
    const auto rectObject = test::make<Object>(prefix, "rectangle.json");

    CHECK(rectObject.id() == 14);
    CHECK(rectObject.x() == 576);
    CHECK(rectObject.y() == 584);
    CHECK(rectObject.width() == 368);
    CHECK(rectObject.height() == 184);
    CHECK(rectObject.rotation() == 0);
    CHECK(rectObject.name().empty());
    CHECK(rectObject.type().empty());
    CHECK(rectObject.visible());
  }

  TEST_CASE("Parsing point object")
  {
    const auto pointObject = test::make<Object>(prefix, "point.json");

    CHECK(pointObject.id() == 20);
    CHECK(pointObject.x() == 220);
    CHECK(pointObject.y() == 350);
    CHECK(pointObject.width() == 0);
    CHECK(pointObject.height() == 0);
    CHECK(pointObject.rotation() == 0);
    CHECK(pointObject.name().empty());
    CHECK(pointObject.type().empty());
    CHECK(pointObject.visible());
  }

  TEST_CASE("Parsing polygon object")
  {
    const auto polygonObject = test::make<Object>(prefix, "polygon.json");

    CHECK(polygonObject.id() == 15);
    CHECK(polygonObject.x() == -176);
    CHECK(polygonObject.y() == 432);
    CHECK(polygonObject.width() == 0);
    CHECK(polygonObject.height() == 0);
    CHECK(polygonObject.rotation() == 0);
    CHECK(polygonObject.name().empty());
    CHECK(polygonObject.type().empty());
    CHECK(polygonObject.visible());

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
    const auto polylineObject = test::make<Object>(prefix, "polyline.json");

    CHECK(polylineObject.id() == 16);
    CHECK(polylineObject.x() == 240);
    CHECK(polylineObject.y() == 88);
    CHECK(polylineObject.width() == 0);
    CHECK(polylineObject.height() == 0);
    CHECK(polylineObject.rotation() == 0);
    CHECK(polylineObject.name().empty());
    CHECK(polylineObject.type().empty());
    CHECK(polylineObject.visible());

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
    const auto textObject = test::make<Object>(prefix, "text.json");

    CHECK(textObject.id() == 15);
    CHECK(textObject.x() == 48);
    CHECK(textObject.y() == 136);
    CHECK(textObject.width() == 248);
    CHECK(textObject.height() == 19);
    CHECK(textObject.rotation() == 0);
    CHECK(textObject.name().empty());
    CHECK(textObject.type().empty());
    CHECK(textObject.visible());

    SUBCASE("Text related properties")
    {
      const auto text = textObject.text();
      REQUIRE(text);
      CHECK(text->text() == "Hello World");
      CHECK(text->wrap());
    }
  }
}