#include <iostream>
#include "Pieces/Piece.h"


#include "Board.h"


using namespace std;

int main() {
    //initialize the board to play and print it to the player
    Board board;
    board.print_board();

    //the game loop
    while(true){
        board.check_for_checks();
        cout << "Enter in 2 pairs" << endl;
        char x1, x2;
        int y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1 == 5 and x2 == 5 and y1 == 5 and y2 == 5){
            break;
        }
        bool test_bool = board.swap_pieces(x1,y1,x2,y2);
        board.print_board();


    }

    return 0;
}