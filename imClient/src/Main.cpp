#include "IMF_PCH.h"

#include <SDL3/SDL.h>
#include <imgui.h>

#include "GameEngine/GameContext.h"
#include "GlobalValues.h"
#include "IMFAssert.h"
#include "Renderer/GLCommands.h"
#include "Renderer/Renderer.h"
#include "Setup.h"

#include "GameEngine/Game.h"
#include "GameEngine/ImGuiLayer.h"

int main()
{
  // setup //
  Setup();
  SDL_Window *mainWindow = static_cast<SDL_Window *>(CreateWindow());
  SDL_GLContext mainContext =
      static_cast<SDL_GLContext>(CreateContext(mainWindow));

  // loading glad //
  InitGlad();

  // settigns and others //
  std::cout << "OpenGL Version: " << GetGLVersion() << std::endl;
  SDL_GL_SetSwapInterval(1); // vsync on

  // Initializing the renderer
  Renderer::Init({"imClient/assets/shaders/2DShader.vertex.glsl",
                  "imClient/assets/shaders/2DShader.fragment.glsl"});

  // imgui
  ImGuiLayer *m_imguiLayer = new ImGuiLayer();

  GetGameContext().Layers.push_back(new GameScene());
  GetGameContext().Layers.emplace_back(m_imguiLayer);

  // delta time
  uint32_t lastTime = SDL_GetTicks();
  float deltaTime = 0.0f;

  // start setup
  SDL_Event event;
  for(auto &layer : GetGameContext().Layers)
  {
    layer->OnStart();
  }
  // gameloop //
  while(GetGame().IsRunning)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_EVENT_QUIT)
      {
        GetGame().IsRunning = false;
      }

      for(auto itr = GetGameContext().Layers.end();
          itr != GetGameContext().Layers.begin();)
      {
        (*--itr)->OnEvent(event);
      }
    }

    // delta time
    uint32_t currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    ClearScreen(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

    // game context update
    m_imguiLayer->Begin();
    for(auto &layer : GetGameContext().Layers)
    {
      layer->OnUpdate(deltaTime);
    }
    m_imguiLayer->End();

    SwapBuffers();
  }

  // close //
  // we don't need this delete here because we will be closing the appp anyway
  // but i would like to have it
  delete(m_imguiLayer);
  DestroySDL(mainWindow, mainContext);

  return 0;
}