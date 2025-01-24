#include "IMF_PCH.h"

#include "Setup.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "GlobalValues.h"


void Setup()
{
    IMF_ASSERT(!(SDL_Init(SDL_INIT_VIDEO)),
        "Failed To Init SDL: " + std::string(SDL_GetError()));
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE
    );
}

void* CreateWindow()
{
    SDL_Window* window = SDL_CreateWindow(
        "imFucked", GetGame().Width, GetGame().Height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    IMF_ASSERT(!window,
        "Failed To Init SDL Window: " + std::string(SDL_GetError()));

    return window;
}

void* CreateContext(void* window)
{
    SDL_GLContext context =
        SDL_GL_CreateContext(static_cast<SDL_Window*>(window));
    IMF_ASSERT(!context,
        "Failed To Create SDL GL Context: " + std::string(SDL_GetError()));

    return context;
}

void DestroySDL(void* mainWindow, void* mainContext)
{
    SDL_GL_DestroyContext(static_cast<SDL_GLContext>(mainContext));
    SDL_DestroyWindow(static_cast<SDL_Window*>(mainWindow));
    SDL_Quit();
}

void InitGlad()
{
    IMF_ASSERT(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress),
        "Failed To Load GLAD");
}