/**
 * @brief
 *
 * @author  spjuanjoc
 * @date    2021-10-13
 */

#ifndef PROGRAM_ARGUMENTS_H
#define PROGRAM_ARGUMENTS_H

#pragma GCC system_header
  #include <argparse/argparse.hpp>
#include "Logger.h"

namespace Program
{
constexpr auto          NAME           = "gui_project_cpp";
constexpr auto          VERSION        = "0.0.4";
constexpr auto          INITIAL_SPEED  = 3.0F;
constexpr std::uint32_t MAX_FRAME_RATE = 30;
constexpr std::uint32_t WINDOW_HEIGHT  = 720;
constexpr auto          WINDOW_SCALE   = 1.0F;
constexpr std::uint32_t WINDOW_WIDTH   = 480;
constexpr std::uint32_t DEFAULT_LEVEL  = 4;

struct Arguments
{
  std::uint32_t             width{};
  std::uint32_t             height{};
  std::uint32_t             frame_rate{};
  float                     speed{};
  float                     scale{};
  spdlog::level::level_enum level{};
  //  std::uint32_t startX{};
  //  std::uint32_t startY{};
};

static spdlog::level::level_enum parseLevel(std::uint32_t level)
{
  switch (level)
  {
    case 0: return spdlog::level::level_enum::off;
    case 1: return spdlog::level::level_enum::critical;
    case 2: return spdlog::level::level_enum::err;
    case 3: return spdlog::level::level_enum::warn;
    case 4: return spdlog::level::level_enum::info;
    case 5: return spdlog::level::level_enum::debug;
    case 6: return spdlog::level::level_enum::trace;
    default:return spdlog::level::level_enum::info;
  }
}

static Arguments parseArguments(int argc, const char* argv[])
{
  Logger::Debug(">>");
  Arguments                arguments{};
  argparse::ArgumentParser parser(NAME, VERSION);

  parser.add_argument("-l", "--level").help("The log level").default_value(DEFAULT_LEVEL).scan<'i', std::uint32_t>();
  parser.add_argument("-w", "--width").help("The screen width").default_value(WINDOW_WIDTH).scan<'i', std::uint32_t>();
  parser.add_argument("-h", "--height").help("The screen height").default_value(WINDOW_HEIGHT).scan<'i', std::uint32_t>();
  parser.add_argument("-r", "--frame_rate").help("The frame-per-seconds rate limit").default_value(MAX_FRAME_RATE).scan<'i', std::uint32_t>();
  parser.add_argument("-s", "--scale").help("The window scale").default_value(WINDOW_SCALE).scan<'f', float>();
  parser.add_argument("-i", "--initial_speed").help("The move speed").default_value(INITIAL_SPEED).scan<'f', float>();

  parser.parse_args(argc, argv);

  arguments.width      = parser.get<std::uint32_t>("--width");
  arguments.height     = parser.get<std::uint32_t>("--height");
  arguments.frame_rate = parser.get<std::uint32_t>("--frame_rate");
  arguments.scale      = parser.get<float>("--scale");
  arguments.speed      = parser.get<float>("--initial_speed");
  arguments.level      = parseLevel(parser.get<std::uint32_t>("--level"));

  Logger::Debug("<<");

  return arguments;
}

}  // namespace Program

#endif /* PROGRAM_ARGUMENTS_H */
