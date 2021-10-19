/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-12
 */

#ifndef COMPONENTS_BIRD_H
#define COMPONENTS_BIRD_H

#include <Program/Logger.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <spdlog/spdlog.h>
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
constexpr std::uint32_t GRAVITY     = 10;
constexpr std::uint32_t FLAP_HEIGHT = GRAVITY + 1;
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

  void setEventHandler(Program::EventsHandler* event);

  void setWindow(sf::RenderWindow* window);

private:
  float                        m_angle{};
  bool                         m_is_flapping{};
  float                        m_y_delta{};
  size_t                       m_current_frame{};
  std::uint32_t                m_delta{};
  float                        m_x_position{BIRD_START_X};
  float                        m_y_position{BIRD_START_Y};
  float                        m_window_width{};
  float                        m_window_height{};
  float                        m_difficulty{1};
  float                        m_mass{1};
  float                        m_flap_strength{2};
  sf::Sprite                   m_sprite;
  Program::EventsHandler*      m_event{nullptr};
  sf::RenderWindow*            m_window{nullptr};
  std::vector<std::unique_ptr<sf::Texture>> m_textures;
};

}  // namespace Components

#endif /* COMPONENTS_BIRD_H */
