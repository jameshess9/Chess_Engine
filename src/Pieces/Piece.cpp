//
// Created by Jamie on 9/30/2019.
//

#include "Piece.h"
#include <iostream>

#include <utility>
Piece::Piece(int x_cord, int y_cord, char cur_color, char new_name){
    set_x_location(x_cord);
    set_y_location(y_cord);
    set_color(cur_color);
    set_name(new_name);
    set_pawn_rule(new_name == 'p');
    set_castling_rule(new_name == 'K' or new_name == 'R');
}
Piece::Piece(){
    set_x_location(-1);
    set_y_location(-1);
    set_name('0');
}

void Piece::set_x_location(int x_cord) {
    x_location = x_cord;
}
void Piece::set_y_location(int y_cord) {
    y_location = y_cord;
}
void Piece::set_color(char cur_color){
    color = cur_color;
}
void Piece::set_name(char new_name){
    name = new_name;
}
void Piece::set_pawn_rule(bool updated_rule){
    extra_pawn_move = updated_rule;
}
void Piece::set_castling_rule(bool updated_rule){
    castling_move = updated_rule;
}


