/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-12
 */

#ifndef COMPONENTS_BIRD_H
#define COMPONENTS_BIRD_H

#include "Program/Logger.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

namespace sf
{
class RenderWindow;
}

namespace Program
{
class EventsHandler;
}

namespace Components
{
class Background;

constexpr std::uint32_t BIRD_START_X = 50;
constexpr std::uint32_t BIRD_START_Y = 50;

class Bird
{
public:
  Bird();

  sf::Sprite& getSprite();

  void draw(sf::RenderWindow& window);

  void stand(long long int elapsed_us);

  void move(long long int elapsed_us);

  void fall();

  void flap();

  void wing();

  void die();

  void setEventHandler(Program::EventsHandler* event);

  void setBackground(Components::Background* background);

  void setWindow(sf::RenderWindow* window);

private:
  using textures_collection_t = std::vector<std::unique_ptr<sf::Texture>>;

  bool                    m_is_dead{};
  int                     m_fall_start_height{};
  size_t                  m_current_frame{};
  long long int           m_delta{};
  float                   m_window_width{};
  float                   m_window_height{};
  sf::Vector2f            m_acceleration{};
  sf::Vector2f            m_velocity{};
  sf::Sprite              m_sprite;
  Program::EventsHandler* m_event{nullptr};
  Components::Background* m_background{nullptr};
  sf::RenderWindow*       m_window{nullptr};
  textures_collection_t   m_textures;
};

}  // namespace Components

#endif /* COMPONENTS_BIRD_H */
