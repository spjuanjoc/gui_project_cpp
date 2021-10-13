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

constexpr std::uint32_t GRAVITY = 10;
constexpr std::uint32_t FLAP_HEIGHT = 20;

class Bird
{
public:
  Bird()
  {
    m_texture = std::make_unique<sf::Texture>();
    m_texture->loadFromFile(m_wing_up_img);
    m_sprite.setTexture(*m_texture);
  }

  explicit Bird( std::uint32_t x, std::uint32_t y) : Bird()
  {
    m_x_position = x;
    m_y_position = y;
  }

  sf::Sprite& draw()
  {
    m_sprite.setPosition(m_x_position, m_y_position);
    return m_sprite;
  }

  void fall(const std::uint32_t& height)
  {
    m_y_position += GRAVITY * m_mass * m_difficulty;

    if (m_y_position >= height)
    {
      m_y_position = 0;
    }
    draw();
  }

  void flap()
  {
    m_y_position -= FLAP_HEIGHT * m_flap_strength;
    draw();
  }

private:
  std::uint32_t                m_x_position{};
  std::uint32_t                m_y_position{};
  std::uint32_t                m_difficulty{1};
  std::uint32_t                m_mass{1};
  std::uint32_t                m_flap_strength{1};
  std::unique_ptr<sf::Texture> m_texture;
  sf::Sprite                   m_sprite;
  std::string                  m_wing_up_img{"share/textures/bird/1-1.png"};
  std::string                  m_wing_mid_img{"share/textures/bird/1-2.png"};
  std::string                  m_wing_down_img{"share/textures/bird/1-3.png"};
};
}
#endif /* INCLUDE_COMPONENTS_BIRD_H */
