/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-12
 */

#ifndef INCLUDE_COMPONENTS_BACKGROUND_H
#define INCLUDE_COMPONENTS_BACKGROUND_H

//#include <SFML/Graphics/Sprite.hpp>
//#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <spdlog/spdlog.h>
#include <memory>

namespace sf
{
class Texture;
class Sprite;
}  /* sf */

namespace Components
{
//constex
class Background
{
public:
  Background()
  {
    m_sky_texture = std::make_unique<sf::Texture>();
    m_sky_texture->loadFromFile(m_day);
    m_sky_sprite.setTexture(*m_sky_texture);
    m_ground_texture = std::make_unique<sf::Texture>();
    m_ground_texture->loadFromFile(m_ground);
    m_ground_sprite.setTexture(*m_ground_texture);
  }

  explicit Background(const std::uint32_t& window_height) : Background()
  {
    m_ground_sprite.setPosition(0, window_height - m_ground_height);
  }

  void draw(sf::RenderWindow& window)
  {
    window.draw(m_sky_sprite);
    window.draw(m_ground_sprite);
  }

private:
  const std::uint32_t          m_ground_height{28};
  std::unique_ptr<sf::Texture> m_sky_texture;
  std::unique_ptr<sf::Texture> m_ground_texture;
  sf::Sprite                   m_sky_sprite;
  sf::Sprite                   m_ground_sprite;
  std::string                  m_day{"share/textures/background/day.png"};
  std::string                  m_ground{"share/textures/ground.png"};
};
}
#endif /* INCLUDE_COMPONENTS_BACKGROUND_H */
