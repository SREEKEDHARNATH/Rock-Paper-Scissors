#pragma once
#include "SDL_render.h"
#include "SDL_video.h"

void rRun();
void rQuit();
SDL_Window*& rGetWindow();
SDL_Renderer*& rGetRenderer();
int rGetW();
int rGetH();
const char* rGetTitle();
