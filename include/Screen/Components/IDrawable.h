/**
 * @brief Declares the interface for drawable objects.
 *
 * @author  spjuanjoc
 * @date    2024-04-14
 */

#ifndef GAME_COMPONENTS_DRAWABLE_H
#define GAME_COMPONENTS_DRAWABLE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Screen::Components
{


class IDrawable
{
public:
  virtual ~IDrawable() = default;

  virtual void draw(sf::RenderWindow& window) = 0;

protected:
  virtual void loadTexturesFiles() = 0;

  virtual void setTextures() = 0;
};

}  // namespace Game::Components

#endif /* GAME_COMPONENTS_DRAWABLE_H */
