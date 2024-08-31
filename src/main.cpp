#include <iostream>
#include <stdexcept>
#include <time.h>

#include "board.h"
#include "player.h"
#include "AI.h"
#include "game.h"


using namespace std;

int main()
{
    try {
        //initialize player with true for human and 'r' for AI random, 'e' for easy, and 'h' for hard (default)

        srand(time(0));
        clock_t t_init, t_fin;
        float temps;
        t_init=clock();
        Player p1("black",false, "h");
        Player p2("white",false, "h");
        Board B(p1,p2);

        play(B);
        t_fin=clock();
        temps = (float)(t_fin-t_init)/CLOCKS_PER_SEC;
        cout<<"le temps d'execution est: "<<temps<<endl;
        //cout<<"le pourcentage de victoire pour l'IA est "<<benchmark(10,  'h')<<endl;
        //cout<<test_sort()<<endl;
    } catch (invalid_argument h) {
        cerr<<"Invalid argument: "<<h.what()<<endl;
    }


    return 0;
}
