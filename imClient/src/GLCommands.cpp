#include "IMF_PCH.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "GLCommands.h"

const char *GetGLVersion()
{
  return reinterpret_cast<const char *>(glGetString(GL_VERSION));
}

void ClearScreen(const glm::vec4 &color)
{
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SwapBuffers() { SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow()); }