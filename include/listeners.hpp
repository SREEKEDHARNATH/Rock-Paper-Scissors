#pragma once

#include "SDL_events.h"
#include "SDL_keycode.h"

void rKReg(SDL_KeyboardEvent key);
bool rKIsPressed(SDL_KeyCode k);
bool rKIsPressed(SDL_Scancode sc);
bool rKIsDown(SDL_KeyCode k);
bool rKIsDown(SDL_Scancode sc);
void rKUpdate();

void rMReg(SDL_MouseMotionEvent m);
void rMReg(SDL_MouseButtonEvent b);
void rMReg(SDL_MouseWheelEvent w);
bool rMIsPressed(int b);
bool rMIsDown(int b);
int rMGetX();
int rMGetY();
float rMGetScrlx();
float rMGetScrly();
void rMUpdate();