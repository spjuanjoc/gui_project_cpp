//
// Created by juan.castellanos on 20/08/20.
//

#include "Events/Events.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <spdlog/spdlog.h>

void Events::Handler::Process(sf::RenderWindow& window)
{
  sf::Event event{};
  while (window.pollEvent(event))
  {
    ImGui::SFML::ProcessEvent(event);

    switch (event.type)
    {
      case sf::Event::KeyPressed:
      {
        key     = event.key.code;
        isAlt   = event.key.alt;
        isControl = event.key.control;
        isShift   = event.key.shift;
        isSystem  = event.key.system;

        if (isShift && Events::keyName.at(key) == "W")
        {
          spdlog::info("Shift + W");
          window.close();
        }

        break;
      }
      case sf::Event::KeyReleased:
      {
        key = sf::Keyboard::Key::Unknown;
        break;
      }
      case sf::Event::MouseButtonPressed:
      {
        isClick = true;
        spdlog::info("Clicked");
        break;
      }
      case sf::Event::Closed:
      {
        window.close();
        break;
      }
    }
  }  // End of poll event
}
