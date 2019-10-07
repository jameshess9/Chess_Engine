#include <iostream>
#include "Pieces/Piece.h"


#include "Board.h"


using namespace std;

//this takes a chr and subtracts it by the ascii value for 'a' in order to convert the 'a' -> 0 which
//fits in the bounds of our 2d matrix// we then do 7- that value because our 2d matrix holds 0-7 going down
//and the inputted values have 0-7 going upwards
int char_to_x_value(char chr) {
    //turning a char into an integer
    int int_from_ascii = chr - 97;
    //flipping it so 0 -> 7 and vice versa
    int retval = int_from_ascii;

    return retval;
}
//our 2d matrix that holds all the pieces has a range [0->7 going downwards][0->7 going upwards
//people input chess moves as a char followed by a number and the number is what this function is for
//they enter a number 1-8 1 on the bottom and 8 on the top which is the opposite of what ours does
//we add by 1 to get it to the 0-7 scale then do 7 - the value to get the reversed value
int flip_integer(int y_value){
    return 7 - y_value + 1;
}

int main() {
    //initialize the board to play and print it to the player
    Board board;
    board.print_board();

    //the game loop
    while(true){
        bool in_check = board.check_for_checks();
        if(in_check){
            bool check_mate = board.check_for_checkmate();
            if(check_mate){
                break;
            }
        }
        cout << "Enter in 2 pairs" << endl;
        char input_x1, input_x2;
        int input_y1, input_y2;

        cin >> input_x1 >> input_y1 >> input_x2 >> input_y2;


        //these take our y values (ints from 1->8) and converts them into something better for our matrix(7->0)
        int x1 = flip_integer(input_y1);
        int x2 = flip_integer(input_y2);
        //these take our x values (chars from a->h) and converts them into something better for our matrix(h->a)
        int y1 = char_to_x_value(input_x1);
        int y2 = char_to_x_value(input_x2);

        if(x1 == 5 and x2 == 5 and y1 == 5 and y2 == 5){
            break;
        }

        bool test_bool = board.swap_pieces(x1,y1,x2,y2);
        board.print_board();


    }

    return 0;
}
