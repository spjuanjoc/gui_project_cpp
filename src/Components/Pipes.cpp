/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-17
 */

#include "Components/Pipes.h"
#include <Program/Logger.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <random>

namespace Components
{
constexpr std::array PIPE_Y_POS{-75, -70, -65, -60, -55, -50, -45, -40, -35, -30, -25,
                                -20, -15, -10, -5,  0,   5,   10,  15,  20,  25,  30,
                                35,  40,  45,  50,  55,  60,  65,  70,  75,  80,  85,
                                90,  95,  100, 105, 110, 115, 120, 125};

PipePair::PipePair()
{
  Logger::Info("Configure pipes");
  loadTexturesFiles();
  setTextures();

  m_y_offset   = m_window_size.height / 2;
  m_x_position = m_window_size.width * 2;

  m_lower_sprite.setPosition(m_x_position, m_y_position + m_y_offset);
  m_upper_sprite.setPosition(m_x_position, m_y_position - m_y_offset);
  m_texture_width = static_cast<float>(m_lower_texture.getSize().x);
}

void PipePair::draw(sf::RenderWindow& window)
{
  window.draw(m_lower_sprite);
  window.draw(m_upper_sprite);
}

void PipePair::move()
{
  if (m_x_position <= -(m_texture_width))
  {
    m_x_position = (m_window_size.width * 2);  // review this
    m_y_position = nextPipesHeight();
  }

  m_x_position -= m_x_speed;
  m_lower_sprite.setPosition(m_x_position, m_y_position + m_y_offset);
  m_upper_sprite.setPosition(m_x_position, m_y_position - m_y_offset);
}

void PipePair::setWindowSize(const sf::Vector2<std::uint32_t>& window_size)
{
  m_window_size.height = static_cast<float>(window_size.y);
  m_window_size.width  = static_cast<float>(window_size.x);
}

void PipePair::setXPosition(float x)
{
  m_x_position += x + m_texture_width;
}

void PipePair::setXSpeed(float speed)
{
  m_x_speed = speed;
}

void PipePair::setColor(const sf::Color& color)
{
  m_lower_sprite.setColor(color);
  m_upper_sprite.setColor(color);
}

void PipePair::loadTexturesFiles()
{
  m_image.loadFromFile(m_file);
  m_upper_texture.loadFromImage(m_image);
  m_image.flipVertically();
  m_lower_texture.loadFromImage(m_image);
}

void PipePair::setTextures()
{
  m_lower_sprite.setTexture(m_upper_texture);
  m_upper_sprite.setTexture(m_lower_texture);
}

float PipePair::nextPipesHeight()
{
  std::vector<int> out;
  const size_t     elements = 1;

  std::sample(std::begin(PIPE_Y_POS),
              std::end(PIPE_Y_POS),
              std::back_inserter(out),
              elements,
              std::mt19937{std::random_device{}()});
  Logger::Debug("pipes position {} ", out[0]);

  return static_cast<float>(out[0]);
}

void PipePair::stop()
{
  m_is_stopped = true;
}

sf::Sprite& PipePair::getLowSprite()
{
  return m_upper_sprite;
}

sf::Sprite& PipePair::getUpSprite()
{
  return m_lower_sprite;
}

}  // namespace Components
