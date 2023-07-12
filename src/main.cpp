/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2021-10-12


*/

//#include "Components/Background.h"
//#include "Components/Bird.h"
#include "Program/Arguments.h"
#include "Program/EventsHandler.h"
#include "Program/Logger.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

constexpr auto WINDOW_TITLE = "ImGui+SFML in C++";

int main(int argc, const char* argv[])
{
  Logger::Info(">>main");
  auto args = Program::parseArguments(argc, argv);
  Logger::SpdLogger::get().setLevel(args.level);

  sf::RenderWindow window(sf::VideoMode(args.width, args.height), WINDOW_TITLE);
  window.setFramerateLimit(args.frame_rate);
//  window.setPosition({args.startX, args.startY});
  sf::Clock deltaClock;
  Program::EventsHandler program{};

  ImGui::SFML::Init(window);
  ImGui::GetStyle().ScaleAllSizes(args.scale);
  ImGui::GetIO().FontGlobalScale = args.scale;

  const auto& window_size = window.getSize();
  long long int elapsed_time = 0;


  constexpr std::array             options{"Option1", "Option2", "Option3"};
  std::array<bool, options.size()> states{};


  while (window.isOpen())
  {
    program.poll(window);
    elapsed_time = deltaClock.getElapsedTime().asMicroseconds();
    ImGui::SFML::Update(window, deltaClock.restart());

    window.clear();

//    if(program.isRunning())
//    {

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


    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();
  Logger::Info("<<main");

  return 0;
}
