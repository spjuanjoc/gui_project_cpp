/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-17
 */

#include "Components/Bird.h"
#include "Components/Background.h"
#include "Program/EventsHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace Components
{
constexpr auto       FLAP_FREQUENCY    = 80000;
constexpr float      FLAP_ANGLE        = -30.0F;
constexpr float      FALL_ROTATION     = 6.0F;
constexpr float      FLAP_MAX_VELOCITY = 20.0F;
constexpr float      FALL_MAX_VELOCITY = -20.0F;
constexpr int        FLAP_FALL_DELTA   = 10;
constexpr auto       DEAD_ANGLE        = -180;
const sf::Vector2f   FLAP_ACCELERATION{-0.0F, -10.0F};
const sf::Vector2f   FALL_ACCELERATION{0, 8.0F};
constexpr std::array textures{"share/textures/bird/1-mid.png",
                              "share/textures/bird/1-up.png",
                              "share/textures/bird/1-mid.png",
                              "share/textures/bird/1-down.png"};

Bird::Bird()
{
  Logger::Info("Configure bird");

  for (const auto& texture : textures)
  {
    auto frame = std::make_unique<sf::Texture>(); // ToDo move to stack
    frame->loadFromFile(texture);
    m_textures.emplace_back(std::move(frame));
  }

  m_sprite.setTexture(*m_textures[0]);
  m_sprite.setPosition(BIRD_START_X, BIRD_START_Y);

  float half_x = static_cast<float>(m_textures[0]->getSize().x) / 2.0F;
  float half_y = static_cast<float>(m_textures[0]->getSize().y) / 2.0F;
  m_sprite.setOrigin(half_x, half_y);
}

sf::Sprite& Bird::getSprite()
{
  return m_sprite;
}

void Bird::draw(sf::RenderWindow& window)
{
  m_sprite.setTexture(*m_textures[m_current_frame]);
  m_sprite.move(m_velocity);
  window.draw(m_sprite);
}

void Bird::flap()
{
  if (m_event->pressedKey() == Program::KEY_NAMES::Space && m_event->isRunning())
  {
    Logger::Trace("flap");
    m_current_frame = 3;
    m_acceleration  = FLAP_ACCELERATION;
    m_fall_start_height = static_cast<int>(m_sprite.getPosition().y - FLAP_FALL_DELTA);
    m_sprite.setRotation(FLAP_ANGLE);
  }
}

void Bird::fall()
{
  m_acceleration = FALL_ACCELERATION;
  m_sprite.rotate(FALL_ROTATION);
}

void Bird::wing()
{
  if (m_delta > FLAP_FREQUENCY)
  {
    Logger::Info("Move wings");
    m_delta         = 0;
    m_current_frame = (m_current_frame >= m_textures.size() - 1) ? 0 : m_current_frame + 1;
  }
}

void Bird::move(long long int elapsed_us)
{
  m_delta += elapsed_us;
  wing();
  flap();

  m_velocity += m_acceleration;
  m_velocity.y = std::clamp(m_velocity.y, FALL_MAX_VELOCITY, FLAP_MAX_VELOCITY);

  if (m_sprite.getPosition().y <= static_cast<float>(m_fall_start_height))
  {
    Logger::Info("fall");
    fall();
  }
}

void Bird::stand(long long int elapsed_us)
{
  m_acceleration = {0, 0};
  m_velocity = {0, 0};
  m_sprite.setRotation(0);
  m_fall_start_height = static_cast<int>(m_sprite.getPosition().y);

  if (!m_is_dead)
  {
    m_delta += elapsed_us;

//    if (m_current_frame == 0 || m_current_frame == 1)
//    {
//      stand_by.y += stand_by_height;
//      m_sprite.move(stand_by);
//    }
//    else if (m_current_frame == 2 || m_current_frame == 3)
//    {
//      stand_by.y -= stand_by_height;
//      m_sprite.move(stand_by);
//    }

    wing();
  }
}

void Bird::setEventHandler(Program::EventsHandler* event)
{
  m_event = event;
}

void Bird::setWindow(sf::RenderWindow* window)
{
  m_window            = window;
  m_window_width      = static_cast<float>(m_window->getSize().x);
  m_window_height     = static_cast<float>(m_window->getSize().y);
  const auto& start_x = m_window_width / 3;
  const auto& start_y = m_window_height / 2;
  m_sprite.setPosition(start_x, start_y);
}

void Bird::setBackground(Background* background)
{
  m_background = background;
}

void Bird::die()
{
  m_is_dead = true;
  m_event->pause();
  m_sprite.setRotation(DEAD_ANGLE);
  Logger::Info("Dead 💀");
}

}  // namespace Components
