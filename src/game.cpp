#include "game.hpp"
#include "SDL_mouse.h"
#include "SDL_rect.h"
#include "api.hpp"
#include "core.hpp"
#include "listeners.hpp"
#include <iostream>
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
SDL_Rect drag(rImage& obj,rImage& select){
    static std::unordered_map<int, std::pair<int, bool>> map;
    static std::vector<SDL_Rect> rects;
    static std::vector<bool> hold;
    static std::vector<bool> sel;

    auto& p = map[obj.r.x+obj.r.y+obj.r.w+obj.r.h];
    if (!p.second){
        p.second=true;
        hold.push_back(false);
        sel.push_back(false);
        rects.push_back(obj.r);
        p.first=(hold.size()-1);
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
        obj.r.x=mouse.x-(obj.r.w/2);
        obj.r.y=mouse.y-(obj.r.h/2);
        SDL_Rect se=select.r;
        se.w*=2;
        se.h*=2;
        if (SDL_HasIntersection(&mouse, &se)){
            sel[p.first]=true;
            return select.r;
        }
        sel[p.first]=false;
        return obj.r;
    }
    else {
        if (sel[p.first]){
            return select.r;
        }
        return rects[p.first];
    }
}
void draw(rImage& rock,rImage& paper,rImage& Scissor,rImage& select, bool player1){
    select.r.x=(rGetW()/2)-select.r.w;
    select.r.y=(rGetH()/2)+10;
    rock.r.x=200;
    paper.r.x=600;
    Scissor.r.x=1000;
    if (player1){
        rock.r.y=600;
        paper.r.y=600;
        Scissor.r.y=600;
    }
    else {
        rock.r.y=100;
        paper.r.y=100;
        Scissor.r.y=100;
        select.r.y-=select.r.h+10;
    }
    
    rock.r=drag(rock,select);
    paper.r=drag(paper,select);
    Scissor.r=drag(Scissor,select);
    
    select.draw();

    rock.draw();
    paper.draw();
    Scissor.draw();
}