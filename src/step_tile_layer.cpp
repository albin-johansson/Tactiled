#include "step_tile_layer.hpp"

#include "step_utils.hpp"

namespace step {

TileLayer::TileLayer(const json& json)
{
  detail::safe_bind(json, "compression", m_compression);
  detail::safe_bind(json, "encoding", m_encoding);

  if (json.contains("chunks")) {
    m_chunks = detail::fill<std::vector<chunk>>(json, "chunks");
  }

  if (json.contains("data")) {
    m_data = std::make_unique<detail::data>(json.at("data"));
  }
}

TileLayer::Encoding TileLayer::encoding() const noexcept
{
  return m_encoding;
}

TileLayer::Compression TileLayer::compression() const noexcept
{
  return m_compression;
}

const detail::data* TileLayer::data() const
{
  return m_data.get();
}

const std::vector<chunk>& TileLayer::chunks() const noexcept
{
  return m_chunks;
}

}  // namespace step
