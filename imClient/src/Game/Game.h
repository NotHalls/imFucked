#pragma once

#include "GameContext.h"

#include <SDL3/SDL.h>


class GameScene : public GameLayer
{
private:
    char m_firstTimeKey = (1 << 1);

public:
    GameScene() {}
    void OnEvent(const SDL_Event* event) override
    {
        switch(event->type)
        {
            case SDL_EVENT_KEY_DOWN:
                switch(event->key.scancode)
                {
                    case SDL_SCANCODE_W:
                        std::cout << "HEHEH" << std::endl;
                    break;
                }
            break;
        }
    }

    void OnStart() override
    {
        std::cout << "STARTED!" << std::endl;
    }

    void OnUpdate(float dt) override
    {
    }
};