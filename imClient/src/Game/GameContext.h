#pragma once

#include "IMF_PCH.h"


union SDL_Event;

struct GameLayer
{
public:
    GameLayer() = default;

    virtual void OnEvent(const SDL_Event* event) {}

    virtual void OnStart() {}
    virtual void OnUpdate(float deltaTime) {}
};

struct GameContext
{
    std::vector<GameLayer*> Layers;
};

inline GameContext& GetGameContext()
{
    static GameContext gameContext;
    return gameContext;
}