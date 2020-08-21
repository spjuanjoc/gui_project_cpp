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
        isKeyPressed = true;
        key          = event.key.code;
        break;
      }
      case sf::Event::Closed:
        window.close();
        break;
    }
  }  // End of poll event
}
