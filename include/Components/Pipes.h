/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-15
 */

#ifndef COMPONENTS_PIPEPAIR_H
#define COMPONENTS_PIPEPAIR_H

#include "Program/Logger.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <random>

namespace Components
{
constexpr auto       TEN_PERCENT   = 0.1F;
constexpr auto       INITIAL_SPEED  = 5;
constexpr auto       INITIAL_WIDTH  = 480;
constexpr auto       INITIAL_HEIGHT = 720;


struct WindowSize
{
  float width;
  float height;
};

class PipePair
{
public:
  PipePair();

  void draw(sf::RenderWindow& window);

  void move();

  void stop();

  void setWindowSize(const sf::Vector2<std::uint32_t>& window_size);

  void setXPosition(float x);

  void setXSpeed(float speed);

  void setColor(const sf::Color& color);

  sf::Sprite& getLowSprite();

  sf::Sprite& getUpSprite();

private:
  void loadTexturesFiles();

  void setTextures();

  static float nextPipesHeight();

  bool              m_is_stopped{};
  float             m_x_speed{INITIAL_SPEED};
  float             m_x_position{0};
  float             m_y_position{0};
  float             m_y_offset{0};
  float             m_x_offset{0};
  float             m_texture_width{0};
  WindowSize        m_window_size{INITIAL_WIDTH, INITIAL_HEIGHT};
  sf::Texture       m_upper_texture;
  sf::Texture       m_lower_texture;
  sf::Sprite        m_lower_sprite;
  sf::Sprite        m_upper_sprite;
  sf::Image         m_image;
  const std::string m_file{"share/textures/pipe.png"};
};

}  // namespace Components

#endif /* COMPONENTS_PIPEPAIR_H */
