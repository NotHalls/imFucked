#include "ImGuiLayer.h"
#include "IMF_PCH.h"

#include <SDL3/SDL.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl3.h>
#include <imgui.h>

#include "GlobalValues.h"

ImGuiLayer::ImGuiLayer()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImGui_ImplSDL3_InitForOpenGL(SDL_GL_GetCurrentWindow(),
                               SDL_GL_GetCurrentContext());
  ImGui_ImplOpenGL3_Init("#version 460");
}
ImGuiLayer::~ImGuiLayer()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer::OnEvent(const SDL_Event &event)
{
  ImGui_ImplSDL3_ProcessEvent(&event);
}
void ImGuiLayer::OnStart() {}
void ImGuiLayer::OnUpdate(float dt)
{
  if(m_firstTime)
  {
    // @TODO: can we add something other that that variable
    // to get the X (exit) button?
    // ImGui::Begin("First Time Here?", &m_firstTime);
    // ImGui::Text("This is some useful text.");
    // if(ImGui::Button("OK!"))
    // {
    //   m_firstTime = false;
    // }
    // ImGui::End();
  }
}

void ImGuiLayer::Begin()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Menu"))
  {
    if(ImGui::MenuItem("Editor"))
    {
      m_isOpen = true;
    }
    ImGui::EndMenu();
  }
  if(ImGui::BeginMenu("Game"))
  {
    if(ImGui::MenuItem("Exit"))
    {
      GetGame().IsRunning = false;
    }
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();

  if(m_isOpen)
  {
    ImGui::Begin("Dockspace", &m_isOpen,
                 ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking);
    ImGuiID dockspaceID = ImGui::GetID("EditorDockspace");
    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
    if(ImGui::BeginMenuBar())
    {
      if(ImGui::BeginMenu("Menu"))
      {
        if(ImGui::MenuItem("Exit Editor"))
        {
          m_isOpen = false;
        }
        if(ImGui::MenuItem("Exit"))
        {
          GetGame().IsRunning = false;
        }
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }
    ImGui::End();
  }
}

void ImGuiLayer::End()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  SDL_Window *currentWindow = SDL_GL_GetCurrentWindow();
  SDL_GLContext currentContext = SDL_GL_GetCurrentContext();

  ImGui::UpdatePlatformWindows();
  ImGui::RenderPlatformWindowsDefault(nullptr, nullptr);

  SDL_GL_MakeCurrent(currentWindow, currentContext);
}