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
  Logger::Info(">>main");
  auto args = Program::parseArguments(argc, argv);
  Logger::SpdLogger::get().setLevel(args.level);

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
  bird.setBackground(&background);
  bird.setWindow(&window);
  background.setWindowSize(window_size);
  background.setXSpeed(args.speed);
  long long int us = 0;
//  const auto& sprite = bird.getSprite();

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
      const auto& bb = bird.getSprite().getGlobalBounds();
      const auto& lpb1 = background.getPipes1().lock()->getLowSprite().getGlobalBounds();
      const auto& usb1 = background.getPipes1().lock()->getUpSprite().getGlobalBounds();
      const auto& lpb2 = background.getPipes2().lock()->getLowSprite().getGlobalBounds();
      const auto& usb2 = background.getPipes2().lock()->getUpSprite().getGlobalBounds();
//      Logger::Info("bounds top, left, height, width: bird ({},{},{},{}):", bb.top, bb.left, bb.height, bb.width);
//      Logger::Info("bounds top, left, height, width: pipes ({},{},{},{})",
//                   lpb1.top,
//                   lpb1.left,
//                   lpb1.height,
//                   lpb1.width);

      if (bb.intersects(lpb1) || bb.intersects(usb1) || bb.intersects(lpb2) || bb.intersects(usb2))
      {
        Logger::Info("intersects");
        bird.die();
        background.stop();
      }
    }
    else
    {
      bird.stand(us);
    }

    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
  Logger::Info("<<main");

  return 0;
}
