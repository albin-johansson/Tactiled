#include "step_layer.h"

#include "step_exception.h"
#include "step_utils.h"

namespace step {

Layer::Layer(const json& json)
{
  init_common(json);
  switch (type()) {
    case Layer::Type::TileLayer: {
      m_layerData.emplace<TileLayer>(json);
      break;
    }
    case Layer::Type::ObjectGroup: {
      m_layerData.emplace<ObjectGroup>(json);
      break;
    }
    case Layer::Type::ImageLayer: {
      m_layerData.emplace<ImageLayer>(json.get<ImageLayer>());
      break;
    }
    case Layer::Type::Group: {
      m_layerData.emplace<Group>(json.get<Group>());
      break;
    }
    default: {
      const auto id = std::to_string(static_cast<int>(type()));
      throw StepException{"Layer > Unknown layer type: " + id};
    }
  }
}

int Layer::id() const noexcept
{
  return m_id;
}

const TileLayer& Layer::as_tile_layer() const
{
  if (std::holds_alternative<TileLayer>(m_layerData)) {
    return std::get<TileLayer>(m_layerData);
  } else {
    throw StepException{"Layer > The layer isn't a tile layer!"};
  }
}

const ImageLayer& Layer::as_image_layer() const
{
  if (std::holds_alternative<ImageLayer>(m_layerData)) {
    return std::get<ImageLayer>(m_layerData);
  } else {
    throw StepException{"Layer > The layer isn't an image layer!"};
  }
}

const ObjectGroup& Layer::as_object_group() const
{
  if (std::holds_alternative<ObjectGroup>(m_layerData)) {
    return std::get<ObjectGroup>(m_layerData);
  } else {
    throw StepException{"Layer > The layer isn't an object group!"};
  }
}

const Group& Layer::as_group() const
{
  if (std::holds_alternative<Group>(m_layerData)) {
    return std::get<Group>(m_layerData);
  } else {
    throw StepException{"Layer > The layer isn't a group!"};
  }
}

bool Layer::is_tile_layer() const noexcept
{
  return m_type == Type::TileLayer;
}

bool Layer::is_image_layer() const noexcept
{
  return m_type == Type::ImageLayer;
}

bool Layer::is_object_group() const noexcept
{
  return m_type == Type::ObjectGroup;
}

bool Layer::is_group() const noexcept
{
  return m_type == Type::Group;
}

Layer::Type Layer::type() const noexcept
{
  return m_type;
}

int Layer::width() const noexcept
{
  return m_width;
}

int Layer::height() const noexcept
{
  return m_height;
}

int Layer::start_x() const noexcept
{
  return m_startX;
}

int Layer::start_y() const noexcept
{
  return m_startY;
}

bool Layer::visible() const noexcept
{
  return m_visible;
}

std::string Layer::name() const
{
  return m_name;
}

double Layer::offset_x() const noexcept
{
  return m_offsetX;
}

double Layer::offset_y() const noexcept
{
  return m_offsetY;
}

double Layer::opacity() const noexcept
{
  return m_opacity;
}

const Properties* Layer::properties() const noexcept
{
  return m_properties.get();
}

void Layer::init_common(const json& json)
{
  json.at("type").get_to(m_type);

  detail::safe_bind(json, "name", m_name);
  detail::safe_bind(json, "opacity", m_opacity);
  detail::safe_bind(json, "visible", m_visible);
  detail::safe_bind(json, "id", m_id);
  detail::safe_bind(json, "width", m_width);
  detail::safe_bind(json, "height", m_height);
  detail::safe_bind(json, "startx", m_startX);
  detail::safe_bind(json, "starty", m_startY);
  detail::safe_bind(json, "offsetx", m_offsetX);
  detail::safe_bind(json, "offsety", m_offsetY);

  m_properties = detail::safe_bind_unique<Properties>(json, "properties");
}

}  // namespace step
