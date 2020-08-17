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

void foo()
{
  spdlog::set_pattern("[%d-%m-%Y %T.%e %z] th[%t] %s:%!:%# [%l] %v");
  spdlog::info(">>");
  spdlog::info("debug message");
  spdlog::info("<<");
  SPDLOG_INFO("Some info message with extra details");
}

int main([[maybe_unused]] int argc, [[maybe_unused]] const char* argv[])
{
  spdlog::info("Hello spdlog");
  foo();
  spdlog::info(">>");
  sf::RenderWindow window(sf::VideoMode(modeWidth, modeHeight), "Window title");
  window.setFramerateLimit(frameRate);
  ImGui::SFML::Init(window);

  //  sf::CircleShape shape(100.f);
  //  shape.setFillColor(sf::Color::Yellow);

  constexpr auto scaleFactor = 2.0;
  ImGui::GetStyle().ScaleAllSizes(scaleFactor);
  ImGui::GetIO().FontGlobalScale = scaleFactor;

  sf::Clock            deltaClock;
  constexpr std::array options{"Option1", "Option2", "Option3"};
  std::array<bool, options.size()> states{};

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

    std::size_t index = 0;
    for (const auto& item : options)
    {
      ImGui::Checkbox(fmt::format("{} : {}", index + 1, item).c_str(), &states.at(index));
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
