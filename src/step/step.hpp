/**
 * MIT License
 *
 * Copyright (c) 2020-2021 Albin Johansson
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

#include "animation.hpp"
#include "chunk.hpp"
#include "color.hpp"
#include "common.hpp"
#include "data.hpp"
#include "frame.hpp"
#include "grid.hpp"
#include "image_layer.hpp"
#include "layer.hpp"
#include "map.hpp"
#include "object.hpp"
#include "object_group.hpp"
#include "point.hpp"
#include "properties.hpp"
#include "property.hpp"
#include "step_api.hpp"
#include "step_detail.hpp"
#include "step_exception.hpp"
#include "step_fwd.hpp"
#include "terrain.hpp"
#include "text.hpp"
#include "tile.hpp"
#include "tile_layer.hpp"
#include "tile_offset.hpp"
#include "tileset.hpp"
#include "valid_property.hpp"
#include "wang_color.hpp"
#include "wang_set.hpp"
#include "wang_tile.hpp"