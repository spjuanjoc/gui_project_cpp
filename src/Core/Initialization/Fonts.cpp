/**
 * @brief Defines the loading of fonts.
 *
 * @author  spjuanjoc
 * @date    2024-04-14
 */

#include "Core/Initialization/Fonts.h"

#include "Core/Constants/Constants.h"
#include "Core/Logging/Logger.h"

#include <filesystem>

#include <imgui.h>

namespace Core::Initialization
{

void
loadFonts()
{
  try
  {
    ImGuiIO& gui_io = ImGui::GetIO();
    gui_io.Fonts->Clear();

    if (std::filesystem::exists(FONT_FILENAME))
    {
      gui_io.Fonts->AddFontFromFileTTF(FONT_FILENAME, FONT_SIZE);
    }
    else
    {
      Logger::Error("The fonts file {0} does not exist. Using the default font.", FONT_FILENAME);
    }
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

}  // namespace Core::Initialization
