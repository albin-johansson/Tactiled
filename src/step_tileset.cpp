/**
 * MIT License
 *
 * Copyright (c) 2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef STEP_TILESET_SOURCE
#define STEP_TILESET_SOURCE

#include "step_tileset.h"

#include "step_exception.h"
#include "step_utils.h"

namespace step {

STEP_DEF
void load_from(const JSON& json, Tileset& set)
{
  if (json.at("type").get<std::string>() != "tileset") {
    throw StepException{"Tileset > \"type\" must be \"tileset\"!"};
  }

  json.at("tilewidth").get_to(set.m_tileWidth);
  json.at("tileheight").get_to(set.m_tileHeight);
  json.at("tilecount").get_to(set.m_tileCount);
  json.at("columns").get_to(set.m_nColumns);
  json.at("imagewidth").get_to(set.m_imageWidth);
  json.at("imageheight").get_to(set.m_imageHeight);
  json.at("margin").get_to(set.m_margin);
  json.at("spacing").get_to(set.m_spacing);
  json.at("image").get_to(set.m_image);

  if (json.contains("firstgid")) {
    json.at("firstgid").get_to(set.m_firstGID);
  }

  if (json.contains("properties")) {
    // TODO properties
  }

  if (json.contains("tiles")) {
    for (const auto& [key, value] : json.at("tiles").items()) {
      set.m_tiles.push_back(value.get<Tile>());
    }
  }

  json.at("name").get_to(set.m_name);

  if (json.count("backgroundcolor")) {
    // TODO add color from_json
    set.m_backgroundColor =
        Color{json.at("backgroundcolor").get<std::string>()};
  }

  if (json.count("transparentcolor")) {
    // TODO add color from_json
    set.m_transparentColor =
        Color{json.at("transparentcolor").get<std::string>()};
  }

  if (json.count("tiledversion")) {
    json.at("tiledversion").get_to(set.m_tiledVersion);
  }

  if (json.count("version")) {
    json.at("version").get_to(set.m_jsonVersion);
  }
}

STEP_DEF void from_json(const JSON& json, Tileset& set)
{
  if (json.contains("source")) {
    json.at("firstgid").get_to(set.m_firstGID);
    json.at("source").get_to(set.m_source);

    const auto external = detail::parse_json(set.m_source.c_str());
    load_from(external, set);
  } else {
    load_from(json, set);
  }
}

}  // namespace step

#endif  // STEP_TILESET_SOURCE
