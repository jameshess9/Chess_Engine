#include <iostream>
#include "Pieces/Piece.h"

#include "Pieces/Bishop.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Pawn.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"

using namespace std;

int main() {
    int x = 0;
    int y = 0;
    bool cur_color = true;
    Piece wPiece(x, y, cur_color);
    Pawn wKnight(x,y,cur_color);


    int test1 = wPiece.get_x_location();
    int test2 = wPiece.get_y_location();
    bool test3 = wPiece.get_color();

    int test4 = wKnight.get_x_location();
    int test5 = wKnight.get_y_location();
    bool test6 = wKnight.get_color();

    cout << test1 << " " << test2 << " " << test3 << endl;
    cout << test4 << " " << test5 << " " << test6 << endl;

    return 0;
}