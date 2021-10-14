/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-12
 */

#ifndef COMPONENTS_BACKGROUND_H
#define COMPONENTS_BACKGROUND_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <spdlog/spdlog.h>
#include <memory>

namespace Components
{
constexpr auto TEN_PERCENT   = 0.1F;
constexpr auto FIFTY_PERCENT = 0.5F;

struct WindowSize
{
  float x;
  float y;
};

class Background
{
public:
  Background()
  {
    loadTexturesFiles();
    setTextures();
  }

  explicit Background(const sf::Vector2<std::uint32_t>& window_size) : Background()
  {
    m_window_size.y = static_cast<float>(window_size.y);
    m_window_size.x = static_cast<float>(window_size.x);
    const auto& sky_size = static_cast<sf::Vector2<float>>(m_sky_texture.getSize());
    const auto& ground_size = static_cast<sf::Vector2<float>>(m_ground_texture.getSize());
    const auto floor_width = m_window_size.y - sky_size.y - ground_size.y;
    sf::Vector2<float> floor_size(m_window_size.x, floor_width);
    m_ground_y = sky_size.y;
    m_pipe_offset = sky_size.y / 2;
    m_pipe_x = sky_size.x / 2;

    m_ground_sprite.setPosition(m_ground_x, m_ground_y);
    m_upper_sprite.setPosition(m_pipe_x, m_pipe_y + m_pipe_offset);
    m_lower_sprite.setPosition(m_pipe_x, m_pipe_y - m_pipe_offset);
    m_floor.setSize(floor_size);
    m_floor.setPosition(0, sky_size.y + ground_size.y);
    m_floor.setFillColor(m_floor_color);
  }

  void draw(sf::RenderWindow& window)
  {
    window.draw(m_sky_sprite);
    window.draw(m_upper_sprite);
    window.draw(m_lower_sprite);
    window.draw(m_ground_sprite);
    window.draw(m_floor);
  }

  void move()
  {
    moveGround();
    movePipes();
  }

private:
  void loadTexturesFiles()
  {
    m_sky_texture.loadFromFile(m_day_file);
    m_ground_texture.loadFromFile(m_ground_file);
    m_pipe_image.loadFromFile(m_pipe_file);
    m_upper_pipe.loadFromImage(m_pipe_image);
    m_pipe_image.flipVertically();
    m_lower_pipe.loadFromImage(m_pipe_image);
  }

  void setTextures()
  {
    m_sky_sprite.setTexture(m_sky_texture);
    m_ground_sprite.setTexture(m_ground_texture);
    m_upper_sprite.setTexture(m_upper_pipe);
    m_lower_sprite.setTexture(m_lower_pipe);
  }

  void moveGround()
  {
    const auto width = static_cast<float>(m_ground_texture.getSize().x);
    if (m_ground_x <= -(width * TEN_PERCENT))
    {
      m_ground_x = 0;
    }

    m_ground_x -= m_x_speed;
    m_ground_sprite.setPosition(m_ground_x, m_ground_y);
  }

  void movePipes()
  {
    if (m_pipe_x <= -(m_window_size.x * FIFTY_PERCENT))
    {
      m_pipe_x = m_window_size.x;
    }

    m_pipe_x -= m_x_speed;
    m_upper_sprite.setPosition(m_pipe_x, m_pipe_y + m_pipe_offset);
    m_lower_sprite.setPosition(m_pipe_x, m_pipe_y - m_pipe_offset);
  }


  WindowSize         m_window_size{0, 0};
  float              m_x_speed{2};
  float              m_ground_x{0};
  float              m_ground_y{0};
  float              m_pipe_x{0};
  float              m_pipe_y{0};
  float              m_pipe_offset{0};
  sf::Texture        m_sky_texture;
  sf::Texture        m_ground_texture;
  sf::Texture        m_upper_pipe;
  sf::Texture        m_lower_pipe;
  sf::Sprite         m_sky_sprite;
  sf::Sprite         m_ground_sprite;
  sf::Sprite         m_upper_sprite;
  sf::Sprite         m_lower_sprite;
  sf::Image          m_pipe_image;
  sf::RectangleShape m_floor;
  const sf::Color    m_floor_color{245, 228, 138};
  const std::string  m_day_file{"share/textures/background/day.png"};
  const std::string  m_ground_file{"share/textures/ground.png"};
  const std::string  m_pipe_file{"share/textures/pipe.png"};
};
}
#endif /* COMPONENTS_BACKGROUND_H */
