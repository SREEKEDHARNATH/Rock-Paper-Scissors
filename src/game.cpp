#include "game.hpp"
#include "SDL_mouse.h"
#include "SDL_rect.h"
#include "SDL_timer.h"
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
bool confirmed=false;
SDL_Rect drag(rImage& obj,rImage& select,playOption pla,rFont& f,rText& status){
    static rSoundEffect rockS("assets/sound effects/rock.mp3");
    static rSoundEffect paperS("assets/sound effects/paper.mp3");
    static rSoundEffect scissorS("assets/sound effects/scissor.mp3");
    
    static rImage confirm("assets/images/confirm.png");
    static std::unordered_map<int, std::pair<int, bool>> map;
    static std::vector<SDL_Rect> rects;

    static std::vector<bool> hold;
    static std::vector<bool> sel;
    static std::vector<playOption> playop;
    static int confirmedpos;
    if (!(confirm.r.x==select.r.x)){
        confirm.r.x=select.r.x+90;
        confirm.r.y=select.r.y;
    }
    SDL_Rect mouse={rMGetX(),rMGetY(),1,1};
    auto& p = map[obj.r.x+obj.r.y+obj.r.w+obj.r.h];
    if (!p.second){
        p.second=true;
        hold.push_back(false);
        sel.push_back(false);
        rects.push_back(obj.r);
        playop.push_back(pla);
        p.first=(hold.size()-1);
    }
    if (!confirmed){
        for (int i=0;i<sel.size();i++){
            if (sel[i]){
                confirm.draw();
                if (SDL_HasIntersection(&mouse,&confirm.r)){
                    if (rMIsPressed(SDL_BUTTON_LEFT)){
                        confirmed=true;
                        confirmedpos=i;
                        if (playop[i] == playOption::ROCK){
                            rSend("R");
                            status.set(f, ((rIsPlayer1() ? "Player1 has chosen " : "Player2 has chosen ") + std::string("Rock")).c_str());
                            rockS.play();
                        }
                        else if (playop[i] == playOption::PAPER){
                            rSend("P");
                            status.set(f, ((rIsPlayer1() ? "Player1 has chosen " : "Player2 has chosen ") + std::string("Paper")).c_str());
                            paperS.play();
                        }
                        else {
                            rSend("S");
                            status.set(f, ((rIsPlayer1() ? "Player1 has chosen " : "Player2 has chosen ") + std::string("Scissor")).c_str());
                            scissorS.play();
                        }
                    }
                }
            }
        }
        if (SDL_HasIntersection(&obj.r, &mouse) || hold[p.first]){
            if (rMIsDown(SDL_BUTTON_LEFT)){
                bool shouldhold=false;
                for (int i=0;i<hold.size();i++){
                    if (i==p.first){
                        continue;
                    }
                    if (hold[i]){
                        shouldhold=true;
                    }
                }
                hold[p.first]=!shouldhold;
            }
            else {
                hold[p.first]=false;
            }
        }
        if (hold[p.first]){
            obj.r.x=mouse.x-(obj.r.w/2);
            obj.r.y=mouse.y-(obj.r.h/2);
            SDL_Rect se=select.r;
            se.x-=(se.w*1.5);
            se.y-=(se.h*1.5);
            se.w*=3;
            se.h*=3;
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
    else {
        return select.r;
    }
}
bool same(SDL_Rect r,SDL_Rect r2){
    return (r.x==r2.x) && (r.y==r2.y) && (r.w==r2.w) && (r.h==r2.h);
}
void draw(rImage& rock,rImage& paper,rImage& Scissor,rImage& select, bool player1,rFont& f,rText& status){
    static rSoundEffect winS("assets/sound effects/win.mp3");
    static rSoundEffect lossS("assets/sound effects/loss.mp3");
    static rSoundEffect tieS("assets/sound effects/tie.mp3");
    
    status.draw();    
    playOption pl;
    if (same(rock.r, select.r)){
        pl=playOption::ROCK;
    }
    else if (same(paper.r, select.r)){
        pl=playOption::PAPER;
    }
    else if (same(Scissor.r, select.r)){
        pl=playOption::SCISSORS;
    }
    if (confirmed){
        static auto start=SDL_GetTicks64();
        if ((SDL_GetTicks64()-start)>1000){
            auto msg = rRecieve();
            if (!msg.empty()){
                playOption en;
                if (msg == "R"){
                    en=playOption::ROCK;
                }
                else if (msg=="P"){
                    en=playOption::PAPER;
                }
                else if (msg=="S"){
                    en=playOption::SCISSORS;
                }
                auto res=evaluate(pl,en);
                switch (res) {
                    case state::WIN:
                        winS.play();
                        break;
                    case state::LOSS:
                        lossS.play();
                        break;
                    case state::TIE:
                        tieS.play();
                        break;
                }
                confirmed=false;
                std::string txt = ((rIsPlayer1() ? "Player1 has " : "Player2 has ") + std::string(((res == state::WIN) ? "Won." : ((res==state::TIE) ? "Tied." : "Loss."))));
                status.set(f, txt.c_str());
            }
            start=SDL_GetTicks64();
        }
    }
    else {
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
        rock.r=drag(rock,select,playOption::ROCK,f,status);
        paper.r=drag(paper,select,playOption::PAPER,f,status);
        Scissor.r=drag(Scissor,select,playOption::SCISSORS,f,status);
        select.draw();
    
        rock.draw();
        paper.draw();
        Scissor.draw();
    }
}