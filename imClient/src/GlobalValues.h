#pragma once

#include "IMF_PCH.h"

struct Game
{
  int Width = 1280;
  int Height = 720;

  bool IsRunning = true;
};

inline Game &GetGame()
{
  static Game game;
  return game;
}