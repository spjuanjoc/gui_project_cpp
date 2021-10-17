/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-17
 */

#include "Components/Bird.h"
#include "Program/EventsHandler.h"

Components::Bird::Bird()
{
  m_texture = std::make_unique<sf::Texture>();
  m_texture->loadFromFile(m_wing_up_img);
  m_sprite.setTexture(*m_texture);
}

sf::Sprite& Components::Bird::draw()
{
  m_sprite.setPosition(m_x_position, m_y_position);
  return m_sprite;
}

void Components::Bird::fall(const uint32_t& height)
{
  m_y_position += GRAVITY * m_mass * m_difficulty;

  if (m_y_position >= static_cast<float>(height))
  {
    m_y_position = 0;
  }
  draw();
}

void Components::Bird::flap()
{
  if (m_event->pressedKey() == Program::KEY_NAMES::Space)
  {
    Logger::Trace("flap");
    m_y_position -= FLAP_HEIGHT * m_flap_strength;
    draw();
  }
}

void Components::Bird::setEventHandler(Program::EventsHandler* event)
{
  m_event = event;
}
void Components::Bird::move(std::uint32_t window_height)
{
  fall(window_height);
  flap();
}
