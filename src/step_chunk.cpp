#include "step_chunk.h"

namespace step {

Chunk::Chunk(const JSON& json)
    : m_x{json.at("x").get<int>()},
      m_y{json.at("y").get<int>()},
      m_width{json.at("width").get<int>()},
      m_height{json.at("height").get<int>()},
      m_data{json.at("data")}
{}

int Chunk::x() const noexcept
{
  return m_x;
}

int Chunk::y() const noexcept
{
  return m_y;
}

int Chunk::width() const noexcept
{
  return m_width;
}

int Chunk::height() const noexcept
{
  return m_height;
}

const detail::Data& Chunk::data() const noexcept
{
  return m_data;
}

}  // namespace step
