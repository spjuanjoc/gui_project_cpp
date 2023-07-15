/**
* @brief Defines the global logger objects.
*
* @author  spjuanjoc
* @date    2021-03-25
*/

#ifndef CORE_LOGGER_H
#define CORE_LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Logger
{
constexpr auto LOGGER_NAME     = "multi_sink";
constexpr auto LOGGER_FILENAME = "logs/file_logger.log";
constexpr auto MAX_FILE_SIZE   = 1024 * 1024 * 2;  // 2 MB supported by Code Insight
constexpr auto MAX_FILES       = 5;
constexpr auto CONSOLE_LEVEL   = spdlog::level::level_enum::info;
constexpr auto FILE_LEVEL      = spdlog::level::level_enum::trace;

/**
 * Logger class that wraps the spdlog objects for a multisink singleton logger.
 */
class SpdLogger
{
protected:
  SpdLogger();

public:
  /**
   *
   * @return The logger reference.
   */
  static SpdLogger& get()
  {
    static SpdLogger logger;
    return logger;
  }

  virtual ~SpdLogger();

  /**
   * The deleted special members. Non-copy non-movable.
   */
  SpdLogger(const SpdLogger&) = delete;
  SpdLogger(SpdLogger&&)      = delete;
  SpdLogger& operator=(const SpdLogger&) = delete;
  SpdLogger& operator=(SpdLogger&&) = delete;

  /**
   * Defines the log level.
   *
   * @param level The enum value of level.
   */
  void setLevel(spdlog::level::level_enum level);

private:
  using console_sink_t = std::shared_ptr<spdlog::sinks::ansicolor_stdout_sink<spdlog::details::console_mutex>>;
  using file_sink_t = std::shared_ptr<spdlog::sinks::rotating_file_sink<std::mutex>>;
  using log_level_e = spdlog::level::level_enum;

  std::uint32_t  m_max_file_size{MAX_FILE_SIZE};
  std::uint32_t  m_max_files{MAX_FILES};
  std::string    m_filename{LOGGER_FILENAME};
  std::string    m_name{LOGGER_NAME};
  log_level_e    m_console_level{CONSOLE_LEVEL};
  log_level_e    m_file_level{FILE_LEVEL};
  console_sink_t m_console_sink;
  file_sink_t    m_file_sink;
};

template<typename FormatString, typename... Args>
void Trace(const FormatString& fmt, Args&&... args)
{
  SpdLogger::get();
  spdlog::get(LOGGER_NAME)->trace(fmt, std::forward<Args>(args)...);
}

template<typename FormatString, typename... Args>
void Debug(const FormatString& fmt, Args&&... args)
{
  SpdLogger::get();
  spdlog::get(LOGGER_NAME)->debug(fmt, std::forward<Args>(args)...);
}

template<typename FormatString, typename... Args>
void Info(const FormatString& fmt, Args&&... args)
{
  SpdLogger::get();
  spdlog::get(LOGGER_NAME)->info(fmt, std::forward<Args>(args)...);
}

template<typename FormatString, typename... Args>
void Warn(const FormatString& fmt, Args&&... args)
{
  SpdLogger::get();
  spdlog::get(LOGGER_NAME)->warn(fmt, std::forward<Args>(args)...);
}

template<typename FormatString, typename... Args>
void Error(FormatString&& format_string, Args&&... args)
{
  SpdLogger::get();
  spdlog::get(LOGGER_NAME)->error(std::forward<FormatString>(format_string), std::forward<Args>(args)...);
}

template<typename FormatString, typename... Args>
void Critical(const FormatString& fmt, Args&&... args)
{
  SpdLogger::get();
  spdlog::get(LOGGER_NAME)->critical(fmt, std::forward<Args>(args)...);
}

}  // namespace Logger

#endif /* CORE_LOGGER_H */
