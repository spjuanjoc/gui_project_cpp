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
#include "Screen/Components/Background.h"
#include "Screen/Components/StartWindow.h"

#include <imgui-SFML.h>

void
showKeysBox(const Core::EventsHandler& program)
{
  ImGui::Begin("Key Pressed");
  {
    ImGui::TextUnformatted(fmt::format("Key pressed: {}", program.pressedKeyName()).c_str());
  }
  ImGui::End();
}

void
onMouseEvents(const Core::EventsHandler& program, const sf::Clock& deltaClock, long long int& elapsed)
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
  sf::Clock                       deltaClock;
  Core::EventsHandler             program {};
  Screen::Components::Background  background;
  Screen::Components::StartWindow start_window;
  long long int                   elapsed = 0;

  while (main_window.isOpen())
  {
    program.poll(main_window);
    ImGui::SFML::Update(main_window, deltaClock.restart());

    main_window.clear();
    //    ImGui::ShowDemoWindow();

    background.draw(main_window);

    if (program.isRunning())
    {
      showKeysBox(program);
      onMouseEvents(program, deltaClock, elapsed);
    }
    else
    {
      //          ImGui::ShowMetricsWindow();
      start_window.draw(main_window);
    }

    ImGui::SFML::Render(main_window);
    main_window.display();
  }
}

int
main(int argc, const char* argv[])
{
  auto args = Core::parseArguments(argc, argv);
  Logger::SpdLogger::get().setLevel(args.level);
  Logger::Info(">>main");

  sf::RenderWindow main_window(sf::VideoMode(args.width, args.height), WINDOW_TITLE);

  main_window.setFramerateLimit(args.frame_rate);
  [[maybe_unused]] bool isInit = ImGui::SFML::Init(main_window);
  ImGui::GetStyle().ScaleAllSizes(args.scale);
  Core::Initialization::loadFonts();
  [[maybe_unused]]bool isFont = ImGui::SFML::UpdateFontTexture();
  ImGui::GetStyle().ScaleAllSizes(args.scale);
  ImGui::GetIO().FontGlobalScale = args.scale;

  runMainLoop(main_window);

  ImGui::SFML::Shutdown();
  Logger::Info("<<main");

  return 0;
}
