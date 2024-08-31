#include "board.h"
#include "utils.h"
#include <iostream>


using namespace std;

Board::Board(Player p1, Player p2){
    //grid = new int[len*len];

    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            if(j==0 || j==len-1 || i==0 || i==len-1){
                grid[i*len+j] = 100;
            }
            else{
                grid[i*len+j] = 0;
            }
        }
    }
    grid[len*4+4]=1;
    grid[len*4+5]=-1;
    grid[len*5+4]=-1;
    grid[len*5+5]=1;

    players.push_back(p1);
    players.push_back(p2);
}

//Board::Board(Board* b){
//    grid = new int[len*len];
//
//    for(int i=0; i<len; i++){
//        for(int j=0; j<len; j++){
//            grid[i]=b->getCadse(i,j);
//        }
//    }
//
//    players.push_back(b->getPlayer(0));
//    players.push_back(b->getPlayer(1));
//
//    currPlayer = b->getIndexCurrPlayer();
//}

//Board::~Board(){
//    delete [] grid;
//}

bool Board::existingNeighbor(int i, int j){
    int color = players[currPlayer].getColor();
    for(int n = -1; n<2; n++){
        for(int m = -1; m<2; m++){
            if(n!=0 || m!=0){
                if(grid[coord(i+n,j+m)] == -color){
                    return true;
                }
            }
        }
    }
    return false;
}

vector<Move> Board::isFraiming(int i, int j){
    vector<Move> movesToDo;
    int color = players[currPlayer].getColor();
    for(int n = -1; n<2; n++){
        for(int m = -1; m<2; m++){
            if(n!=0 || m!=0){
                if(grid[coord(i+n,j+m)] == -color){
                    int initialN=n;
                    int initialM=m;
                    while(grid[coord(i+n,j+m)] == -color){
                        if (n!=0) {n+=n/abs(n);}
                        if (m!=0) {m+=m/abs(m);}
                    }
                    if(grid[coord(i+n,j+m)] == color){
                        while(n!=initialN||m!=initialM){
                            if (n!=0) {n-=n/abs(n);}
                            if (m!=0) {m-=m/abs(m);}
                            Move moveToDo(n+i, m+j);
                            movesToDo.push_back(moveToDo);
                        }
                    }
                    n=initialN;
                    m=initialM;
                }
            }
        }
    }
    return movesToDo;
}

Board Board::deepCopy(){
    Board newBoard = Board(players[0], players[1]);
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            newBoard.setCase(i, j, grid[coord(i, j)]);
        }
    }
    if(!(currPlayer == newBoard.getIndexCurrPlayer())){
        newBoard.nextPlayer();
    }
    return newBoard;
}

bool Board::validMove(int i, int j){
    if(grid[coord(i,j)]==-1 || grid[coord(i,j)]==1) return false;

     if(!(existingNeighbor(i, j))) return false;

    return isFraiming(i, j).size()!=0;
}

vector<Move> Board::listOfPossibleMoves(){
    vector<Move> listOfMoves;
    for(int i=1; i<len-1; i++){
        for(int j=1; j<len-1; j++){
            if(validMove(i, j)){
                Move possibleMove(i, j);
                listOfMoves.push_back(possibleMove);
            }
        }
    }
    return listOfMoves;
}

void Board::refresh(Move M){
    grid[coord(M.getRow(),M.getCol())]=players[currPlayer].getColor();
    vector<Move> movesToDo=isFraiming(M.getRow(),M.getCol());
    std::vector<Move> ::iterator it = movesToDo.begin();
    for(;it!=movesToDo.end();++it){
        grid[coord(it->getRow(),it->getCol())]*=-1;
    }
}

int Board::getIndexCurrPlayer(){
    return currPlayer;
}

Player Board::getCurrPlayer(){
    return players[currPlayer];
}

Player Board::getOtherPlayer(){
    return players[(currPlayer+1)%2];
}


int Board::countColor(){
    int count=0;
    for(int i=0;i<len*len;i++){
        if (grid[i]==players[currPlayer].getColor())
            count+=1;
    }
    return count;
}

void Board::nextPlayer(){
    if(currPlayer == 0) currPlayer = 1;
    else currPlayer = 0;
}

bool Board::cannotPlay(){
    return (listOfPossibleMoves().size()==0);
}

bool Board::stopGame(){
    bool pass1 = cannotPlay();
    nextPlayer();
    bool pass2 = cannotPlay();
    nextPlayer();
    return( pass1 && pass2);
}

bool Board::winner(){
    int cur = countColor();
    nextPlayer();
    int nex = countColor();
    nextPlayer();
    return(cur>nex && stopGame());
}

bool Board::draw(){
    bool cur = winner();
    nextPlayer();
    bool nex = winner();
    nextPlayer();
    return(( !cur) && (!nex) && stopGame());
}

void Board::printBoard(){
    cout<<endl;
    for (int i=0;i<len; i++){
        cout<<"           ";
        for(int j=0;j<len;j++){
            if ((i==0 && j==0)||(i==len-1 && j==len-1)||(i==0 && j==len-1)||(i==len-1 && j==0))
                cout<<"|"<<"o";
            else if(i==0 || i==len-1)
                cout<<"|"<<j;
            else if(j==0 || j==len-1)
                cout<<"|"<<i;
            else if(grid[coord(i,j)]==0)
                cout<<"|"<<"_";
            else if(grid[coord(i,j)]==1)
                cout<<"|"<<"W";
            else if(grid[coord(i,j)]==-1)
                cout<<"|"<<"B";
        }
        cout<<"|"<<endl;
    }
    cout<<endl;
}


