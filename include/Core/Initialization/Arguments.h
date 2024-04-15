/**
 * @brief Processes the program arguments.
 *
 * @author  spjuanjoc
 * @date    2021-11-26
 */

#ifndef CORE_ARGUMENTS_H
#define CORE_ARGUMENTS_H

#include "Core/Constants/Constants.h"
#include "Core/Logging/Logger.h"

#pragma GCC system_header
  #include <argparse/argparse.hpp>

namespace Core
{

/**
 * Declares the arguments that the application receives.
 */
struct Arguments
{
  std::uint32_t             width{};
  std::uint32_t             height{};
  std::uint32_t             frame_rate{};
  float                     scale{};
  spdlog::level::level_enum level{};
};

/**
 * Processes the Log Level argument.
 *
 * @param level The integer level.
 *
 * @return The enum level.
 */
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

/**
 * Processes the defined program arguments.
 *
 * @param argc The main argument count.
 * @param argv The main argument values.
 *
 * @return The struct with the processed arguments.
 */
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

  parser.parse_args(argc, argv);

  arguments.width      = parser.get<std::uint32_t>("--width");
  arguments.height     = parser.get<std::uint32_t>("--height");
  arguments.frame_rate = parser.get<std::uint32_t>("--frame_rate");
  arguments.scale      = parser.get<float>("--scale");
  arguments.level      = parseLevel(parser.get<std::uint32_t>("--level"));

  Logger::Debug("<<");

  return arguments;
}

}  // namespace Core

#endif /* CORE_ARGUMENTS_H */
