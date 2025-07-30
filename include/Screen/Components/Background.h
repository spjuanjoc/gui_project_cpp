/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2021-10-12
 */

#ifndef COMPONENTS_BACKGROUND_H
#define COMPONENTS_BACKGROUND_H

#include "Screen/Components/IDrawable.h"

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

namespace Screen::Components
{
constexpr auto BACKGROUND_FILENAME = "share/textures/background/regular_pine.png";

class Background : virtual public IDrawable
{
public:
  Background();

  void draw(sf::RenderWindow& window) override;

protected:
  void loadTexturesFiles() override;

  void setTextures() override;

private:
  sf::Texture      m_texture;
  sf::Sprite       m_sprite;
  std::string_view m_file { BACKGROUND_FILENAME };
};

}  // namespace Game::Components

#endif /* COMPONENTS_BACKGROUND_H */
