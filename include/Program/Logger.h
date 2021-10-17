/**
* @brief
*
* @author  juan.castellanos
* @date    2021-03-25
*/

#ifndef PROGRAM_LOGGER_H
#define PROGRAM_LOGGER_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"  // support for rotating file logging
#include "spdlog/sinks/stdout_color_sinks.h"  // or "../stdout_sinks.h" if no colors needed


namespace Logger
{
constexpr auto LOGGER_NAME     = "multi_sink";
constexpr auto LOGGER_FILENAME = "logs/file_logger.log";
constexpr auto MAX_FILE_SIZE   = 1024 * 1024 * 5;  // 5 MB
constexpr auto MAX_FILES       = 5;
constexpr auto CONSOLE_LEVEL = spdlog::level::level_enum::info;
constexpr auto FILE_LEVEL = spdlog::level::level_enum::trace;


class ISpdLogger
{
};

class SpdLogger : ISpdLogger
{
protected:
  SpdLogger();

public:
  static SpdLogger& get()
  {
    static SpdLogger logger;
    return logger;
  }

  virtual ~SpdLogger();

  SpdLogger(const SpdLogger&) = delete;
  SpdLogger(SpdLogger&&)      = delete;
  SpdLogger& operator=(const SpdLogger&) = delete;
  SpdLogger& operator=(SpdLogger&&) = delete;

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
void Error(const FormatString& fmt, Args&&... args)
{
  SpdLogger::get();
  spdlog::get(LOGGER_NAME)->error(fmt, std::forward<Args>(args)...);
}

template<typename FormatString, typename... Args>
void Critical(const FormatString& fmt, Args&&... args)
{
  SpdLogger::get();
  spdlog::get(LOGGER_NAME)->critical(fmt, std::forward<Args>(args)...);
}

}  // namespace Logger

#endif /* PROGRAM_LOGGER_H */
