/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-12

 * @see (https://github.com/AlexZihaoXu/CppFlappyBird.git)
*/

#include "Components/Background.h"
#include "Components/Bird.h"
#include "Program/Arguments.h"
#include "Program/EventsHandler.h"
#include "Program/Logger.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

constexpr auto WINDOW_TITLE = "Flappy Bird C++";

int main(int argc, const char* argv[])
{
  Logger::Info(">>");
  Logger::SpdLogger::get().setLevel(spdlog::level::level_enum::debug);
  auto args = Program::parseArguments(argc, argv);
  Logger::Info(args.width);

  sf::RenderWindow window(sf::VideoMode(args.width, args.height), WINDOW_TITLE);
  window.setFramerateLimit(args.frame_rate);
//  window.setPosition({args.startX, args.startY});
  sf::Clock deltaClock;
  Program::EventsHandler game{};

  ImGui::SFML::Init(window);
  ImGui::GetStyle().ScaleAllSizes(args.scale);
  ImGui::GetIO().FontGlobalScale = args.scale;

  const auto& window_size = window.getSize();
  Components::Background background;
  Components::Bird bird;
  bird.setEventHandler(&game);
  bird.setWindow(&window);
  background.setWindowSize(window_size);
  background.setXSpeed(args.speed);
  long long int us = 0;

  while (window.isOpen())
  {
    game.poll(window);
    us = deltaClock.getElapsedTime().asMicroseconds();
    ImGui::SFML::Update(window, deltaClock.restart());

    window.clear();
    background.draw(window);
    background.moveGround();
    bird.draw(window);

    if(game.isRunning())
    {
      background.move();
      bird.move(us);
    }
    else
    {
      bird.stand(us);
    }

    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
  Logger::Info("<<");

  return 0;
}
