#pragma once

#include "GameEngine/GameContext.h"

class ImGuiLayer : public GameLayer
{
private:
  bool m_isOpen = false;
  // @TODO: this is to learn saving
  bool m_firstTime = true;

public:
  ImGuiLayer();
  ~ImGuiLayer();
  void OnEvent(const SDL_Event &event) override;
  void OnStart() override;
  void OnUpdate(float dt) override;

  void Begin();
  void End();
};