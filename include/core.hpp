#pragma once
#include "SDL_render.h"
#include "SDL_video.h"
#include <string>

void rSend(const char* msg);
std::string rRecieve();
void rRun(int argc, char** argv);
void rQuit();
SDL_Window*& rGetWindow();
SDL_Renderer*& rGetRenderer();
int rGetW();
int rGetH();
const char* rGetTitle();
bool& rIsPlayer1();