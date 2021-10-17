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


namespace Program
{
class EventsHandler;
}

namespace Components
{
constexpr std::uint32_t GRAVITY     = 10;
constexpr std::uint32_t FLAP_HEIGHT = 18;
constexpr std::uint32_t BIRD_START_X = 50;

class Bird
{
public:
  Bird();

  sf::Sprite& draw();

  void move(std::uint32_t window_height);

  void fall(const std::uint32_t& height);

  void flap();

  void setEventHandler(Program::EventsHandler* event);

private:
  float                        m_x_position{BIRD_START_X};
  float                        m_y_position{};
  float                        m_difficulty{1};
  float                        m_mass{1};
  float                        m_flap_strength{1};
  std::unique_ptr<sf::Texture> m_texture;
  sf::Sprite                   m_sprite;
  std::string                  m_wing_up_img{"share/textures/bird/1-1.png"};
  std::string                  m_wing_mid_img{"share/textures/bird/1-2.png"};
  std::string                  m_wing_down_img{"share/textures/bird/1-3.png"};
  Program::EventsHandler*      m_event{nullptr};
};

}  // namespace Components

#endif /* COMPONENTS_BIRD_H */
