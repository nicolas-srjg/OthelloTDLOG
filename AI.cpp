#include <iostream>
#include "board.h"
#include "math.h"
#include "AI.h"

using namespace std;


float minimax(Board position, int depth, float alpha, float beta, Player player_to_maximize, int max_depth, Move& move_to_do){
    if(depth == 0 || position.cannotPlay()){
        return heuristic(position, player_to_maximize);
    }

    //put best moves ahead
    vector<Move> sortedMove = sortMove(position.listOfPossibleMoves());//
    // nbr of moves we will test
    int size = sortedMove.size();

    if(position.getCurrPlayer().getColor() == player_to_maximize.getColor()){ // si le joueur actuel est a maximiser
        float max_eval=-INFINITY;

        // index of the best move
        int index_move_to_do = 0;

        for(int move=0; move<size; move++){
            Board new_pos_board = position;
            new_pos_board.refresh(sortedMove[move]);
            new_pos_board.nextPlayer();
            float eval = minimax(new_pos_board, depth - 1, alpha, beta, player_to_maximize, max_depth, move_to_do);
            if(eval>max_eval){
                max_eval=eval;
                index_move_to_do = move;
            }
            alpha = max(alpha, eval);
            if (beta <= alpha){
                break;
            }
        }
        if(max_depth==depth)
            move_to_do = sortedMove[index_move_to_do];
        return max_eval;
    }
    else{
        float min_eval = INFINITY;

        for(int move=0; move<size; move++){
            Board new_pos_board = position;
            new_pos_board.refresh(sortedMove[move]);
            new_pos_board.nextPlayer();
            float eval = minimax(new_pos_board, depth - 1, alpha, beta, player_to_maximize, max_depth, move_to_do);
            min_eval = min(min_eval, eval);
            beta = min(beta, eval);
            if ( beta<= alpha){
                break;
            }
        }
        return min_eval;
    }
}

float minimax_sans_alpha_beta(Board position, int depth, Player player_to_maximize, int max_depth, Move& move_to_do){
    if(depth == 0 || position.cannotPlay()){
        return heuristic(position, player_to_maximize);
    }

    //put best moves ahead
    vector<Move> sortedMove = position.listOfPossibleMoves();//
    // nbr of moves we will test
    int size = sortedMove.size();

    if(position.getCurrPlayer().getColor() == player_to_maximize.getColor()){ // si le joueur actuel est a maximiser
        float max_eval=-INFINITY;

        // index of the best move
        int index_move_to_do = 0;

        for(int move=0; move<size; move++){
            Board new_pos_board = position;
            new_pos_board.refresh(sortedMove[move]);
            new_pos_board.nextPlayer();
            float eval = minimax_sans_alpha_beta(new_pos_board, depth - 1, player_to_maximize, max_depth, move_to_do);
            if(eval>max_eval){
                max_eval=eval;
                index_move_to_do = move;
            }
        }
        if(max_depth==depth)
            move_to_do = sortedMove[index_move_to_do];
        return max_eval;
    }
    else{
        float min_eval = INFINITY;

        for(int move=0; move<size; move++){
            Board new_pos_board = position;
            new_pos_board.refresh(sortedMove[move]);
            new_pos_board.nextPlayer();
            float eval = minimax_sans_alpha_beta(new_pos_board, depth - 1, player_to_maximize, max_depth, move_to_do);
            min_eval = min(min_eval, eval);
        }
        return min_eval;
    }
}

