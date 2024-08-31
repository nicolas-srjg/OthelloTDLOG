cmake_minimum_required(VERSION 2.6)

project(OthelloAI)

add_executable(othelloai
  src/main.cpp
  src/player.cpp src/player.h
  src/board.cpp src/board.h
  src/utils.cpp src/utils.h
  src/game.h src/game.cpp
  src/tree.h src/tree.cpp
  src/AI.h AI.cpp
)


add_subdirectory(pybind11)
pybind11_add_module(pyothelloai
    src/bind.cpp src/bind.h
    src/player.cpp src/player.h
    board.cpp board.h
    src/utils.cpp src/utils.h
    src/game.h src/game.cpp
    src/tree.h src/tree.cpp
    src/AI.h src/AI.cpp
)
