/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-12
 */

#ifndef COMPONENTS_BIRD_H
#define COMPONENTS_BIRD_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <spdlog/spdlog.h>
#include <memory>

namespace Components
{
constexpr std::uint32_t GRAVITY     = 10;
constexpr std::uint32_t FLAP_HEIGHT = 18;

class Bird
{
public:
  Bird()
  {
    m_texture = std::make_unique<sf::Texture>();
    m_texture->loadFromFile(m_wing_up_img);
    m_sprite.setTexture(*m_texture);
  }

  sf::Sprite& draw()
  {
    m_sprite.setPosition(m_x_position, m_y_position);
    return m_sprite;
  }

  void fall(const std::uint32_t& height)
  {
    m_y_position += GRAVITY * m_mass * m_difficulty;

    if (m_y_position >= static_cast<float>(height))
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
  float                        m_x_position{50};
  float                        m_y_position{};
  float                        m_difficulty{1};
  float                        m_mass{1};
  float                        m_flap_strength{1};
  std::unique_ptr<sf::Texture> m_texture;
  sf::Sprite                   m_sprite;
  std::string                  m_wing_up_img{"share/textures/bird/1-1.png"};
  std::string                  m_wing_mid_img{"share/textures/bird/1-2.png"};
  std::string                  m_wing_down_img{"share/textures/bird/1-3.png"};
};

}  // namespace Components

#endif /* COMPONENTS_BIRD_H */
