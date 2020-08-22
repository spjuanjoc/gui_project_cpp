//
// Created by juan.castellanos on 20/08/20.
//

#include "Events/Events.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>

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
        alt     = event.key.alt;
        control = event.key.control;
        shift   = event.key.shift;
        system  = event.key.system;
        break;
      }
      case sf::Event::KeyReleased:
      {
        key = sf::Keyboard::Key::Unknown;
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
