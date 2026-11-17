#include "listeners.hpp"

#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "SDL_scancode.h"
 
bool keys[SDL_NUM_SCANCODES]={false};
bool prvkeys[SDL_NUM_SCANCODES]={false};

void rKReg(SDL_KeyboardEvent key){
    if (key.keysym.scancode > 0 && key.keysym.scancode < SDL_NUM_SCANCODES){
        keys[key.keysym.scancode]=(key.state==SDL_PRESSED);
    }
}
bool rKIsPressed(SDL_KeyCode k){
    return rKIsPressed(SDL_GetScancodeFromKey(k));
}
bool rKIsPressed(SDL_Scancode sc){
    if (sc>0&&sc<SDL_NUM_SCANCODES){
        return keys[sc] && !prvkeys[sc];
    }
    return false;
}
bool rKIsDown(SDL_KeyCode k){
    return rKIsDown(SDL_GetScancodeFromKey(k));
}
bool rKIsDown(SDL_Scancode sc){
    if (sc>0&&sc<SDL_NUM_SCANCODES){
        return keys[sc];
    }
    return false;
}
void rKUpdate(){
    for (int i=0;i<SDL_NUM_SCANCODES;i++){
        prvkeys[i]=keys[i];
    }
}