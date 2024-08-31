#include "utils.h"

Move::Move(int i,int j){
    row=i;
    col=j;
}

int Move::getCol(){return col;}
int Move::getRow(){return row;}
void Move::setCol(int j){col=j;}
void Move::setRow(int i){row=i;}

bool Move::operator==(Move a){
    return(row==a.row && col==a.col);
}

bool Move::inVector(std::vector<Move> V){
    std::vector<Move> ::iterator it = V.begin();
    for(;it!=V.end();++it){
        if (*this==*it)
            return true;
    }
    return false;
}

bool Move::inCorner(){
    return ((row==1 && col==1) || (row==1 && col==8) || (row==8 && col==1) || (row==8 && col==8) );
}

bool Move::inXC(){
    bool topRight=((row==2 && col==8) || (row==1 && col==7) || (row==2 && col==7));
    bool topLeft=((row==2 && col==1) || (row==1 && col==2) || (row==2 && col==2));
    bool bottomRight=((row==8 && col==7) || (row==7 && col==8) || (row==7 && col==7));
    bool bottomLeft=((row==8 && col==7) || (row==7 && col==1) || (row==7 && col==2));
    return(topRight || topLeft || bottomRight || bottomLeft);
}
