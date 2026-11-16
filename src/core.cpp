#include "core.hpp"
#include "SDL.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include <iostream>
#include <utility>

std::pair<bool, const char*> init();
void rRun(){
    auto i=init();
    if (!i.first){
        std::cerr << i.second << "\n";
        return;
    }

    SDL_Event e;
    bool running = true;
    SDL_ShowWindow(rGetWindow());
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running=false;
                    break;
            }
        }

        SDL_RenderClear(rGetRenderer());
        SDL_RenderPresent(rGetRenderer());
        
        SDL_Delay(16);
    }
}

std::pair<bool, const char*> init(){
    if (SDL_Init(SDL_INIT_EVERYTHING)){
        return {false, SDL_GetError()};
    }
    rGetWindow()=SDL_CreateWindow(rGetTitle(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, rGetW(), rGetH(), SDL_WINDOW_HIDDEN);
    if (!rGetWindow()){
        return {false, SDL_GetError()};
    }
    rGetRenderer()=SDL_CreateRenderer(rGetWindow(), -1, 0);
    if (!rGetRenderer()){
        return {false, SDL_GetError()};
    }
    return {true,""};
}
void rQuit(){
    if (rGetRenderer()){
        SDL_DestroyRenderer(rGetRenderer());
    }
    if (rGetWindow()){
        SDL_DestroyWindow(rGetWindow());
    }
    SDL_Quit();
}
SDL_Window*& rGetWindow(){
    static SDL_Window* window=nullptr;
    return window;
}
SDL_Renderer*& rGetRenderer(){
    static SDL_Renderer* renderer=nullptr;
    return renderer;
}
int rGetW(){
    return 1280;
}
int rGetH(){
    return 720;
}
const char* rGetTitle(){
    return "Rock Paper Scissors";
}
