cmake_minimum_required(VERSION 2.6)

project(ProjetOthello)

add_executable(ProjetOthello
  main.cpp
  player.cpp player.h
  board.cpp board.h
  utils.cpp utils.h
  game.h game.cpp
  tree.h tree.cpp
  AI.h AI.cpp
)

add_subdirectory(pybind11)
pybind11_add_module(bindOthello
    bind.cpp bind.h
    player.cpp player.h
    board.cpp board.h
    utils.cpp utils.h
    game.h game.cpp
    tree.h tree.cpp
    AI.h AI.cpp
)
