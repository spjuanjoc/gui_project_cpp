#include "Events/Events.h"
#include "Components/Bird.h"
#include "Components/Background.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <docopt/docopt.h>
#include <imgui-SFML.h>
#include <imgui.h>
//#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <chrono>
#include <string_view>
#include <list>
#include <thread>

using namespace std::chrono_literals;

constexpr std::string_view TITLE{"Flappy Bird C++"};

constexpr std::string_view USAGE =
  R"(Gui Project.

    Usage:
      gui_project_cpp [options]

    Options:
      -h --help     Show this screen.
      --version     Show version.
      --width=<width>     Set screen width  [default: 720].
      --height=<height>   Set screen height [default: 480].
      --scale=<scale>     Set scale factor [default: 2].
      --frameRate=<fr>    Set frame rate [default: 60].
      --startX=<X>        Set the start X position [default: 0].
      --startY=<Y>        Set the start Y position [default: 0].
)";

void drawBackground(sf::RenderWindow& window, const std::unique_ptr<sf::Texture>& texture)
{
  window.draw(sf::Sprite(*texture));
}


void drawBottom(sf::RenderWindow& window, const std::unique_ptr<sf::Texture>& texture, std::uint32_t y)
{
  sf::Sprite bottom(*texture);
  bottom.setPosition(0, y - 28);
  window.draw(bottom);
}


int main(int argc, const char* argv[])
{
  std::map<std::string, docopt::value> args{docopt::docopt(std::string(USAGE),
                                                           {std::next(argv), std::next(argv, argc)},
                                                           true,                        // show help if requested
                                                           "gui_project_cpp 0.0.2")};  // version string

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

  const auto width     = args["--width"].asLong();      // 720; //
  const auto height    = args["--height"].asLong();     // 480; //
  const auto frameRate = args["--frameRate"].asLong();  // 60; //
  const auto startX = static_cast<std::int32_t>(args["--startX"].asLong());  // 0; //
  const auto startY = static_cast<std::int32_t>(args["--startY"].asLong());  // 0; //
  const auto scale     = static_cast<float>(args["--scale"].asLong());      // 2; //
  constexpr std::array             options{"Option1", "Option2", "Option3"};
  std::array<bool, options.size()> states{};

  spdlog::set_pattern("[%d-%m-%Y %T.%e %z] [%l]: %v");
  spdlog::info(">>");

  sf::RenderWindow window(sf::VideoMode(width, height), std::string(TITLE));
  window.setFramerateLimit(frameRate);
//  window.setPosition({startX, startY});
  sf::Clock deltaClock;
  Events::Handler eventsHandler{};

  ImGui::SFML::Init(window);
  ImGui::GetStyle().ScaleAllSizes(scale);
  ImGui::GetIO().FontGlobalScale = scale;

  auto background = std::make_unique<sf::Texture>();
  auto bottom = std::make_unique<sf::Texture>();
  auto bird = std::make_unique<Components::Bird>();
  background->loadFromFile("share/textures/background/day.png");
  bottom->loadFromFile("share/textures/ground.png");
  const sf::Sprite& birdSprite = bird->draw();
  std::int64_t delta = 0.0;

  while (window.isOpen())
  {
    eventsHandler.Process(window);

    // Frame logic start
    delta = deltaClock.getElapsedTime().asMicroseconds() / 1000.0;
    ImGui::SFML::Update(window, deltaClock.restart());
    window.clear();

    drawBackground(window, background);
    drawBottom(window, bottom, height);
//    std::this_thread::sleep_for(50ms);

    bird->fall(delta);
//    bird->draw();
//    window.draw(birdSprite);

//    if(eventsHandler.isClick)
//    {
//      bird->flap();
//      spdlog::info("Clicked");
//    }

//    if (eventsHandler.key == 57)
//    {
//      bird->moveY();
//      bird->draw();
//      spdlog::info("flap");
//    }
    window.draw(birdSprite);

    // Box 1
//    ImGui::Begin("Options");
//    {
//      std::size_t index = 0;
//      for (const auto& item : options)
//      {
//        ImGui::Checkbox(fmt::format("{} : {}", index + 1, item).c_str(), &states.at(index));
//        ++index;
//      }
//    }
//    ImGui::End();
    // Box 2
//    ImGui::Begin("Key Pressed");
//    {
//      ImGui::TextUnformatted(fmt::format("Key pressed: {} {}", Events::keyName.at(eventsHandler.key), eventsHandler.key).c_str());
////      std::this_thread::sleep_for(50ms);
//    }
//    ImGui::End();

//    window.clear();
    ImGui::SFML::Render(window);
    window.display();
    // Frame logic end
  }

  ImGui::SFML::Shutdown();

  spdlog::info("<<");
  return 0;
}
