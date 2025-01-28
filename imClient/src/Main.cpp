#include "IMF_PCH.h"

#include <SDL3/SDL.h>
#include <imgui.h>

#include "IMFAssert.h"
#include "Setup.h"
#include "EditorGUI.h"
#include "GlobalValues.h"
#include "GLCommands.h"
#include "Game/GameContext.h"

#include "Game/Game.h"


int main()
{
    // setup //
    SDL_Window* mainWindow = static_cast<SDL_Window*>(CreateWindow());
    SDL_GLContext mainContext =
        static_cast<SDL_GLContext>(CreateContext(mainWindow));

    // loading glad //
    InitGlad();


    // settigns and others //
    std::cout << "OpenGL Version: " << GetGLVersion() << std::endl;
    SDL_GL_SetSwapInterval(1); // vsync on


    // imgui init //
    InitEditorGUI();

    // @TEMP //
    GetEditorGUI().EditorWindows.emplace("Demo", true);
    bool startWindowOpen = true;

    GetGameContext().Layers.push_back(new GameScene());

    // delta time
    uint32_t lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;

    // start setup
    SDL_Event event;
    for(auto& layer : GetGameContext().Layers)
    { layer->OnStart(); }
    // gameloop //
    while(GetGame().IsRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            { GetGame().IsRunning = false; }

            for(auto& layer : GetGameContext().Layers)
            { layer->OnEvent(&event); }

            ProcessImGuiEvents(&event);
        }

        // delta time
        uint32_t currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // game context update
        for(auto& layer : GetGameContext().Layers)
        { layer->OnUpdate(deltaTime); }

        // imgui stuff //
        StartEditorGUI();

        UpdateEditorGUI();

        ClearScreen(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

        StopEditorGUI();

        SwapBuffers();
    }


    // close //
    CloseEditorGUI();
    DestroySDL(mainWindow, mainContext);

    return 0;
}