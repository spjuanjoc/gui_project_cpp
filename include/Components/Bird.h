/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-12
 */

#ifndef INCLUDE_COMPONENTS_BIRD_H
#define INCLUDE_COMPONENTS_BIRD_H

#include <spdlog/spdlog.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

namespace Components
{
class Bird
{
public:
  Bird()
  {
    m_texture = std::make_unique<sf::Texture>();
    m_texture->loadFromFile("share/textures/bird/1-1.png");
    m_sprite.setTexture(*m_texture);
  }

  explicit Bird( std::uint32_t x, std::uint32_t y) : Bird()
  {
    m_x_pos = x;
    m_y_pos = y;
  }

  sf::Sprite& draw()
  {
    m_sprite.setPosition(m_x_pos, m_y_pos);
    return m_sprite;
  }

  void flap()
  {
    m_speed = -200;
  }

  void fall(std::int64_t& delta)
  {
//    m_speed += m_delta;
//    m_y_pos += m_speed * m_delta;
    m_y_pos += 10;
    if (m_y_pos >= 600)
    {
      m_y_pos = 0;
    }
    draw();
//    spdlog::info("speed: {}, y: {}, delta: {}.", m_speed, m_y_pos, delta);
  }

private:
  std::uint32_t                m_x_pos{};
  std::uint32_t                m_y_pos{};
  float                        m_speed{100};
  float                        m_delta{1};
  std::unique_ptr<sf::Texture> m_texture;
  sf::Sprite                   m_sprite;
};
}
#endif /* INCLUDE_COMPONENTS_BIRD_H */