float heuristic(Board position, Player player_to_maximize){
    float diff_coin, mobility, strength=0;

    if (position.getCurrPlayer().getColor()!=player_to_maximize.getColor())
        position.nextPlayer();

    //difference of coins
    int coin_max_player = position.countColor();
    position.nextPlayer();
    int coin_min_player = position.countColor();
    position.nextPlayer();
    diff_coin = 100*(coin_max_player-coin_min_player)/(coin_max_player+coin_min_player);

    //mobility
    int numb_moves_max_player = position.listOfPossibleMoves().size();
    position.nextPlayer();
    int numb_moves_min_player = position.countColor();
    position.nextPlayer();
    if ( numb_moves_max_player + numb_moves_min_player != 0)
        mobility =100 * (numb_moves_max_player - numb_moves_min_player) / (numb_moves_max_player + numb_moves_min_player);
    else
        mobility = 0;

    //strength
    int val_square[8][8]={
        {1000, -150, 30, 10, 10, 30, -150, 1000},
        {-150, -250, 0 , 0 , 0 , 0 , -250, -150},
        { 30 ,  0  , 1 , 2 , 2 , 1 ,  0  ,  30 },
        { 10 ,  0  , 2 , 16, 16, 2 ,  0  ,  10 },
        { 10 ,  0  , 2 , 16, 16, 2 ,  0  ,  10 },
        { 30 ,  0  , 1 , 2 , 2 , 1 ,  0  ,  30 },
        {-150, -250, 0 , 0 , 0 , 0 , -250, -150},
        {1000, -150, 30, 10, 10, 30, -150, 1000}
    };

    int dir1[3][2]={{0,1},{1,1},{1,0}};
    int dir2[3][2]={{0,-1},{1,-1},{1,0}};

    int playerMax = position.getCurrPlayer().getColor();
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            if (position.getCase(i+1,j+1)==playerMax)
                strength += val_square[i][j];
            if (position.getCase(i+1,j+1)==-playerMax)
                strength -= val_square[i][j];
        }
    }

    for(int i=0; i<3;i++){
        if (position.getCase(1,1)==playerMax && position.getCase(1+dir1[i][0],1+dir1[i][1])==playerMax)
            strength+=250;
        if (position.getCase(8,8)==playerMax && position.getCase(8-dir1[i][0],8-dir1[i][1])==playerMax)
            strength+=250;
        if (position.getCase(1,8)==playerMax && position.getCase(1+dir2[i][0],8+dir2[i][1])==playerMax)
            strength+=250;
        if (position.getCase(8,1)==playerMax && position.getCase(8-dir2[i][0],1-dir2[i][1])==playerMax)
            strength+=250;
    }


    if(player_to_maximize.getDifficulty()=="e")
        return mobility + diff_coin ;
    else
        return 1.5*mobility + diff_coin + 0.8*strength;
}


Move random_move(Board position){
    int move = rand() % position.listOfPossibleMoves().size();
    return position.listOfPossibleMoves()[move];
}

bool test_sort(){
    for(int k=0; k<100000;k++){
        //random construction
        vector<Move> V;
        int rand_size=rand()%15+1;
        for(int l=0;l<rand_size;l++){
            Move m(rand()%8+1,rand()%8+1);
            if(!(m.inVector(V)))
                V.push_back(m);
            else
                l-=1;
        }
        vector<Move> sortV = sortMove(V);
        if (sortV.size()!=rand_size)
            return false;
        for(int i=0; i<V.size()-1;i++){
            int a=0,b=0;
            if(sortV[i].inCorner())
                a=1;
            if(sortV[i+1].inCorner())
                b=1;
            if(sortV[i].inXC())
                a=-1;
            if(sortV[i+1].inXC())
                b=-1;
            if(a<b)
                return false;
        }
    }
    return true;
}

std::vector<Move> sortMove(vector<Move> possibilities){
    Move stop(0,0);
    for(int i=0; i<possibilities.size();i++){
        if(possibilities[i].inCorner()){
            possibilities.insert(possibilities.begin(),possibilities[i]);
            possibilities.erase(possibilities.begin()+i+1);
        }
        else{
            if (possibilities[i].inXC()){
                if(stop==possibilities[i])
                    break;
                if(stop.getRow()==0 && stop.getCol()==0)
                    stop=possibilities[i];
                possibilities.push_back(possibilities[i]);
                possibilities.erase(possibilities.begin()+i);
                i-=1;

            }
        }
    }
    return possibilities;
}

//vector<Move> permute(vector<Move> possibilities){
//    vector<int> order, disordered;
//    vector<Move> possPermut;
//    for(int i=0;i<possibilities.size();i++){
//        order.push_back(i);
//    }
//    while (not (order.empty())){
//        int k = rand()%order.size();
//        disordered.push_back(order[rand()%order.size()]);
//        order.erase(order.begin()+k);
//    }
//    for(int j=0;j<possibilities.size();j++){
//        possPermut.push_back(possibilities[order[j]]);
//    }
//    return possPermut;
//}
