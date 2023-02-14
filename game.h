#pragma once
#include "board.h"

void play(Board B);

//pourcentage of winning against random after 100 games
float benchmark(int nb_games, char competitor);
