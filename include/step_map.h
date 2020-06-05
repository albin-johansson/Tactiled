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

#ifndef STEP_TILED_MAP_HEADER
#define STEP_TILED_MAP_HEADER

#include <string>
#include <vector>

#include "step_api.h"
#include "step_color.h"
#include "step_layer.h"
#include "step_properties.h"
#include "step_tileset.h"
#include "step_types.h"

namespace step {

// class StepComponent final {
// public:
// private:
//  std::string m_tiledVersion;
//  double m_jsonVersion{0};
//};

class Map final {
 public:
  enum class RenderOrder { RightDown, RightUp, LeftDown, LeftUp };
  enum class Orientation { Orthogonal, Isometric, Staggered, Hexagonal };
  enum class StaggerAxis { X, Y };
  enum class StaggerIndex { Odd, Even };

  STEP_API friend void from_json(const JSON&, Map&);

  STEP_QUERY bool infinite() const noexcept;

 private:
  int m_width{0};
  int m_height{0};
  int m_tileWidth{0};
  int m_tileHeight{0};
  int m_nextLayerID{0};
  int m_nextObjectID{0};
  std::vector<Layer> m_layers;
  std::vector<Tileset> m_tilesets;
  Properties m_properties;
  Orientation m_orientation{Orientation::Orthogonal};
  RenderOrder m_renderOrder{RenderOrder::RightDown};  // ONLY ORTHOGONAL
  StaggerAxis m_staggerAxis{StaggerAxis::X};  // (only staggered & hexagonal)
  StaggerIndex m_staggerIndex{StaggerIndex::Odd};  // ONLY STAGGERED/HEXAGONAL
  int m_hexSideLength{0};                          // ONLY HEXAGONAL
  Maybe<Color> m_backgroundColor;
  std::string m_tiledVersion;
  double m_jsonVersion{0};
  bool m_infinite{false};
};

STEP_API void from_json(const JSON& json, Map& map);

STEP_SERIALIZE_ENUM(Map::RenderOrder,
                    {{Map::RenderOrder::RightDown, "right-down"},
                     {Map::RenderOrder::RightUp, "right-up"},
                     {Map::RenderOrder::LeftDown, "left-down"},
                     {Map::RenderOrder::LeftUp, "left-up"}})

STEP_SERIALIZE_ENUM(Map::Orientation,
                    {{Map::Orientation::Orthogonal, "orthogonal"},
                     {Map::Orientation::Isometric, "isometric"},
                     {Map::Orientation::Staggered, "staggered"},
                     {Map::Orientation::Hexagonal, "hexagonal"}})

STEP_SERIALIZE_ENUM(Map::StaggerAxis,
                    {{Map::StaggerAxis::X, "x"}, {Map::StaggerAxis::Y, "y"}})

STEP_SERIALIZE_ENUM(Map::StaggerIndex,
                    {{Map::StaggerIndex::Odd, "odd"},
                     {Map::StaggerIndex::Even, "even"}})

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_map.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_TILED_MAP_HEADER
