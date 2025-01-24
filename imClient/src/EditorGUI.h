#pragma once

#include "IMF_PCH.h"


union SDL_Event;

struct EditorGUI
{
    bool IsOpen = false;

    std::unordered_map<std::string, bool> EditorWindows;
};

inline EditorGUI& GetEditorGUI()
{
    static EditorGUI editorGUI;
    return editorGUI;
}

void InitEditorGUI();
void CloseEditorGUI();

void StartEditorGUI();
void StopEditorGUI();

void ProcessImGuiEvents(const SDL_Event* sdlEvent);