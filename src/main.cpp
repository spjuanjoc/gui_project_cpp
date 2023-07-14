/**
 * @brief Defines the entry point which starts rendering the window, and polling the
 *        multimedia events.
 *
 * @author  spjuanjoc
 * @date    2021-10-12
*/

#include "Core/Events/EventsHandler.h"
#include "Core/Initialization/Arguments.h"
#include "Core/Initialization/Constants.h"
#include "Core/Logging/Logger.h"

#include <imgui.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <imgui-SFML.h>

void
loadFonts()
{
  try
  {
    ImGuiIO& gui_io = ImGui::GetIO();
    gui_io.Fonts->Clear();
    //check if file exists
    gui_io.Fonts->AddFontFromFileTTF(FONT_FILENAME, FONT_SIZE);
  }
  catch (const std::exception& exception)
  {
    Logger::Error("The fonts could not be loaded. {0}", exception.what());
  }
  catch (...)
  {
    Logger::Error("The fonts could not be loaded.");
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
  sf::Clock deltaClock;

  ImGui::SFML::Init(main_window);
  ImGui::GetStyle().ScaleAllSizes(args.scale);
  loadFonts();
  ImGui::SFML::UpdateFontTexture();
  Core::EventsHandler program {};

  ImGui::GetStyle().ScaleAllSizes(args.scale);
  ImGui::GetIO().FontGlobalScale = args.scale;

  constexpr std::array             options { "Option1", "Option2", "Option3" };
  std::array<bool, options.size()> states {};

  while (main_window.isOpen())
  {
    program.poll(main_window);
    ImGui::SFML::Update(main_window, deltaClock.restart());

    main_window.clear();

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
      ImGui::TextUnformatted(fmt::format("Key pressed: {}", program.pressedKeyName()).c_str());
      //      std::this_thread::sleep_for(50ms);
    }
    ImGui::End();
    //    }


    ImGui::SFML::Render(main_window);
    main_window.display();
  }

  ImGui::SFML::Shutdown();
  Logger::Info("<<main");

  return 0;
}
