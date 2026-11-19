#pragma once

#include "SDL_rect.h"
#include "SDL_render.h"
#include <memory>
#include "SDL_ttf.h"
class rImage{
    std::shared_ptr<SDL_Texture> ptr;
    public:
        SDL_Rect r={0,0,0,0};
        rImage() = default;
        rImage(const char* file, bool autoset=true);
        rImage(Uint8 r,Uint8 g,Uint8 b,int w=32,int h=32, bool autoset=true);
        rImage(SDL_Texture* tex, bool autoset=true);

        void set(const char* file, bool autoset=true);
        void set(Uint8 r,Uint8 g,Uint8 b,int w=32,int h=32, bool autoset=true);
        void set(SDL_Texture* tex, bool autoset=true);

        void autoSet();
        void draw();
        std::shared_ptr<SDL_Texture> get();
};
class rFont{
    std::shared_ptr<TTF_Font> ptr;
    public:
        rFont(const char* file,int ptsize=32,bool load=true);
        void set(const char* file,int ptsize=32);
        std::shared_ptr<TTF_Font> get();
};