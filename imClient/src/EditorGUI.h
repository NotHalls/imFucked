// #pragma once

// #include "IMF_PCH.h"

// union SDL_Event;

// struct EditorGUI
// {
//   bool IsOpen = false;
//   // @TODO: this is to learn saving
//   bool FirstTime = true;

//   std::unordered_map<std::string, bool> EditorWindows;
// };

// inline EditorGUI &GetEditorGUI()
// {
//   static EditorGUI editorGUI;
//   return editorGUI;
// }

// void InitEditorGUI();
// void CloseEditorGUI();

// void StartEditorGUI();
// void UpdateEditorGUI();
// void StopEditorGUI();

// void ProcessImGuiEvents(const SDL_Event *sdlEvent);