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
    char name{};
    int x_location{};
    int y_location{};
    char color{};    //w for white b for black e for empty
    bool extra_pawn_move{};
    bool castling_move{}; //when checking if castling is valid it will look for a king and rook both so we can combine it into 1 variable

    string moves;
public:
    Piece(int x_board_location, int y_board_location, char color, char name);
    Piece();

    void set_x_location(int x_cord);
    void set_y_location(int y_cord);
    void set_color(char cur_color);
    void set_name(char new_name);
    void set_pawn_rule(bool updated_rule);
    void set_castling_rule(bool updated_rule);

    int get_x_location() {return x_location;}
    int get_y_location() {return y_location;}
    char get_color() {return color;}
    bool get_pawn_rule() {return extra_pawn_move;}
    bool get_castling_rule() {return castling_move;}

    char get_name() {return name;}

};


#endif //CHESS_ENGINE_PIECE_H
