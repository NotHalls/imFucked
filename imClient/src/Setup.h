#pragma once

#include "IMF_PCH.h"


void Setup();

void* CreateWindow();
void* CreateContext(void* window);
void DestroySDL(void* mainWindow, void* mainContext);

void InitGlad();