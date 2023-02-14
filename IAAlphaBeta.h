#pragma once
#include <iostream>
#include "board.h"
#include "tree.h"

using namespace std;

double heuristic = 2;

double minimax(Board* position, int depth);
