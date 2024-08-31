#pragma once

#include<vector>

class Move{
    int row;
    int col;
public:
    Move(int i, int j);

    int getCol();
    int getRow();
    void setCol(int j);
    void setRow(int i);
    bool operator==(Move a);
    bool inVector(std::vector<Move> V);
    bool inCorner();
    bool inXC();
};

