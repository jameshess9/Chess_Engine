cmake_minimum_required(VERSION 3.15)
project(Chess_Engine)

set(CMAKE_CXX_STANDARD 14)

add_executable(Chess_Engine src/main.cpp src/Board.cpp src/Board.h src/Pieces/Piece.cpp src/Pieces/Piece.h src/Pieces/Knight.cpp src/Pieces/Knight.h src/Pieces/Bishop.cpp src/Pieces/Bishop.h src/Pieces/King.cpp src/Pieces/King.h src/Pieces/Queen.cpp src/Pieces/Queen.h src/Pieces/Rook.cpp src/Pieces/Rook.h src/Pieces/Pawn.cpp src/Pieces/Pawn.h)