#pragma once

#include <iostream>
#include <sstream>

#include "LogTypes.h"

class Logger
{
public:
  static void Rant(RantLevel level = RantLevel::DEBUG,
                   RantFlags flags = RantFlags::ShowRantLevel,
                   const std::string &rant = "No Message Was Given")
  {
    std::ostringstream logMessage;

    // Apply color if UseColor flag is set
    if(static_cast<unsigned int>(flags) &
       static_cast<unsigned int>(RantFlags::UseColor))
      logMessage << getRantLevelColorString(level);

    // Include log level if ShowRantLevel flag is set
    if(static_cast<unsigned int>(flags) &
       static_cast<unsigned int>(RantFlags::ShowRantLevel))
      logMessage << "[" << getRantLevelString(level) << "] ";

    // Append the rant message
    logMessage << rant;

    // Output the log message
    std::cout << logMessage.str() << std::endl;
  }

private:
  static const std::string &getRantLevelString(RantLevel level)
  {
    switch(level)
    {
    case RantLevel::TRACE:
      return "TRACE";
    case RantLevel::INFO:
      return "INFO";
    case RantLevel::DEBUG:
      return "DEBUG";
    case RantLevel::WARN:
      return "WARN";
    case RantLevel::ERROR:
      return "ERROR";
    case RantLevel::FATAL:
      return "FATAL";

    default:
      return "UNKNOWN";
    }
  }

  static const std::string &getRantLevelColorString(RantLevel level)
  {
    switch(level)
    {
    case RantLevel::TRACE:
      return "\033[38;2;0;255;255m"; // CYAN (RGB: 0, 255, 255)
    case RantLevel::INFO:
      return "\033[38;2;0;255;0m"; // GREEN (RGB: 0, 255, 0)
    case RantLevel::DEBUG:
      return "\033[38;2;0;0;255m"; // BLUE (RGB: 0, 0, 255)
    case RantLevel::WARN:
      return "\033[38;2;255;255;0m"; // YELLOW (RGB: 255, 255, 0)
    case RantLevel::ERROR:
      return "\033[38;2;255;165;0m"; // ORANGE (RGB: 255, 165, 0)
    case RantLevel::FATAL:
      return "\033[38;2;255;0;0m"; // RED (RGB: 255, 0, 0)

    default:
      return "\033[38;2;255;255;255m"; // WHITE
    }
  }
};

#define RantLog(...)                                                           \
  Logger::Rant(RantLevel::DEBUG, RantFlags::ShowRantLevel, __VA_ARGS__);

#define RantError(...)                                                         \
  Logger::Rant(RantLevel::ERROR, RantFlags::ShowRantLevel, __VA_ARGS__);

#define RantWarn(...)                                                          \
  Logger::Rant(RantLevel::WARN, RantFlags::ShowRantLevel, __VA_ARGS__);

#define RantFatal(...)                                                         \
  Logger::Rant(RantLevel::FATAL, RantFlags::ShowRantLevel, __VA_ARGS__);       \
  exit;
