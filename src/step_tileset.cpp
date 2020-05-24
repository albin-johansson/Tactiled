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

// This is what a tileset looks like when it isn't embedded in a map
//  "tilesets":[
//  {
//    "firstgid":1,
//        "source":"terrain.json"
//  }],

STEP_DEF
Tileset::Tileset(const JSON& json)
{
  if (json.contains("source")) {
    m_firstGID = json.at("firstgid").get<int>();
    m_source = json.at("source").get<std::string>();
    load_from(detail::parse_json(m_source.c_str()));
  } else {
    load_from(json);
  }
}

STEP_DEF
std::unique_ptr<Tileset> Tileset::unique(const JSON& json)
{
  return std::make_unique<Tileset>(json);
}

STEP_DEF
void Tileset::load_from(const JSON& json)
{
  if (json.at("type").get<std::string>() != "tileset") {
    throw StepException{"Tileset > \"type\" must be \"tileset\"!"};
  }

  m_firstGID = json.at("firstgid").get<int>();
  m_tileWidth = json.at("tilewidth").get<int>();
  m_tileHeight = json.at("tileheight").get<int>();
  m_tileCount = json.at("tilecount").get<int>();
  m_nColumns = json.at("columns").get<int>();
  m_imageWidth = json.at("imagewidth").get<int>();
  m_imageHeight = json.at("imageheight").get<int>();
  m_margin = json.at("margin").get<int>();
  m_spacing = json.at("spacing").get<int>();
  m_image = json.at("image").get<std::string>();

  // TODO properties

  //  if (json.count("properties")) {
  //    for (const auto& [key, value] : json.at("properties").items()) {
  //    }
  //  }

  for (const auto& [key, value] : json.at("tiles").items()) {
    m_tiles.push_back(value.get<Tile>());
  }

  m_name = json.at("name").get<std::string>();

  if (json.count("backgroundcolor")) {
    m_backgroundColor = Color{json.at("backgroundcolor").get<std::string>()};
  }

  if (json.count("transparentcolor")) {
    m_transparentColor = Color{json.at("transparentcolor").get<std::string>()};
  }

  if (json.count("tiledversion")) {
    m_tiledVersion = json.at("tiledversion").get<std::string>();
  }

  if (json.count("version")) {
    m_jsonVersion = json.at("version").get<std::string>();
  }
}

}  // namespace step

#endif  // STEP_TILESET_SOURCE
