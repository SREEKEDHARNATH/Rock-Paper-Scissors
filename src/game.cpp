#include "game.hpp"
#include "SDL_mouse.h"
#include "SDL_rect.h"
#include "api.hpp"
#include "core.hpp"
#include "listeners.hpp"
#include <unordered_map>
#include <utility>
#include <vector>

state evaluate(playOption p1, playOption p2){
    if (p1==playOption::ROCK){
        if (p2==playOption::PAPER){
            return state::LOSS;
        }
        else if (p2==playOption::SCISSORS){
            return state::WIN;
        }
        else {
            return state::TIE;
        }
    }
    else if (p1==playOption::PAPER){
        if (p2==playOption::ROCK){
            return state::WIN;
        }
        else if (p2==playOption::SCISSORS){
            return state::LOSS;
        }
        else {
            return state::TIE;
        }
    }
    else {
        if (p2==playOption::ROCK){
            return state::LOSS;
        }
        else if (p2==playOption::PAPER){
            return state::WIN;
        }
        else {
            return state::TIE;
        }
    }
}
SDL_Rect drag(rImage& obj){
    static std::unordered_map<int, std::pair<int, bool>> map;
    static std::vector<SDL_Rect> rects;
    static std::vector<bool> hold;

    auto& p = map[obj.r.x+obj.r.y+obj.r.w+obj.r.h];
    if (!p.second){
        p.second=true;
        hold.push_back(false);
        rects.push_back(obj.r);
        p.first=hold.size()-1;
    }

    SDL_Rect mouse={rMGetX(),rMGetY(),1,1};
    if (SDL_HasIntersection(&obj.r, &mouse) || hold[p.first]){
        if (rMIsDown(SDL_BUTTON_LEFT)){
            hold[p.first]=true;
        }
        else {
            hold[p.first]=false;
        }
    }
    if (hold[p.first]){
        SDL_Rect r = obj.r;
        r.x=mouse.x;
        r.y=mouse.y;
        return r;
    }
    else {
        return rects[p.first];
    }
}
void draw(rImage& rock,rImage& paper,rImage& Scissor,rImage& select){
    rock.r.x=200;
    rock.r.y=600;
    paper.r.x=600;
    paper.r.y=600;
    Scissor.r.x=1000;
    Scissor.r.y=600;
    
    rock.r=drag(rock);
    paper.r=drag(paper);
    Scissor.r=drag(Scissor);
    
    select.r.x=(rGetW()/2)-select.r.w;
    select.r.y=(rGetH()/2)+10;
    select.draw();
    select.r.y-=select.r.h+10;
    select.draw();

    rock.draw();
    paper.draw();
    Scissor.draw();

    rock.r.x=200;
    paper.r.x=600;
    Scissor.r.x=1000;
    rock.r.y=100;
    paper.r.y=100;
    Scissor.r.y=100;

    rock.r=drag(rock);
    paper.r=drag(paper);
    Scissor.r=drag(Scissor);

    rock.draw();
    paper.draw();
    Scissor.draw();
}