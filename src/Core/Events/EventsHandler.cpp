/**
* @brief Handles the multimedia events for the keyboard and mouse.
*
* @author  spjuanjoc
* @date    2021-11-26
*/

#include "Core/Events/EventsHandler.h"
#include "Core/Logging/Logger.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>

namespace Core
{

void EventsHandler::poll(sf::RenderWindow& window)
{
  sf::Event event{};
  while (window.pollEvent(event))
  {
    ImGui::SFML::ProcessEvent(event);

    switch (event.type)
    {
      case sf::Event::KeyPressed:
      {
        m_key     = static_cast<KEY_NAMES>(event.key.code);
        isAlt     = event.key.alt;
        isControl = event.key.control;
        isShift   = event.key.shift;
        isSystem  = event.key.system;

        pauseResume();
        close(window);

        break;
      }
      case sf::Event::KeyReleased:
      {
        m_key = KEY_NAMES::UNKNOWN;
        break;
      }
      case sf::Event::MouseButtonPressed:
      {
        isClicked = true;
        break;
      }
      case sf::Event::MouseButtonReleased:
      {
        isClicked = false;
        break;
      }
      case sf::Event::Closed:
      {
        Logger::Info("Bye");
        window.close();
        break;
      }
      default:
        break;
    }
  }  // End of poll event
}

void EventsHandler::pauseResume()
{
  if (KEY_NAMES::Enter == pressedKey())
  {
    if (m_isRunning)
    {
      m_isRunning = false;
      Logger::Info("Pause");
    }
    else
    {
      m_isRunning = true;
      Logger::Info("Start");
    }
  }
}

void EventsHandler::close(sf::RenderWindow& window)
{
  if ((isShift || isControl) && (m_key == KEY_NAMES::W || m_key == KEY_NAMES::Q))
  {
    Logger::Info("Close");
    window.close();
  }
}

bool
EventsHandler::isClickPressed() const
{
  return isClicked;
}

}  // namespace Core
