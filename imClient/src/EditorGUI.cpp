#include "IMF_PCH.h"

#include <SDL3/SDL.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl3.h>
#include <glad/glad.h>
#include <imgui.h>

#include "EditorGUI.h"
#include "GlobalValues.h"

void InitEditorGUI()
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

void CloseEditorGUI()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}

void StartEditorGUI()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();

  ImGui::BeginMainMenuBar();
  if(ImGui::BeginMenu("Menu"))
  {
    if(ImGui::MenuItem("Editor"))
    {
      GetEditorGUI().IsOpen = true;
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

  if(GetEditorGUI().IsOpen)
  {
    ImGui::Begin("Dockspace", &GetEditorGUI().IsOpen,
                 ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking);
    ImGuiID dockspaceID = ImGui::GetID("EditorDockspace");
    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
    if(ImGui::BeginMenuBar())
    {
      if(ImGui::BeginMenu("Menu"))
      {
        if(ImGui::MenuItem("Exit Editor"))
        {
          GetEditorGUI().IsOpen = false;
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

void UpdateEditorGUI()
{
  if(GetEditorGUI().FirstTime)
  {
    // @TODO: can we add something other that that variable
    // to get the X (exit) button?
    ImGui::Begin("First Time Here?", &GetEditorGUI().FirstTime);
    ImGui::Text("This is some useful text.");
    if(ImGui::Button("OK!"))
    {
      GetEditorGUI().FirstTime = false;
    }
    ImGui::End();
  }

  if(GetEditorGUI().EditorWindows.at("Demo"))
  {
    ImGui::Begin("Demo", &GetEditorGUI().EditorWindows.at("Demo"));
    ImGui::Text("Hello, world!");
    if(ImGui::Button("Close"))
    {
      GetEditorGUI().EditorWindows.at("Demo") = false;
    }
    ImGui::End();
  }
}

void StopEditorGUI()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  SDL_Window *currentWindow = SDL_GL_GetCurrentWindow();
  SDL_GLContext currentContext = SDL_GL_GetCurrentContext();

  ImGui::UpdatePlatformWindows();
  ImGui::RenderPlatformWindowsDefault(nullptr, nullptr);

  SDL_GL_MakeCurrent(currentWindow, currentContext);
}

void ProcessImGuiEvents(const SDL_Event *sdlEvent)
{
  ImGui_ImplSDL3_ProcessEvent(sdlEvent);
}