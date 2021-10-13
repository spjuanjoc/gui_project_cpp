/**
* @brief
*
* @author  juan.castellanos
* @date    2020-08-20
*/

#include "Program/EventsHandler.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <spdlog/spdlog.h>

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
        m_key     = event.key.code;
        isAlt   = event.key.alt;
        isControl = event.key.control;
        isShift   = event.key.shift;
        isSystem  = event.key.system;

        if (isShift && Program::KEY_NAMES.at(m_key) == "W")
        {
          spdlog::info("Shift + W");
          window.close();
        }

        break;
      }
      case sf::Event::KeyReleased:
      {
        m_key = sf::Keyboard::Key::Unknown;
        break;
      }
      case sf::Event::MouseButtonPressed:
      {
        isClick = true;

        if (m_isRunning)
        {
          m_isRunning = false;
          spdlog::info("Stop");
        }
        else
        {
          m_isRunning = true;
          spdlog::info("Start");
        }
        break;
      }
      case sf::Event::Closed:
      {
        spdlog::info("Bye");
        window.close();
        break;
      }
    }
  }  // End of poll event
}
