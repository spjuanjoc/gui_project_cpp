#include "Events/Events.h"
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

constexpr std::string_view TITLE{"some title"};

constexpr std::string_view USAGE =
  R"(Game Project.

    Usage:
      game_project_cpp [options]

    Options:
      -h --help     Show this screen.
      --version     Show version.
      --width=<width>     Set screen width  [default: 720].
      --height=<height>   Set screen height [default: 480].
      --scale=<scale>     Set scale factor [default: 2].
      --frameRate=<fr>    Set frame rate [default: 60].
)";

int main(int argc, const char* argv[])
{
  std::map<std::string, docopt::value> args{docopt::docopt(std::string(USAGE),
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

  const auto width  = args["--width"].asLong();
  const auto height = args["--height"].asLong();
  const auto frameRate = args["--frameRate"].asLong();
  const auto scale = args["--scale"].asLong();

  spdlog::set_pattern("[%d-%m-%Y %T.%e %z] [%l]: %v");
  spdlog::info(">>");

  sf::RenderWindow window(sf::VideoMode(width, height), std::string(TITLE));
  window.setFramerateLimit(frameRate);

  ImGui::SFML::Init(window);
  ImGui::GetStyle().ScaleAllSizes(scale);
  ImGui::GetIO().FontGlobalScale = scale;

  constexpr std::array             options{"Option1", "Option2", "Option3"};
  std::array<bool, options.size()> states{};

  sf::Clock deltaClock;
  Events::Handler eventsHandler;

  while (window.isOpen())
  {
    eventsHandler.isKeyPressed = false;
    eventsHandler.Process(window);

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
      ImGui::TextUnformatted(fmt::format("Key pressed: {}", Events::keyName.at(eventsHandler.key)).c_str());
//      std::this_thread::sleep_for(50ms);
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
