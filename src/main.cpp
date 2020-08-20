#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <docopt/docopt.h>
#include <imgui-SFML.h>
#include <imgui.h>
#include <spdlog/spdlog.h>
#include <chrono>
#include <iostream>
#include <list>
#include <thread>

using namespace std::chrono_literals;

constexpr auto frameRate{60};
constexpr auto modeWidth{720};
constexpr auto modeHeight{640};

constexpr const char* USAGE =
  R"(Game Project.

    Usage:
      game_project_cpp [options]

    Options:
      -h --help     Show this screen.
      --version     Show version.
      --showWin     Show the window [default: false].
      --width=<w>   Set screen width [default: 640].
)";

void foo()
{
  spdlog::set_pattern("[%d-%m-%Y %T.%e %z] [%l]: %v");
}

int main(int argc, const char* argv[])
{
  std::map<std::string, docopt::value> args{docopt::docopt(USAGE,
                                                           {std::next(argv), std::next(argv, argc)},
                                                           true,                        // show help if requested
                                                           "game_project_cpp 0.0.1")};  // version string

  for (auto const& arg : args)
  {
    if (arg.second.isBool())
    {
      spdlog::info("{} = {}", arg.first, arg.second.asBool());
    }
    else if (arg.second.isString())
    {
      spdlog::info("{} = {}", arg.first, arg.second.asString());
    }
  }
  const auto w = args["--width"].asLong();
  const auto showW = args["--showWin"].asBool();
  std::cout << "Width: " << w << ", show window: " << std::boolalpha << showW << '\n';

  spdlog::info("Hello spdlog");
  foo();
  spdlog::info(">>");

  sf::RenderWindow window(sf::VideoMode(modeWidth, modeHeight), "Window title");
  window.setFramerateLimit(frameRate);
  ImGui::SFML::Init(window);

  constexpr auto scaleFactor = 2.0;
  ImGui::GetStyle().ScaleAllSizes(scaleFactor);
  ImGui::GetIO().FontGlobalScale = scaleFactor;

  constexpr std::array             options{"Option1", "Option2", "Option3"};
  std::array<bool, options.size()> states{};
  bool isKeyPressed{};

  sf::Clock deltaClock;

  while (window.isOpen())
  {
    isKeyPressed = false;
    sf::Event event{};
    while (window.pollEvent(event))
    {
      ImGui::SFML::ProcessEvent(event);

      switch (event.type)
      {
        case sf::Event::KeyPressed:
        {
          isKeyPressed = true;
          break;
        }
        case sf::Event::Closed:
          window.close();
          break;
      }
    } // End of poll event

    // Frame logic start
    ImGui::SFML::Update(window, deltaClock.restart());

    // Box 1
    ImGui::Begin("Options");
    {
      std::size_t index = 0;
      for (const auto& item : options)
      {
        ImGui::Checkbox(fmt::format("{} : {}", index + 1, item).c_str(), &states.at(index));
        ++index;
      }
    }
    ImGui::End();

    // Box 2
    ImGui::Begin("Key Pressed");
    {
      ImGui::TextUnformatted(fmt::format("Is key pressed {}", isKeyPressed).c_str());
      std::this_thread::sleep_for(50ms);
    }
    ImGui::End();

    window.clear();
    ImGui::SFML::Render(window);
    window.display();
    // Frame logic end
  }

  ImGui::SFML::Shutdown();

  spdlog::info("<<");
  return 0;
}
