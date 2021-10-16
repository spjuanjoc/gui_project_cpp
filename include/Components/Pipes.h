/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-15
 */

#ifndef COMPONENTS_PIPEPAIR_H
#define COMPONENTS_PIPEPAIR_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <spdlog/spdlog.h>
#include <algorithm>
#include <random>

namespace Components
{
constexpr auto       TEN_PERCENT   = 0.1F;
constexpr auto       FIFTY_PERCENT = 0.5F;
constexpr std::array pipe_y_pos{-100, -75, -50, -25, 0, 25, 50, 75, 100, 125, 150};

struct WindowSize
{
  float width;
  float height;
};

class PipePair
{
public:
  PipePair()
  {
    loadTexturesFiles();
    setTextures();

    m_y_offset   = m_window_size.height / 2;
    m_x_position = m_window_size.width * 2;

    m_upper_sprite.setPosition(m_x_position, m_y_position + m_y_offset);
    m_lower_sprite.setPosition(m_x_position, m_y_position - m_y_offset);
    m_texture_width = static_cast<float>(m_lower_texture.getSize().x);
  }

  void draw(sf::RenderWindow& window)
  {
    window.draw(m_upper_sprite);
    window.draw(m_lower_sprite);
  }

  void move()
  {
    if (m_x_position <= -(m_texture_width))
    {
      m_x_position = (m_window_size.width * 2); // review this
      m_y_position = nextPipesHeight();
    }

    m_x_position -= m_x_speed;
    m_upper_sprite.setPosition(m_x_position, m_y_position + m_y_offset);
    m_lower_sprite.setPosition(m_x_position, m_y_position - m_y_offset);
  }

  void setWindowSize(const sf::Vector2<std::uint32_t>& window_size)
  {
    m_window_size.height = static_cast<float>(window_size.y);
    m_window_size.width  = static_cast<float>(window_size.x);
  };

  void setXPosition(float x)
  {
    m_x_position += x + m_texture_width;
  };

  void setXSpeed(float speed)
  {
    m_x_speed = speed;
  }

  void setColor(const sf::Color& color)
  {
    m_upper_sprite.setColor(color);
    m_lower_sprite.setColor(color);
  }

private:
  void loadTexturesFiles()
  {
    m_image.loadFromFile(m_file);
    m_upper_texture.loadFromImage(m_image);
    m_image.flipVertically();
    m_lower_texture.loadFromImage(m_image);
  }

  void setTextures()
  {
    m_upper_sprite.setTexture(m_upper_texture);
    m_lower_sprite.setTexture(m_lower_texture);
  }

  static float nextPipesHeight()
  {
    std::vector<int> out;
    size_t           elements = 1;

    std::sample(std::begin(pipe_y_pos), std::end(pipe_y_pos), std::back_inserter(out), elements, std::mt19937{std::random_device{}()});
    fmt::print("a random number from {}: {}\n ", "pipe_y_pos", out[0]);

    return static_cast<float>(out[0]);
  }

  WindowSize        m_window_size{480, 720};
  float             m_x_speed{5};
  float             m_x_position{0};
  float             m_y_position{0};
  float             m_y_offset{0};
  float             m_x_offset{0};
  float             m_texture_width{0};
  sf::Texture       m_upper_texture;
  sf::Texture       m_lower_texture;
  sf::Sprite        m_upper_sprite;
  sf::Sprite        m_lower_sprite;
  sf::Image         m_image;
  const std::string m_file{"share/textures/pipe.png"};
};

}  // namespace Components

#endif /* COMPONENTS_PIPEPAIR_H */
