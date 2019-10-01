//
// Created by Jamie on 9/30/2019.
//

#include "Piece.h"
Piece::Piece(int x_cord, int y_cord, bool cur_color){
    set_x_location(x_cord);
    set_y_location(y_cord);
    set_color(cur_color);
}

void Piece::set_x_location(int x_cord) {
    x_location = x_cord;
}
void Piece::set_y_location(int y_cord) {
    y_location = y_cord;
}
void Piece::set_color(bool cur_color){
    color = cur_color;
}
