#include "game.h"
#include "AI.h"
#include "math.h"

void play(Board B){
    while(!(B.stopGame())){
        if ( !(B.cannotPlay())){
            B.printBoard();
            cout<<B.getCurrPlayer()<<"'s turn: ";
            if(B.getCurrPlayer().isHuman())
                B.refresh(B.getCurrPlayer().chooseMove(B.listOfPossibleMoves()));
            else{
                if (B.getCurrPlayer().getDifficulty()=="r")//random
                    B.refresh(random_move(B));
                else{
                    int minimax_depth;
                    if (B.getCurrPlayer().getDifficulty()=="e" )//easy
                        minimax_depth=3;
                    else
                        minimax_depth=7;
                    Move move_to_do = Move(1,1);
                    minimax_sans_alpha_beta(B, minimax_depth, B.getCurrPlayer(),  minimax_depth, move_to_do);
                    B.refresh(move_to_do);
                }
            }
        }
        else
            cout<<"player "<<B.getCurrPlayer()<<"cannot play"<<endl;
        B.nextPlayer();
    }

    if (B.draw()){
        B.printBoard();
        B.nextPlayer();
        cout<<"the game end with a draw"<<endl;
    }
    else if (B.winner()){
        B.printBoard();
        B.nextPlayer();
        cout<<"    "<<B.getCurrPlayer()<< " has : " <<B.countColor()<<" pieces"<<endl;
        B.nextPlayer();
        cout<<"    "<<B.getCurrPlayer()<< " has : " <<B.countColor()<<" pieces"<<endl;
        cout<<"The winner is "<<B.getCurrPlayer()<<endl;
    }
    else {
        B.printBoard();
        B.nextPlayer();
        cout<<"    "<<B.getCurrPlayer()<< " has : " <<B.countColor()<<" pieces"<<endl;
        B.nextPlayer();
        cout<<"    "<<B.getCurrPlayer()<< " has : " <<B.countColor()<<" pieces"<<endl;
        cout<<"The winner is "<<B.getOtherPlayer()<<endl;
    }

}

float benchmark(int nb_games, std::string competitor){
    //return the percentage of winning against random

    //Initialization
    Player p1("black",false,"h");
    Player p2("white",false,"h");
    double percentage=0;

    //loop of nb_games games
    for(int i=0; i<nb_games; i++){
        Board B(p1,p2);
        while( !(B.stopGame())){
            if ( !(B.cannotPlay())){
                if(B.getCurrPlayer().getDifficulty()=="r")
                    B.refresh(random_move(B));
                else{
                    int minimax_depth;
                    if (B.getCurrPlayer().getDifficulty()=="e" )//easy
                        minimax_depth=2;
                    else
                        minimax_depth=4;
                    Move move_to_do = Move(1,1);
                    minimax(B, minimax_depth, -INFINITY, INFINITY, B.getCurrPlayer(),  minimax_depth, move_to_do);
                    vector<Move> list_of_move = {move_to_do};
                    B.refresh(B.getCurrPlayer().chooseMove(list_of_move));
                }
            }
            B.nextPlayer();
        }
        if (B.getCurrPlayer().getDifficulty()==competitor)
            B.nextPlayer();
        if (B.winner() )
            percentage+=1.;
    }
    return percentage/double(nb_games);
}
