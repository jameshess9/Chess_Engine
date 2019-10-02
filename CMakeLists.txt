cmake_minimum_required(VERSION 3.15)
project(Chess_Engine)

set(CMAKE_CXX_STANDARD 14)

add_executable(Chess_Engine src/main.cpp src/Board.cpp src/Board.h src/Pieces/Piece.cpp src/Pieces/Piece.h)