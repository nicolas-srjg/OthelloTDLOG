#pragma once

#include <iostream>
#include "tree.h"

using namespace std;


//heuristic values
//const double center;
//const double corner;


float heuristic(Board position, Player player_to_maximize);

float minimax(Board position, int depth, float alpha, float beta, Player player_to_maximize, int max_depth, Move& move_to_do);

float minimax_sans_alpha_beta(Board position, int depth, Player player_to_maximize, int max_depth, Move& move_to_do);


Move random_move(Board position);

vector<Move> sortMove(vector<Move> possibilities);

bool test_sort();

//vector<Move> permute(vector<Move> possibilities);
