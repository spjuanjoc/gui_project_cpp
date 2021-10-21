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
#include <memory>

namespace Components
{
class Background
{
public:
  Background();

  void draw(sf::RenderWindow& window);

  void move();

  void stop();

  void setWindowSize(const sf::Vector2<std::uint32_t>& window_size);

  void setXSpeed(float speed);

  sf::Sprite& getSky();
  sf::Sprite& getGround();

  std::weak_ptr<PipePair> getPipes1();
  std::weak_ptr<PipePair> getPipes2();

  void moveGround();

private:

  void loadTexturesFiles();

  void setTextures();

  bool                      m_is_stopped{};
  float                     m_x_speed{INITIAL_SPEED};
  float                     m_ground_x{0};
  float                     m_ground_y{0};
  WindowSize                m_window_size{INITIAL_WIDTH, INITIAL_HEIGHT};
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
  std::shared_ptr<PipePair> m_pipes_1;
  std::shared_ptr<PipePair> m_pipes_2;
};

}  // namespace Components

#endif /* COMPONENTS_BACKGROUND_H */
