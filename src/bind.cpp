#include <pybind11/pybind11.h>
#include "AI.h"
#include "board.h"
#include <iostream>



namespace py = pybind11;


//int test(Board position){
//    return position.listOfPossibleMoves().size();
//}

int add(int a, int b){
    return a+b +2;
}

py::list get_grid(Board position){
    py::list grid;
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(!(j==0 || j==9 || i==0 || i==9)){
                grid.append(position.getCase(i,j));
            }
        }
    }
    return grid;
}

py::list getListOfPossibleMoves(Board position){
    py::list list_of_possible_moves;
    int size = position.listOfPossibleMoves().size();
    for(int i=0; i<size; i++){
        list_of_possible_moves.append(position.listOfPossibleMoves()[i]);
    }
    return list_of_possible_moves;
}

PYBIND11_MODULE(bindOthello, m) {
    m.def("add", &add);
    m.def("get_grid", &get_grid, "get the grid of the board");
    m.def("minimax",&minimax, "algorithme alpha beta");
    m.def("random_move",& random_move,"generate a random move");
    m.def("getListOfPossibleMoves",&getListOfPossibleMoves,"list python of possible moves");


    py::class_<Player>(m, "Player")
            .def(py::init<std::string &, bool &,std::string &>(),py::arg("h") = "white", py::arg("hp") = true, py::arg("diff") = "h")
            .def("getDifficulty", &Player::getDifficulty)
            .def("getColor", &Player::getColor)
            .def("isHuman", &Player::isHuman);

    py::class_<Move>(m, "Move")
            .def(py::init<int  &, int &>())
            .def("getCol", &Move::getCol)
            .def("getRow", &Move::getRow)
            .def("setCol", &Move::setCol)
            .def("setRow", &Move::setRow);


    py::class_<Board>(m, "Board")
            .def(py::init<Player &, Player &>())
            .def("stopGame", &Board::stopGame)
            .def("cannotPlay", &Board::cannotPlay)
            .def("getCurrPlayer", &Board::getCurrPlayer)
            .def("refresh", &Board::refresh)
            .def("getCase", &Board::getCase)
            .def("nextPlayer", &Board::nextPlayer)
            .def("deepCopy", &Board::deepCopy)
            .def("countColor", &Board::countColor)
            .def("winner", &Board::winner)
            .def("getOtherPlayer", &Board::getOtherPlayer)
            .def("listOfPossibleMoves", &Board::listOfPossibleMoves);
}
