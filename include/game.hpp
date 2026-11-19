#pragma once

#include "api.hpp"
enum playOption{
    ROCK,
    PAPER,
    SCISSORS
};
enum state{
    WIN,
    TIE,
    LOSS
};

state evaluate(playOption p1, playOption p2);
void draw(rImage& rock,rImage& paper,rImage& Scissor,rImage& select,bool player1,rFont& f,rText& status);