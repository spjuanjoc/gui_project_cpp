#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <list>


constexpr auto frameRate{60};
constexpr auto modeWidth{640};
constexpr auto modeHeight{480};

int main([[maybe_unused]] int argc, [[maybe_unused]] const char* argv[])
{
  spdlog::info(">>");
  sf::RenderWindow window(sf::VideoMode(modeWidth, modeHeight), "Window title");
  window.setFramerateLimit(frameRate);
  ImGui::SFML::Init(window);

  //  sf::CircleShape shape(100.f);
  //  shape.setFillColor(sf::Color::Yellow);

  constexpr auto scaleFactor = 2.0;
  ImGui::GetStyle().ScaleAllSizes(scaleFactor);
  ImGui::GetIO().FontGlobalScale = scaleFactor;

  sf::Clock           deltaClock;
  std::array<bool, 3> states{};
  std::list           list{"Option1", "Option2", "Option3"};

  while (window.isOpen())
  {
    sf::Event event{};
    while (window.pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    // Frame logic start
    ImGui::SFML::Update(window, deltaClock.restart());

    ImGui::Begin("Box title");

    int index = 0;
    for (const auto& item : list)
    {
      ImGui::Checkbox(fmt::format("{} : {}", index + 1, item).c_str(), std::next(std::begin(states), index));
      ++index;
    }
    ImGui::End();

    ImGui::Begin("Another box");
    ImGui::Button("Button 1 inside box");
    ImGui::End();

    window.clear();
    //    window.draw(shape);
    ImGui::SFML::Render(window);
    window.display();
    // Frame logic end
  }

  ImGui::SFML::Shutdown();

  spdlog::info("<<");
  return 0;
}
