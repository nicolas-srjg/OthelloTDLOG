#pragma once

#include <iostream>
#include "utils.h"
#include<vector>


using namespace std;

class Player{
    int color;
    bool humanPlayer;
    std::string difficulty;
public:
    Player(std::string p="white", bool hp=true, std::string diff="h");
    int getColor()const{ return color; };
    int isHuman()const{ return humanPlayer; }
    std::string getDifficulty()const{return difficulty;};
    Move chooseMove(std::vector<Move> possibilities);
};

ostream& operator<<(ostream&, const Player& p);

/*
class HumanPlayer : public Player{
    Move chooseMove(std::vector<Move> possibilities);

};

class AIPlayer : public Player{
    Move chooseMove();
};
*/
