#include "player.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Player::Player(std::string p,bool hp, std::string diff){
    if(p!="white"&& p!="black") throw invalid_argument("This color doesn't exist");
    if(p=="white") color=1;
    else if(p=="black") color=-1;
    else cout<<"erreur";
    humanPlayer=hp;
    if (diff!="h"&& diff!="e" && diff!="r") throw invalid_argument("This mode of difficulty doesn't exist");
    difficulty=diff;
}


Move Player::chooseMove(vector<Move> possibilities){
    if (humanPlayer){
        int col,row;
        cout<<"Enter first the row and then the column"<<endl;
        cout<<"Row:";
        cin>>row;
        if (row!=1 && row!=2 &&row!=3&&row!=4&&row!=5&&row!=6&&row!=7&&row!=8) throw invalid_argument("This number isn't a line");
        cout<<"Column:";
        cin>>col;
        if (col!=1 && col!=2 &&col!=3&&col!=4&&col!=5&&col!=6&&col!=7&&col!=8) throw invalid_argument("This number isn't a column");
        Move potential_move=Move(row,col);
        while (!(potential_move.inVector(possibilities))){
            cout<<"Invalid move"<<endl;
            cout<<"Enter first the row and then the column"<<endl;
            cout<<"Row:";
            cin>>row;
            cout<<"Column:";
            cin>>col;
            potential_move=Move(row,col);
        }
        return potential_move;
    }
    else{
        return possibilities[0];
    }
}

ostream& operator<<(ostream& str,const Player& p){
    if (p.getColor()==-1)
        str<<"Black";
    else
        str<<"White";
    return str;
}
