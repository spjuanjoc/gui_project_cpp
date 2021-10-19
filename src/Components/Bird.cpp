/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-17
 */

#include "Components/Bird.h"
#include "Program/EventsHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace Components
{
constexpr auto       FLAP_UP_ANGLE   = -10;
constexpr auto       FLAP_DOWN_ANGLE = 10;
constexpr auto       FLAP_FREQUENCY  = 60000;
constexpr std::array textures{"share/textures/bird/1-mid.png",
                              "share/textures/bird/1-up.png",
                              "share/textures/bird/1-mid.png",
                              "share/textures/bird/1-down.png"};

Components::Bird::Bird()
{
  for (const auto& texture : textures)
  {
    auto frame = std::make_unique<sf::Texture>();
    frame->loadFromFile(texture);
    m_textures.emplace_back(std::move(frame));
  }
  m_sprite.setTexture(*m_textures[0]);
  m_sprite.setPosition(m_x_position, m_y_position);
}

sf::Sprite& Components::Bird::getSprite()
{
  return m_sprite;
}

void Components::Bird::draw(sf::RenderWindow& window)
{
  m_sprite.setTexture(*m_textures[m_current_frame]);
  m_sprite.setRotation(m_angle);
  m_sprite.setPosition(m_x_position, m_y_position);
  window.draw(m_sprite);
}

void Components::Bird::fall()
{
  if (!m_is_flapping)
  {
    m_y_position += GRAVITY * m_mass * m_difficulty;
    Logger::Trace("fall bird x:{}", m_y_position);
//    m_angle = 0;

    if (m_y_position >= static_cast<float>(m_window_height))
    {
      m_y_position = 0;// m_sky_height - m_textures[0]->getSize().y;
      //    m_event->pause();
    }
  }
}

void Components::Bird::wing()
{
  if (m_delta > FLAP_FREQUENCY)
  {
    m_delta         = 0;
    m_current_frame = (m_current_frame >= m_textures.size() - 1) ? 0 : m_current_frame + 1;
    m_angle = 0;
  }
}

void Components::Bird::flap()
{
  if (m_event->pressedKey() == Program::KEY_NAMES::Space && m_event->isRunning())
  {
    m_y_delta += m_flap_strength;
    m_current_frame = 3;
    m_angle         = FLAP_UP_ANGLE;
    m_is_flapping   = true;
  }

  if (m_is_flapping)
  {
    m_y_delta += FLAP_HEIGHT + m_flap_strength;
    m_y_position = m_y_position - m_y_delta;
  }

  if (m_y_delta >= 33)
  {
    m_y_delta    = 0;
    m_is_flapping = false;
  }
}

void Components::Bird::move(long long int elapsed_us)
{
  m_delta += elapsed_us;
  wing();
  flap();
  fall();
}

void Components::Bird::stand(long long int elapsed_us)
{
  m_delta += elapsed_us;

  if (m_current_frame == 0 || m_current_frame == 1)
  {
    m_y_position += 1;
  }
  else
  {
    m_y_position -= 1;
  }

  m_angle = 0;

  wing();
}

void Components::Bird::setEventHandler(Program::EventsHandler* event)
{
  m_event = event;
}

void Components::Bird::setWindow(sf::RenderWindow* window)
{
  m_window        = window;
  m_window_width  = static_cast<float>(m_window->getSize().x);
  m_window_height = static_cast<float>(m_window->getSize().y);
  m_x_position    = m_window_width / 3;
  m_y_position    = m_window_height / 2;
  m_sprite.setPosition(m_x_position, m_y_position);
}

}  // namespace Components
