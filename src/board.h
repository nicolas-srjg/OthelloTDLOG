#pragma once

#include "player.h"
#include <iostream>

using namespace std;


class Board{
    // length of the board
    const int len = 10;

    // table of all the cases
    int grid[100];

    // list of the 2 players
    vector<Player> players;

    // index of the current player in players
    int currPlayer = 0;
public:
    // constructor
    Board(Player p1,Player p2);

    //constructor par copie (deepCopy)
    //Board(Board* b);

    //destructor
    //~Board();

    void setCase(int i, int j){ grid[coord(i, j)]=players[currPlayer].getColor(); }

    void setCase(int i, int j, int color){ grid[coord(i, j)] = color; }

    int getCase(int i, int j){ return grid[coord(i, j)]; }

    Player getPlayer(int i){ return players[i]; }

    int coord(int i, int j){ return i*len+j; }

    //return true if a piece has a neighbour of a different color
    bool existingNeighbor(int i, int j);

    //return a vector of pieces to turn for a given move
    vector<Move> isFraiming(int i, int j);

    // deep copy of board
    Board deepCopy();

    //return true if the move if valid for the current player
    bool validMove(int i, int j);

    //return list of possible moves
    vector<Move> listOfPossibleMoves();

    //refresh the board after a move
    void refresh(Move M);

    //return the index of current player
    int getIndexCurrPlayer();

    //return the current player
    Player getCurrPlayer();

    //return the other player
    Player getOtherPlayer();

    //Count the number of pieces of a player
    int countColor();

    //Change the  player
    void nextPlayer();

    //return true if player p cannot play
    bool cannotPlay();

    //stop the game when no one can play
    bool stopGame();

    //return true if p wins
    bool winner();

    //return true if draw
    bool draw();

    // display in the terminal the board
    void printBoard();
};
