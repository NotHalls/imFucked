#include "IMF_PCH.h"

#include <SDL3/SDL.h>
#include <imgui.h>

#include "IMFAssert.h"
#include "Setup.h"
#include "EditorGUI.h"
#include "GlobalValues.h"
#include "GLCommands.h"


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

    // gameloop //
    SDL_Event event;

    while(GetGame().IsRunning)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            { GetGame().IsRunning = false; }

            ProcessImGuiEvents(&event);
        }

        // imgui stuff //
        StartEditorGUI();

        if(startWindowOpen)
        {
            ImGui::Begin("Hello, world!", &startWindowOpen);
            ImGui::Text("This is some useful text.");
            ImGui::Button("This Is A Button");
            ImGui::End();
        }

        if(GetEditorGUI().EditorWindows.at("Demo"))
        {
            ImGui::Begin("Demo", &GetEditorGUI().EditorWindows.at("Demo"));
            ImGui::Text("Hello, world!");
            if(ImGui::Button("Close"))
            { GetEditorGUI().EditorWindows.at("Demo") = false; }
            ImGui::End();
        }

        ClearScreen(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

        StopEditorGUI();

        SwapBuffers();
    }


    // close //
    CloseEditorGUI();
    DestroySDL(mainWindow, mainContext);

    return 0;
}