#pragma once

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