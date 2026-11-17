#pragma once

#include "SDL_events.h"
#include "SDL_keycode.h"

void rKReg(SDL_KeyboardEvent key);
bool rKIsPressed(SDL_KeyCode k);
bool rKIsPressed(SDL_Scancode sc);
bool rKIsDown(SDL_KeyCode k);
bool rKIsDown(SDL_Scancode sc);
void rKUpdate();