/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-17
 */

#include "Components/Background.h"

namespace Components
{

Background::Background()
{
  loadTexturesFiles();
  setTextures();
  const auto&        sky_size    = static_cast<sf::Vector2<float>>(m_sky_texture.getSize());
  const auto&        ground_size = static_cast<sf::Vector2<float>>(m_ground_texture.getSize());
  const auto         floor_width = m_window_size.height - sky_size.y - ground_size.y;
  sf::Vector2<float> floor_size(m_window_size.width, floor_width);
  m_pipes_1 = std::make_unique<PipePair>();
  m_pipes_2 = std::make_unique<PipePair>();
  m_pipes_2->setXPosition(m_window_size.width);  //review this
  m_pipes_2->setColor(sf::Color::Green);
  m_ground_y = sky_size.y;

  m_ground_sprite.setPosition(m_ground_x, m_ground_y);
  m_floor.setSize(floor_size);
  m_floor.setPosition(0, sky_size.y + ground_size.y);
  m_floor.setFillColor(m_floor_color);
}

void Background::draw(sf::RenderWindow& window)
{
  window.draw(m_sky_sprite);
  window.draw(m_upper_sprite);
  window.draw(m_lower_sprite);
  m_pipes_1->draw(window);
  m_pipes_2->draw(window);
  window.draw(m_ground_sprite);
  window.draw(m_floor);
}

void Background::move()
{
  m_pipes_1->move();
  m_pipes_2->move();
}

void Background::setWindowSize(const sf::Vector2<std::uint32_t>& window_size)
{
  m_window_size.height = static_cast<float>(window_size.y);
  m_window_size.width  = static_cast<float>(window_size.x);
  m_pipes_1->setWindowSize(window_size);
  m_pipes_2->setWindowSize(window_size);
}

void Background::setXSpeed(float speed)
{
  m_x_speed = speed;
  m_pipes_1->setXSpeed(speed);
  m_pipes_2->setXSpeed(speed);
}

void Background::loadTexturesFiles()
{
  m_sky_texture.loadFromFile(m_day_file);
  m_ground_texture.loadFromFile(m_ground_file);
}

void Background::setTextures()
{
  m_sky_sprite.setTexture(m_sky_texture);
  m_ground_sprite.setTexture(m_ground_texture);
}

void Background::moveGround()
{
  const auto width = static_cast<float>(m_ground_texture.getSize().x);
  if (m_ground_x <= -(width * TEN_PERCENT))
  {
    m_ground_x = 0;
  }

  m_ground_x -= m_x_speed;
  m_ground_sprite.setPosition(m_ground_x, m_ground_y);
}

}  // namespace Components
