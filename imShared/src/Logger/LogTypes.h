#pragma once

#include <string>

enum class RantLevel : short
{
  // useful for tracing a part of somethign like a function
  TRACE = 0,
  // information that would be useful for not just developers but sysadmins and
  // others
  DEBUG = 1,
  // information about a function being called or a setting being changed
  INFO = 2,
  // warning about something in the codebase, protential risks
  WARN = 3,
  // any error which causes something in the codebase to not run properly, EX:
  // data not being loaded into a buffer
  ERROR = 4,
  // any error that is causing the application to shutdown or crash (will cause
  // a breakpoint)
  FATAL = 5,
};

enum class RantFlags : unsigned int
{ // we will leave the default as 2 (ShowRantLevel)
  // Nothing, no color, nothing... just... nothing
  None = 0,
  // includes colors in the rant
  UseColor = 1 << 0,
  // include what log level the rant is
  ShowRantLevel = 2 << 1,
  // shows the object name, like the function that called it
  ShowObjectName = 3 << 2,
};