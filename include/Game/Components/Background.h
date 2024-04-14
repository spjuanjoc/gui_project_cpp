/**
 * @brief Declares the background class.
 *
 * @author  spjuanjoc
 * @date    2024-04-14
 */

#ifndef COMPONENTS_BACKGROUND_H
#define COMPONENTS_BACKGROUND_H

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Components
{
constexpr auto BACKGROUND_FILENAME = "share/textures/background/regular_pine.png";

class Background
{
public:
  Background();

  void draw(sf::RenderWindow& window);

private:
  void loadTexturesFiles();

  void setTextures();

  sf::Texture      m_texture;
  sf::Sprite       m_sprite;
  std::string_view m_file { BACKGROUND_FILENAME };
};

}  // namespace Components

#endif /* COMPONENTS_BACKGROUND_H */
