/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-12

 * @see (https://github.com/AlexZihaoXu/CppFlappyBird.git)
*/

#include "Components/Pipes.h"
#include "Components/Background.h"
#include "Components/Bird.h"
#include "Program/Arguments.h"
#include "Program/EventsHandler.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <spdlog/spdlog.h>
//#include <chrono>
//#include <string_view>
//#include <thread>

//using namespace std::chrono_literals;

constexpr auto WINDOW_TITLE = "Flappy Bird C++";

int main(int argc, const char* argv[])
{
  auto args = Program::parseArguments(argc, argv);

  spdlog::set_pattern("[%d-%m-%Y %T.%e %z] [%l]: %v");
  spdlog::info(">>");

  sf::RenderWindow window(sf::VideoMode(args.width, args.height), WINDOW_TITLE);
  window.setFramerateLimit(args.frameRate);
//  window.setPosition({args.startX, args.startY});
  sf::Clock deltaClock;
  Program::EventsHandler game{};

  ImGui::SFML::Init(window);
  ImGui::GetStyle().ScaleAllSizes(args.scale);
  ImGui::GetIO().FontGlobalScale = args.scale;

  const auto& window_size = window.getSize();
  Components::Background background;
  Components::Bird bird;
  const sf::Sprite& birdSprite = bird.draw();
  background.setWindowSize(window_size);
  background.setXSpeed(5);

  while (window.isOpen())
  {
    game.Poll(window);
    ImGui::SFML::Update(window, deltaClock.restart());
    window.clear();
    background.draw(window);

    if(game.isRunning())
    {
      background.move();
      bird.fall(args.height);

      if (game.pressedKey() == Program::KEY_NAMES::Space)
      {
        spdlog::debug("flap");
        bird.flap();
      }
    }

    window.draw(birdSprite);

    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();

  spdlog::info("<<");
  return 0;
}
