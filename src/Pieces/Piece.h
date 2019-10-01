//
// Created by Jamie on 9/30/2019.
// This is the superclass that holds all pieces
//
#include <string>
#ifndef CHESS_ENGINE_PIECE_H
#define CHESS_ENGINE_PIECE_H

using namespace std;


class Piece {
private:
    int x_location;
    int y_location;
    bool color;    //true if white false is black
public:
    Piece(int x_board_location, int y_board_location, bool color);

    void set_x_location(int x_cord);
    void set_y_location(int y_cord);
    void set_color(bool cur_color);

    int get_x_location() {return x_location;}
    int get_y_location() {return y_location;}
    bool get_color() {return color;}
};


#endif //CHESS_ENGINE_PIECE_H
