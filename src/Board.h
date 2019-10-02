//
// Created by Jamie on 9/30/2019.
//

#ifndef CHESS_ENGINE_BOARD_H
#define CHESS_ENGINE_BOARD_H


#include "Pieces/Piece.h"

class Board {
private:
    //max size of our chess board
    static int const max_x{8};
    static int const max_y{8};


public:
    Piece piece_array[8][8];

    Board(); //as of right now we will always create a board object and then call init on it to set it to default order

    void init_board();
    void print_board();
    //returns true if successfully swapped returns false if move does not follow game rules
    bool swap_pieces(int x1, int y1, int x2, int y2);
    bool valid_move(Piece initial_location, Piece destination_location);

    Piece get_piece(int x,int y){return piece_array[x][y];}


};


#endif //CHESS_ENGINE_BOARD_H
