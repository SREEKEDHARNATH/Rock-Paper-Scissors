#include "api.hpp"
#include "SDL_image.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include "SDL_ttf.h"
#include "core.hpp"
#include <iostream>

rImage::rImage(const char* file, bool autoset){
    set(file,autoset);
}
rImage::rImage(Uint8 r,Uint8 g,Uint8 b,int w,int h, bool autoset){
    set(r,g,b,w,h,autoset);
}
rImage::rImage(SDL_Texture* tex, bool autoset){
    set(tex,autoset);
}
void rImage::set(const char* file, bool autoset){
    auto tex = IMG_LoadTexture(rGetRenderer(), file);
    if (!tex){
        std::cerr << IMG_GetError() << "\n";
        return;
    }
    ptr.reset(tex, SDL_DestroyTexture);
    if (autoset){
        autoSet();
    }
}
void rImage::set(Uint8 r,Uint8 g,Uint8 b,int w,int h, bool autoset){
    auto surf=SDL_CreateRGBSurface(0, w,h,32,0,0,0,0);
    if (!surf){
        std::cerr << SDL_GetError() << "\n";
        return;
    }
    auto colour = SDL_MapRGB(surf->format, r, g, b);
    SDL_FillRect(surf, NULL,colour);
    auto tex = SDL_CreateTextureFromSurface(rGetRenderer(), surf);
    if (!tex){
        std::cerr << SDL_GetError() << "\n";
        return;
    }
    ptr.reset(tex, SDL_DestroyTexture);
    if (autoset){
        autoSet();
    }
}
void rImage::set(SDL_Texture* tex, bool autoset){
    if (!tex){
        return;
    }
    ptr.reset(tex, SDL_DestroyTexture);
    if (autoset){
        autoSet();
    }
}

void rImage::autoSet(){
if (get().get()){
    SDL_QueryTexture(get().get(), NULL,NULL,&r.w,&r.h);
}
}
void rImage::draw(){
    if (r.w==0 || r.h==0){
        SDL_RenderCopy(rGetRenderer(), get().get(),NULL,NULL);
    }
    else {
        SDL_RenderCopy(rGetRenderer(), get().get(),NULL,&r);
    }
}
std::shared_ptr<SDL_Texture> rImage::get(){
    return ptr;
}

rFont::rFont(const char* file,int ptsize,bool load){
    if (load){
        set(file,ptsize);
    }
}
void rFont::set(const char* file,int ptsize){
    auto t=TTF_OpenFont(file, ptsize);
    if (!t){
        std::cerr << TTF_GetError() << "\n";
        return;
    }
    ptr.reset(t, TTF_CloseFont);
}
std::shared_ptr<TTF_Font> rFont::get(){
    return ptr;
}