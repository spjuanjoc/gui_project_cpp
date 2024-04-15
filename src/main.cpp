/**
 * @brief Defines the entry point which starts rendering the window, and polling the
 *        multimedia events.
 *
 * @author  spjuanjoc
 * @date    2021-10-12
*/

#include "Core/Constants/Constants.h"
#include "Core/Events/EventsHandler.h"
#include "Core/Initialization/Arguments.h"
#include "Core/Initialization/Fonts.h"
#include "Core/Logging/Logger.h"
#include "Game/Components/Background.h"
#include "Game/Components/StartWindow.h"

#include <imgui.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <imgui-SFML.h>

void
showKeysBox(Core::EventsHandler& program)
{
  ImGui::Begin("Key Pressed");
  {
    ImGui::TextUnformatted(fmt::format("Key pressed: {}", program.pressedKeyName()).c_str());
  }
  ImGui::End();
}

void
onMouseEvents(Core::EventsHandler& program, sf::Clock& deltaClock, long long int& elapsed)
{
  ImGui::Begin("Click Pressed");
  {
    if (program.isClickPressed())
    {
      auto milliseconds = deltaClock.getElapsedTime().asMilliseconds();
      auto microseconds = deltaClock.getElapsedTime().asMicroseconds();
      elapsed += microseconds;
      Logger::Info("{:<3} ms, {:<6} us, elapsed {} us.", milliseconds, microseconds, elapsed);
      ImGui::TextUnformatted(fmt::format("Click pressed for {} us.", elapsed).c_str());
    }
    else
    {
      ImGui::TextUnformatted(fmt::format("Click pressed for {} us.", elapsed).c_str());
    }
  }
  ImGui::End();
}

void
runMainLoop(sf::RenderWindow& main_window)
{
  sf::Clock                     deltaClock;
  Core::EventsHandler           program {};
  Game::Components::Background  background;
  Game::Components::StartWindow start_window;
  long long int                 elapsed = 0;

  while (main_window.isOpen())
  {
    program.poll(main_window);
    ImGui::SFML::Update(main_window, deltaClock.restart());

    main_window.clear();

    background.draw(main_window);

    if (program.isRunning())
    {
      showKeysBox(program);
      onMouseEvents(program, deltaClock, elapsed);
    }
    else
    {
      //      ImGui::ShowMetricsWindow();
      start_window.draw(main_window);
    }

    ImGui::SFML::Render(main_window);
    main_window.display();
  }
}

int
main(int argc, const char* argv[])
{
  Logger::Info(">>main");
  auto args = Core::parseArguments(argc, argv);
  Logger::SpdLogger::get().setLevel(args.level);

  sf::RenderWindow main_window(sf::VideoMode(args.width, args.height), WINDOW_TITLE);

  main_window.setFramerateLimit(args.frame_rate);
  ImGui::SFML::Init(main_window);
  ImGui::GetStyle().ScaleAllSizes(args.scale);
  Core::Initialization::loadFonts();
  ImGui::SFML::UpdateFontTexture();
  ImGui::GetStyle().ScaleAllSizes(args.scale);
  ImGui::GetIO().FontGlobalScale = args.scale;

  runMainLoop(main_window);

  ImGui::SFML::Shutdown();
  Logger::Info("<<main");

  return 0;
}
