#include "game.hpp"

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