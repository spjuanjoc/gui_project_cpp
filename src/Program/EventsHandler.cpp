/**
* @brief
*
* @author  juan.castellanos
* @date    2020-08-20
*/

#include "Program/EventsHandler.h"
#include "Program/Logger.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>

void Program::EventsHandler::Poll(sf::RenderWindow& window)
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

        if (isShift && m_key == KEY_NAMES::W)
        {
          Logger::Info("Shift + W");
          window.close();
        }

        break;
      }
      case sf::Event::KeyReleased:
      {
        m_key = KEY_NAMES::UNKNOWN;
        break;
      }
      case sf::Event::MouseButtonPressed:
      {
        isClick = true;

        if (m_isRunning)
        {
          m_isRunning = false;
          Logger::Info("Stop");
        }
        else
        {
          m_isRunning = true;
          Logger::Info("Start");
        }
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
