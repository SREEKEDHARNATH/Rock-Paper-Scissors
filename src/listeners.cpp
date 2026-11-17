#include "listeners.hpp"

#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "SDL_mouse.h"
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

int x=0,y=0;
float scrlx=0,scrly=0;
bool buttons[3]={false};
bool prvbuttons[3]={false};

void rMReg(SDL_MouseMotionEvent m){
    x=m.x;
    y=m.y;
}
void rMReg(SDL_MouseButtonEvent b){
    if (b.button > 0 && b.button < 4){
        buttons[b.button-1]=(b.state==SDL_PRESSED);
    }
}
void rMReg(SDL_MouseWheelEvent w){
    scrlx=w.preciseX;
    scrly=w.preciseY;
    if (w.direction==SDL_MOUSEWHEEL_FLIPPED){
        scrlx*=-1;
        scrly*=-1;
    }
}
bool rMIsPressed(int b){
    if (b > 0 && b<4){
        return buttons[b-1] && !prvbuttons[b-1];
    }
    return false;
}
bool rMIsDown(int b){
    if (b>0 && b<4){
        return buttons[b-1];
    }
    return false;
}
int rMGetX(){
    return x;
}
int rMGetY(){
    return y;
}
float rMGetScrlx(){
    return scrlx;
}
float rMGetScrly(){
    return scrly;
}
void rMUpdate(){
    for (int i=0;i<3;i++){
        prvbuttons[i]=buttons[i];
    }
    scrlx=0;
    scrly=0;
}