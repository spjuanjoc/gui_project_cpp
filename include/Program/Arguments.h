/**
 * @brief
 *
 * @author  juan.castellanos
 * @date    2021-10-13
 */

#ifndef PROGRAM_ARGUMENTS_H
#define PROGRAM_ARGUMENTS_H

#include <docopt/docopt.h>
#include <spdlog/spdlog.h>

namespace Program
{
constexpr auto VERSION   = "gui_project_cpp 0.0.2";
constexpr auto SHOW_HELP = true;
constexpr auto USAGE     = R"(Gui Project.

    Usage:
      gui_project_cpp [options]

    Options:
      -h --help     Show this screen.
      --version     Show version.
      --width=<width>     Set screen width  [default: 480].
      --height=<height>   Set screen height [default: 720].
      --scale=<scale>     Set scale factor [default: 2].
      --frameRate=<fr>    Set frame rate [default: 60].
      --startX=<X>        Set the start X position [default: 0].
      --startY=<Y>        Set the start Y position [default: 0].
)";

struct Arguments
{
  std::uint32_t width{};
  std::uint32_t height{};
  std::uint32_t frameRate{};
  std::uint32_t startX{};
  std::uint32_t startY{};
  float         scale{};
};

static Arguments parseArguments(int argc, const char* argv[])
{
  std::map<std::string, docopt::value> args{docopt::docopt(USAGE, {std::next(argv), std::next(argv, argc)}, SHOW_HELP, VERSION)};

  for (auto const& arg : args)
  {
    if (arg.second.isBool())
    {
      spdlog::info("{} = {}", arg.first, arg.second.asBool());
    }
    else if (arg.second.isString())
    {
      spdlog::info("{} = {}", arg.first, arg.second.asString());
    }
  }

  Arguments arguments{};
  arguments.width     = static_cast<std::uint32_t>(args["--width"].asLong());
  arguments.height    = static_cast<std::uint32_t>(args["--height"].asLong());
  arguments.frameRate = static_cast<std::uint32_t>(args["--frameRate"].asLong());
  arguments.startX    = static_cast<std::uint32_t>(args["--startX"].asLong());
  arguments.startY    = static_cast<std::uint32_t>(args["--startY"].asLong());
  arguments.scale     = static_cast<float>(args["--scale"].asLong());

  return arguments;
}

}  // namespace Program

#endif /* PROGRAM_ARGUMENTS_H */
