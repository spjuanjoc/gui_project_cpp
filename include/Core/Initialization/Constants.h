/**
 * @brief Defines the transversal constants.
 *
 * @author  spjuanjoc
 * @date    2021-11-26
 */

#ifndef CORE_CONSTANTS_H
#define CORE_CONSTANTS_H

#include <cstdint>

namespace Core
{
constexpr auto          NAME           = "gui_project_cpp";
constexpr auto          VERSION        = "0.0.4";
constexpr std::uint32_t MAX_FRAME_RATE = 30;
constexpr std::uint32_t WINDOW_HEIGHT  = 480;
constexpr std::uint32_t WINDOW_WIDTH   = 640;
constexpr std::uint32_t DEFAULT_LEVEL  = 4;
constexpr float         WINDOW_SCALE   = 1.0F;
}  // namespace Core

constexpr auto  WINDOW_TITLE  = "Game Template";
constexpr auto  FONT_FILENAME = "share/fonts/calibri/calibri-regular.ttf";
constexpr float FONT_SIZE     = 22.0F;

#endif /* CORE_CONSTANTS_H */
