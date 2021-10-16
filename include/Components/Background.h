/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-12
 */

#ifndef COMPONENTS_BACKGROUND_H
#define COMPONENTS_BACKGROUND_H

#include "Pipes.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <spdlog/spdlog.h>
#include <memory>

namespace Components
{
class Background
{
public:
  Background()
  {
    loadTexturesFiles();
    setTextures();
    const auto&        sky_size    = static_cast<sf::Vector2<float>>(m_sky_texture.getSize());
    const auto&        ground_size = static_cast<sf::Vector2<float>>(m_ground_texture.getSize());
    const auto         floor_width = m_window_size.height - sky_size.y - ground_size.y;
    sf::Vector2<float> floor_size(m_window_size.width, floor_width);
    m_pipes_1 = std::make_unique<PipePair>();
    m_pipes_2 = std::make_unique<PipePair>();
    m_pipes_2->setXPosition(m_window_size.width); //review this
    m_pipes_2->setColor(sf::Color::Green);
    m_ground_y = sky_size.y;

    m_ground_sprite.setPosition(m_ground_x, m_ground_y);
    m_floor.setSize(floor_size);
    m_floor.setPosition(0, sky_size.y + ground_size.y);
    m_floor.setFillColor(m_floor_color);
  }

  void draw(sf::RenderWindow& window)
  {
    window.draw(m_sky_sprite);
    window.draw(m_upper_sprite);
    window.draw(m_lower_sprite);
    m_pipes_1->draw(window);
    m_pipes_2->draw(window);
    window.draw(m_ground_sprite);
    window.draw(m_floor);
  }

  void move()
  {
    moveGround();
    m_pipes_1->move();
    m_pipes_2->move();
  }

  void setWindowSize(const sf::Vector2<std::uint32_t>& window_size)
  {
    m_window_size.height = static_cast<float>(window_size.y);
    m_window_size.width  = static_cast<float>(window_size.x);
    m_pipes_1->setWindowSize(window_size);
    m_pipes_2->setWindowSize(window_size);
  };

  void setXSpeed(float speed)
  {
    m_x_speed = speed;
    m_pipes_1->setXSpeed(speed);
    m_pipes_2->setXSpeed(speed);
  }

private:
  void loadTexturesFiles()
  {
    m_sky_texture.loadFromFile(m_day_file);
    m_ground_texture.loadFromFile(m_ground_file);
  }

  void setTextures()
  {
    m_sky_sprite.setTexture(m_sky_texture);
    m_ground_sprite.setTexture(m_ground_texture);
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

  WindowSize                m_window_size{480, 720};
  float                     m_x_speed{5};
  float                     m_ground_x{0};
  float                     m_ground_y{0};
  sf::Texture               m_sky_texture;
  sf::Texture               m_ground_texture;
  sf::Sprite                m_sky_sprite;
  sf::Sprite                m_ground_sprite;
  sf::Sprite                m_upper_sprite;
  sf::Sprite                m_lower_sprite;
  sf::RectangleShape        m_floor;
  const sf::Color           m_floor_color{245, 228, 138};
  const std::string         m_day_file{"share/textures/background/day.png"};
  const std::string         m_ground_file{"share/textures/ground.png"};
  std::unique_ptr<PipePair> m_pipes_1;
  std::unique_ptr<PipePair> m_pipes_2;
};

}  // namespace Components

#endif /* COMPONENTS_BACKGROUND_H */
