#ifndef STEP_TILE_LAYER_HEADER
#define STEP_TILE_LAYER_HEADER

#include <memory>

#include "chunk.hpp"
#include "data.hpp"
#include "step_api.hpp"
#include "types.hpp"
#include "utils.hpp"

namespace step {

/**
 * \class tile_layer
 *
 * \brief Represents the API for layers that represent "tile layers", that
 * mainly hold tile data.
 *
 * \since 0.1.0
 *
 * \headerfile step_tile_layer.hpp
 */
class tile_layer final
{
 public:
  /**
   * \enum tile_layer::compression
   *
   * \brief Provides values for the different kinds of compression used by
   * layers.
   *
   * \since 0.1.0
   */
  enum class compression
  {
    zlib,
    gzip,
    none
  };

  /**
   * \enum tile_layer::encoding
   *
   * \brief Provides identifiers for the different encodings used by layers.
   *
   * \since 0.1.0
   */
  enum class encoding
  {
    csv,
    base64
  };

  explicit tile_layer(const json& json)
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

  /**
   * \brief Returns the encoding used by the tile layer.
   *
   * \details The default value of this property is `csv`.
   *
   * \return the encoding used by the tile layer.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto get_encoding() const noexcept -> encoding
  {
    return m_encoding;
  }

  /**
   * \brief Returns the compression used by the tile layer.
   *
   * \details The default value of this property is `none`.
   *
   * \return the compression used by the tile layer.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto get_compression() const noexcept -> compression
  {
    return m_compression;
  }

  /**
   * \brief Returns a pointer to the tile data associated with the tile layer.
   *
   * \details This property is optional.
   *
   * \warning Do not claim ownership of the returned pointer.
   *
   * \return the tile data associated with the tile layer; null if there is
   * no such data.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto data() const -> const detail::data*
  {
    return m_data.get();
  }

  /**
   * \brief Returns the chunks associated with the tile layer.
   *
   * \return the chunks associated with the tile layer.
   *
   * \since 0.1.0
   */
  [[nodiscard]] auto chunks() const noexcept -> const std::vector<chunk>&
  {
    return m_chunks;
  }

 private:
  encoding m_encoding{encoding::csv};
  compression m_compression{compression::none};
  std::unique_ptr<detail::data> m_data;
  std::vector<chunk> m_chunks;
};

NLOHMANN_JSON_SERIALIZE_ENUM(tile_layer::compression,
                             {{tile_layer::compression::none, ""},
                              {tile_layer::compression::gzip, "gzip"},
                              {tile_layer::compression::zlib, "zlib"}})

NLOHMANN_JSON_SERIALIZE_ENUM(tile_layer::encoding,
                             {{tile_layer::encoding::csv, "csv"},
                              {tile_layer::encoding::base64, "base64"}})

}  // namespace step

#endif  // STEP_TILE_LAYER_HEADER