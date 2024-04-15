/**
 * @brief Defines the background class.
 *
 * @author  spjuanjoc
 * @date    2024-04-14
 */

#include "Game/Components/Background.h"
#include "Core/Logging/Logger.h"


namespace Game::Components
{

Background::Background()
{
  Logger::Info(">>Background");
  loadTexturesFiles();
  setTextures();
  Logger::Info("<<Background");
}

void Background::loadTexturesFiles()
{
  m_texture.loadFromFile(m_file.data());
}

void Background::setTextures()
{
  m_sprite.setTexture(m_texture);
}

void Background::draw(sf::RenderWindow& window)
{
  window.draw(m_sprite);
}

}  // namespace Components
