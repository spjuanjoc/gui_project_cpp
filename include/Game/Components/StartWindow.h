/**
 * @brief Declares the start window class.
 *
 * @author  spjuanjoc
 * @date    2024-04-14
 */

#ifndef INCLUDE_GAME_COMPONENTS_STARTWINDOW_H
#define INCLUDE_GAME_COMPONENTS_STARTWINDOW_H

#include "Game/Components/IDrawable.h"

#include <imgui.h>

#include <imgui-SFML.h>

namespace Game::Components
{

constexpr auto  START_TEXT     = "TO START PRESS ENTER";
constexpr auto  START_FILENAME = "share/textures/start.png";


class StartWindow : virtual public IDrawable
{
public:
  StartWindow();

  void draw(sf::RenderWindow& window) override;

protected:
  void loadTexturesFiles() override;

  void setTextures() override;

  void setText(const ImVec2& position);

private:
  std::string_view m_text { START_TEXT };
  sf::Texture      m_texture;
  sf::Sprite       m_sprite;
};

}  // namespace Game::Components

#endif /* INCLUDE_GAME_COMPONENTS_STARTWINDOW_H */
