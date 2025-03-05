#pragma once

#include "IMF_PCH.h"

union SDL_Event;

struct GameLayer
{
public:
  GameLayer()
  {
    // @TODO: check if this works?
    // can i just delete all the layers like this from here.
    // for(auto &layer : GetGameContext().Layers)
    // {
    //   delete(layer);
    // }
  }

  virtual void OnEvent(const SDL_Event &event) {}
  virtual void OnResize() {}

  virtual void OnStart() {}
  virtual void OnUpdate(float deltaTime) {}
};

struct GameContext
{
  std::vector<GameLayer *> Layers;
};

inline GameContext &GetGameContext()
{
  static GameContext gameContext;
  return gameContext;
}