/**
 * @brief Declares the start window class.
 *
 * @author  spjuanjoc
 * @date    2024-04-14
 */

#ifndef INCLUDE_GAME_COMPONENTS_STARTWINDOW_H
#define INCLUDE_GAME_COMPONENTS_STARTWINDOW_H

#include <imgui.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <imgui-SFML.h>

namespace Components
{

constexpr auto  START_TEXT     = "TO START PRESS ENTER";
constexpr auto  START_FILENAME = "share/textures/start.png";
constexpr float HALF_DIVISOR   = 2.0F;


class StartWindow
{
public:
  StartWindow();

  void draw(sf::RenderWindow& window);

private:
  void loadTexturesFiles();

  void setTextures();

  void setText(const ImVec2& position);

  std::string_view m_text { START_TEXT };
  sf::Texture      m_texture;
  sf::Sprite       m_sprite;
};

}  // namespace Components

#endif /* INCLUDE_GAME_COMPONENTS_STARTWINDOW_H */
