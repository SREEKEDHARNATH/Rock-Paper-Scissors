#pragma once

#include "SDL_mixer.h"
#include "SDL_pixels.h"
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
class rText{
    std::string t;
    public:
        rImage img;
        rText(rFont& f,const char* txt,SDL_Colour fg={255,255,255,255},bool load=true);
        void set(rFont& f,const char* txt,SDL_Colour fg={255,255,255,255});
        std::string getText();
        void draw();
};
class rMusic{
    std::shared_ptr<Mix_Music> ptr;
    int vol=20;
    public:
        rMusic(const char* file,bool load=true);
        void set(const char* file);
        void play(bool loops=true);
        void pause();
        void resume();
        void halt();
        void setvol(int vol);
        std::shared_ptr<Mix_Music> get();
};
class rSoundEffect{
    std::shared_ptr<Mix_Chunk> ptr;
    int vol=60;
    public:
        rSoundEffect(const char* file,bool load=true);
        void set(const char* file);
        void play();
        void setvol(int vol);
        std::shared_ptr<Mix_Chunk> get();
};
