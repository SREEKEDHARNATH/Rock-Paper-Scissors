#include "core.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_timer.h"
#include "SDL_ttf.h"
#include "SDL_video.h"
#include "api.hpp"
#include "game.hpp"
#include "listeners.hpp"
#include <iostream>
#include <utility>

std::string ip ="127.0.0.1";
const int port=8000;

std::pair<bool, const char*> init(int argc, char** argv);
SDLNet_SocketSet socketset;
TCPsocket handlerequest(bool listen){
    IPaddress i;
    TCPsocket sockett=nullptr;
    if (SDLNet_ResolveHost(&i, listen ? NULL : ip.c_str(), port)){
        std::cerr << SDLNet_GetError() << "\n";
        return nullptr;
    }
    if (listen){
        auto listener = SDLNet_TCP_Open(&i);
        if (!listener){
            std::cerr << SDLNet_GetError() << "\n";
            return nullptr;
        }
        std::cout << "listening..\n";
        while (!sockett){
            sockett=SDLNet_TCP_Accept(listener);
            SDL_Delay(10);
        }
        SDLNet_TCP_Close(listener);
    }
    else {
        std::cout << "connecting..\n";
        sockett = SDLNet_TCP_Open(&i);
    }
    return sockett;
}
TCPsocket socketimp;
void rSend(const char* msg){
    auto bytes = SDLNet_TCP_Send(socketimp, msg, sizeof(msg));
    if (bytes<=0){
        std::cerr << SDLNet_GetError() << "\n";
    }
}
std::string rRecieve(){
    if (SDLNet_CheckSockets(socketset, 0)){
        if (SDLNet_SocketReady(socketimp)){
            char buffer[256]={0};
            auto bytes = SDLNet_TCP_Recv(socketimp, buffer, sizeof(buffer)-1);
            if (bytes>0){
                buffer[bytes]='\0';
                return buffer;
            }
            else {
               std::cerr << SDLNet_GetError() << "\n";
            }
        }
    }
    return "";
}
void rRun(int argc, char** argv){
    for (int i=0;i<argc;i++){
        auto st=std::string(argv[i]);
        if ((st.find(".com") != st.npos) || st.find("192.") != st.npos){
            std::cout << "Using host:- " << st << "\n";
            ip=st;
            break;
        }
    }
    auto i=init(argc, argv);
    if (!i.first){
        std::cerr << i.second << "\n";
        return;
    }

    SDL_Event e;
    bool running = true;

    rImage bg("assets/images/bg.png",false);
    rImage rock("assets/images/rock.png");
    rImage paper("assets/images/paper.png");
    rImage scissors("assets/images/scissors.png");
    rImage selection("assets/images/selection.png");
    
    rFont f("assets/fonts/font.ttf");
    rMusic m("assets/music/MEGALOVANIA.mp3");
    m.setvol(10);
    m.play();
    
    rText status(f,std::string(rIsPlayer1() ? "Player1 Play" : "Player2 Play").c_str(), {0,0,0,0});
    status.img.r.x+=(rGetW()/2)-(status.img.r.w+30);

    SDL_ShowWindow(rGetWindow());
    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running=false;
                    break;
                case SDL_KEYUP:
                case SDL_KEYDOWN:
                    rKReg(e.key);
                    break;
                case SDL_MOUSEMOTION:
                    rMReg(e.motion);
                    break;
                case SDL_MOUSEWHEEL:
                    rMReg(e.wheel);
                    break;
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEBUTTONDOWN:
                    rMReg(e.button);
                    break;
            }
        }
        if (rKIsPressed(SDLK_ESCAPE)){
            running=false;
        }
        SDL_RenderClear(rGetRenderer());
        bg.draw();
        draw(rock, paper, scissors, selection, rIsPlayer1(), f,status);
        SDL_RenderPresent(rGetRenderer());
        
        rKUpdate();
        rMUpdate();
        SDL_Delay(16);
    }
}
SDL_Surface* icon;
std::pair<bool, const char*> init(int argc, char** argv){
    int img_flags=IMG_INIT_PNG;
    int sound_flags=MIX_INIT_MP3;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
        return {false, SDL_GetError()};
    }
    if (SDLNet_Init()){
        return {false, SDLNet_GetError()};;
    }
    if ((IMG_Init(img_flags) & img_flags) != img_flags){
        return {false, IMG_GetError()};;
    }
    if (TTF_Init()){
        return {false, TTF_GetError()};;
    }
    if ((Mix_Init(sound_flags) & sound_flags) != sound_flags){
        return {false, Mix_GetError()};;
    }
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
    rGetWindow()=SDL_CreateWindow(rGetTitle(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, rGetW(), rGetH(), SDL_WINDOW_HIDDEN);
    if (!rGetWindow()){
        return {false, SDL_GetError()};
    }
    rGetRenderer()=SDL_CreateRenderer(rGetWindow(), -1, 0);
    if (!rGetRenderer()){
        return {false, SDL_GetError()};
    }
    icon = IMG_Load("assets/images/logo.png");
    if (icon){
        SDL_SetWindowIcon(rGetWindow(), icon);
    }
    else {
        return {false, IMG_GetError()};;
    }
    rIsPlayer1()=argv[argc-1] != std::string("-player2");
    socketimp = handlerequest(rIsPlayer1());
    if (socketimp){
        socketset=SDLNet_AllocSocketSet(1);
        SDLNet_TCP_AddSocket(socketset, socketimp);
    }

    return {true,""};
}
void rQuit(){
    if (socketset){
        if (socketimp){
            SDLNet_TCP_DelSocket(socketset, socketimp);
            SDLNet_TCP_Close(socketimp);
        }
        SDLNet_FreeSocketSet(socketset);
    }
    if (icon){
        SDL_FreeSurface(icon);
    }
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDLNet_Quit();
    IMG_Quit();
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
bool& rIsPlayer1(){
    static bool p1;
    return p1;
}