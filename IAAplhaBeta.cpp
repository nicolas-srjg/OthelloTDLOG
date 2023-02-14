#include <iostream>
#include "board.h"
#include "math.h"
#include "IAAlphaBeta.h"

using namespace std;

double minimax(Board* position, int depth){
    if(depth == 0 || position->cannotPlay())
        return heuristic;

    if(heuristic){
        double maXEval=-INFINITY;
        for(int i=0;i<1;i++){
            double eval = minimax (child, depth - 1);
            double maXEval = maX(maXEval, eval);
            return maxEval;
        }
    }
    else{
        double minEval= INFINITY;
        for(){
            double eval = minimax(child, depth - 1, true);
            double minEval = min(minEval, eval);
        }
        return minEval;

    }
}
