#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <memory>
#include <mutex>

#ifdef _WIN32
  #include <windows.h>
#endif

class Logger {
public:
  enum class Level { LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR };

  // C++11 Singleton
  static Logger& getInstance() {
    static Logger instance;
    return instance;
  }

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  void log(Level level, const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);

    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time);

    std::cout << "[" << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << "] "
              << "[" << name << "] "
              << "[" << levelToString(level) << "] ";

    setConsoleColor(level);
    std::cout << message;

    resetConsoleColor();
    std::cout << std::endl;
  }

  void debug(const std::string& message) { log(Level::LOG_DEBUG, message); }
  void info(const std::string& message) { log(Level::LOG_INFO, message); }
  void warning(const std::string& message) { log(Level::LOG_WARNING, message); }
  void error(const std::string& message) { log(Level::LOG_ERROR, message); }

private:
  std::string name =
      "VCMLib";  // string name may be affected by SolutionRenamer.py
  std::mutex logMutex;

  Logger() = default;
  ~Logger() = default;

  std::string levelToString(Level level) const {
    switch (level) {
      case Level::LOG_DEBUG: return "DEBUG";
      case Level::LOG_INFO: return "INFO";
      case Level::LOG_WARNING: return "WARNING";
      case Level::LOG_ERROR: return "ERROR";
      default: return "UNKNOWN";
    }
  }

  void setConsoleColor(Level level) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (level) {
      case Level::LOG_DEBUG:
        SetConsoleTextAttribute(hConsole,
            FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
      case Level::LOG_INFO:
        SetConsoleTextAttribute(
            hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
      case Level::LOG_WARNING:
        SetConsoleTextAttribute(
            hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
      case Level::LOG_ERROR:
        SetConsoleTextAttribute(
            hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
      default:
        SetConsoleTextAttribute(
            hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    }
#else
    switch (level) {
      case Level::LOG_DEBUG:
        std::cout << "\033[34m";  // Blue
        break;
      case Level::LOG_INFO:
        std::cout << "\033[32m";  // Green
        break;
      case Level::LOG_WARNING:
        std::cout << "\033[33m";  // Yellow
        break;
      case Level::LOG_ERROR:
        std::cout << "\033[31m";  // Red
        break;
      default:
        std::cout << "\033[0m";  // Reset
        break;
    }
#endif
  }

  void resetConsoleColor() {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    std::cout << "\033[0m";  // Reset
#endif
  }
};  // class Logger

// Define LOG macro for easy access
#define LOG Logger::getInstance()

// implementation examples
// Logger::getInstance().log(Logger::Level::INFO, something);
// Logger::getInstance().info(something);
// LOG.info(something);

#endif  // LOGGER_H
