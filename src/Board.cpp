//
// Created by Jamie on 9/30/2019.
//

#include <iostream>
#include "Board.h"


using namespace std;

Board::Board(){
    //make a new piece array thats blank

    for(int i = 0; i < max_x; i++){
        for(int j = 0; j < max_y; j++){
            //blacks major pieces
            Piece temp(i,j,'e','0');
            piece_array[i][j] = temp;
        }
    }
    current_turn = 'w'; // always white's turn first
    init_board();
}

void Board::swap_turn() {
    current_turn = !current_turn;
}
void Board::init_board() {


    //w for white b for black ks for kingside qs for queenside
    //i is == to the row and j is == to the column
    //so basically if its row 0 thats black major pieces and row 7 is whites major pieces
    //row 1 is blacks pawns and row 6 is whites pawns
    //all rows in between will be filled with empty pieces color == e

    //we create all the pieces then add them to piece_array
    Piece w_qs_Rook(7,0,'w','R');
    piece_array[7][0] = w_qs_Rook;
    Piece w_qs_Knight(7,1,'w','N');
    piece_array[7][1] = w_qs_Knight;
    Piece w_qs_Bishop(7,2,'w','B');
    piece_array[7][2] = w_qs_Bishop;
    Piece w_Queen(7,3,'w','Q');
    piece_array[7][3] = w_Queen;
    Piece w_King(7,4,'w','K');
    piece_array[7][4] = w_King;
    Piece w_ks_Bishop(7,5,'w','B');
    piece_array[7][5] = w_ks_Bishop;
    Piece w_ks_Knight(7,6,'w','N');
    piece_array[7][6] = w_ks_Knight;
    Piece w_ks_Rook(7,7,'w','R');
    piece_array[7][7] = w_ks_Rook;

    Piece b_qs_Rook(0,0,'b','R');
    piece_array[0][0] = b_qs_Rook;
    Piece b_qs_Knight(0,1,'b','N');
    piece_array[0][1] = b_qs_Knight;
    Piece b_qs_Bishop(0,2,'b','B');
    piece_array[0][2] = b_qs_Bishop;
    Piece b_Queen(0,3,'b','Q');
    piece_array[0][3] = b_Queen;
    Piece b_King(0,4,'b','K');
    piece_array[0][4] = b_King;
    Piece b_ks_Bishop(0,5,'b','B');
    piece_array[0][5] = b_ks_Bishop;
    Piece b_ks_Knight(0,6,'b','N');
    piece_array[0][6] = b_ks_Knight;
    Piece b_ks_Rook(0,7,'b','R');
    piece_array[0][7] = b_ks_Rook;

    //prev_moved_piece needs to be initialized to something and this knight will never be able to check the king
    //on the first move. We must initialize it because looking for checks is called before the first swapping
    //of pieces happens
    prev_moved_piece = b_ks_Knight;
    //set the king locations
    white_king = w_King;
    black_king = b_King;

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 8; j++){
            if(i == 0){
                Piece pawn(i+1,j,'b','p');
                piece_array[i+1][j] = pawn;
            }
            if(i == 1){
                Piece pawn(i+5,j,'w','p');
                piece_array[i+5][j] = pawn;
            }
        }
    }
}

void Board::print_board(){
    for(int i = 0; i < max_x; i++){
        for(int j = 0; j < max_y; j++){
        Piece temp = get_piece(i,j);
        char temp2 = temp.get_name();
        char temp_color = temp.get_color();
        if(temp_color == 'w' or temp_color == 'b'){
            cout << temp_color <<temp2 << " ";
        }
        else{
            cout << temp2 << "  ";
        }

    }
    cout << endl;
}
}
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
//function that switches the pieces on the chess board - main part of the functionality
bool Board::swap_pieces(char x1_input, int y1_input, char x2_input, int y2_input) {
    // our input values are going to be like d2 d4 where the letters correspond to our y values
    // and our ints correspond to our x values.
    //these take our y values (ints from 1->8) and converts them into something better for our matrix(7->0)
    int x1 = flip_integer(y1_input);
    int x2 = flip_integer(y2_input);
    //these take our x values (chars from a->h) and converts them into something better for our matrix(h->a)
    int y1 = char_to_x_value(x1_input);
    int y2 = char_to_x_value(x2_input);
    //note we had to flip these values because chess notation goes low on the board on the left has low values and
    //our 2d matrix has low on the board on the right having higher values

    //cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;

    //first make sure either piece is not out of bounds
    if(x1 < 0 or y1 < 0 or x2 < 0 or y2 < 0 or x1 >= max_x or x2 >= max_x or y1 >= max_y or y2 >= max_y){
        cout << "Out of bounds" << endl;
        return false;
    }

    Piece first_piece = get_piece(x1,y1);
    Piece second_piece = get_piece(x2,y2);

    //we now have to make sure that our initial piece is a piece that can move and not an empty space
    if(first_piece.get_name() == '0'){
        cout << "You can't move a space" << endl;
        return false;
    }

    //the first thing we have to make sure is that piece 1 can move to piece 2 as a valid move
    bool validMove = valid_move(first_piece,second_piece);

    /*
     * Have to implement something here to deal with the fact that pawns capture in different directions
     * Also have to implement something to see if this move makes you go from being in check to not being in check
     * creating a new board copying everything over making the move and then checking for checks seems too costly
     * issue is that if the second piece is a piece we clear it out and then swap with the cleared piece
     * can create a temporary piece equal to the piece that we cleared out and undo swapping if still in check
     */

    //we store this temporary piece in case the baord is still in check after the move therefore making it an invalid move
    Piece temporary_piece = second_piece;

    if(validMove){


        //if the second piece is a real piece
        if(second_piece.get_name() != '0'){
            //if they are the same color return false to being able to swap
            if(first_piece.get_color() == second_piece.get_color()){
                cout << "You can't capture a piece of the same color" << endl;
                return false;
            }
            //else its the opposite color which you can capture therefore just set second one to a blank piece
            else{
                int temp_x = second_piece.get_x_location();
                int temp_y = second_piece.get_y_location();
                Piece temp_piece(temp_x,temp_y,'e','0');
                second_piece = temp_piece;
            }
        }
        //we dont have to move the location in the pieces just the information insides of it
        char temp_name = first_piece.get_name();
        char temp_color = first_piece.get_color();


        //first we change the values into the pieces as to the new locations
        first_piece.set_color(second_piece.get_color());
        first_piece.set_name(second_piece.get_name());
        first_piece.set_pawn_rule(false); //this will make it so if a pawn moves once it cant move twice
        first_piece.set_castling_rule(false); //same thing but for castling with kings and rooks

        second_piece.set_name(temp_name);
        second_piece.set_color(temp_color);

        //push updated pieces back into array
        piece_array[first_piece.get_x_location()][first_piece.get_y_location()] = first_piece;
        piece_array[second_piece.get_x_location()][second_piece.get_y_location()] = second_piece;
        //second_piece is the piece that was just moved
        //the if statement is for if the board is in check
        //we will want to recall check_for_checks given the same piece in storage after black makes its move
        //so we do not want to alter prev_moved_piece if the board is in check
        if(!in_check) {
            prev_moved_piece = second_piece;
        }
        swap_turn();
    }
    //here is where we will deal with the case of board being in check
    if(in_check){
        //so the board was in check before this move so if we have no checks now we are good
        //white makes a move to put black in check -> new iteration of while loop
        //current_turn = black black then makes a move which will make current_turn = white
        //issue is that check_for_checks looks for the prev piece -> resolved
        //so prev_moved_piece will be = to the white piece that put black in check
        //prev_moved piece is white and the current turn is white which seems like it would be correct
        //but in most cases you will be checking for checks on the wrong turn so check_for_checks
        //initially swaps turns so we have to swap turns first here to offset that;
        /*bugs:
         * rules will be changed and not changed back
         * if we make a move that doesnt put us out of check it prints that we must make another move but board
         * print shows the move
         */
        swap_turn();
        bool still_in_check = check_for_checks();
        if(!still_in_check){
            //not in check anymore we are good
            //swap back to the correct turn and continue the game
            swap_turn();
            in_check = false;
            prev_moved_piece = second_piece;

        }
        else{
            //this is an issue our previous move does not work must "reset" the move
            //we already swapped the turn once so its already swapped back now we just need to reset the pieces
            //currently all of first pieces info is stored  in second piece and second piece is stored in temporary_piece
            first_piece.set_color(second_piece.get_color());
            first_piece.set_name(second_piece.get_name());
            //first piece is set back time to set back the second piece
            //important here to make sure we set second_pieces values to temps values
            second_piece = temporary_piece;

            cout << "You must make a move to get out of check" << endl;
            //push the pieces back to the array
            piece_array[first_piece.get_x_location()][first_piece.get_y_location()] = first_piece;
            piece_array[second_piece.get_x_location()][second_piece.get_y_location()] = second_piece;
            return false;
        }

    }
    return validMove;

}

bool Board::valid_move(Piece initial_location, Piece destination_location) {
    //only the person who's move it is can move a piece
    //current turn = true means it is whites turn
    if(current_turn){
        if(initial_location.get_color() == 'b'){
            cout << "It's not your turn" << endl;
            return false;
        }
    }
    else{
        if(initial_location.get_color() == 'w'){
            cout << "It's not your turn" << endl;
            return false;
        }
    }

    //get location as 2 ints per piece = 4 total
    int initial_x = initial_location.get_x_location();
    int destination_x = destination_location.get_x_location();

    int initial_y = initial_location.get_y_location();
    int destination_y = destination_location.get_y_location();
    bool retVal = false;
    //moving a pawn
    if(initial_location.get_name() == 'p'){
        //so if its a pawn it can move one forward
        //this is movement in the x direction minus 1 therefore initial x == destination x + 1
        if(initial_location.get_color() == 'w') {
            bool moveForwardOne = (initial_x == destination_x + 1) and (initial_y == destination_y);
            bool moveForwardTwo = false;
            if(initial_location.get_pawn_rule()){
                moveForwardTwo = (initial_x == destination_x + 2) and (initial_y == destination_y);
            }
            if (moveForwardOne or moveForwardTwo) {
                return true;
            }
        }
        else{
            bool moveForwardOne = (initial_x == destination_x - 1) and (initial_y == destination_y);
            bool moveForwardTwo = false;
            if (initial_location.get_pawn_rule()) {
                moveForwardTwo = (initial_x == destination_x - 2) and (initial_y == destination_y);
            }
            if (moveForwardOne or moveForwardTwo) {
                return true;
            }
        }
    }
        //moving a knight
    else if(initial_location.get_name() == 'N'){
        //moves in a L direction -> 8 possible locations
        //first loop will run in the -2 direction and +2 direction in each way
        //the second loop will then run in the -1 and +1 direction in each way
        //the first if statement handles up 2 and down 2 and then left 1 and right one covering the first 4 locations
        //the else if statement handles the cases were you go left 2 and right 2 then up 1 and down 1
        for(int i = -2; i <5;i = i + 4){
            for(int j = -1; j < 2; j = j + 2){
                if((initial_x == (destination_x + i)) and (initial_y == (destination_y + j))){
                    retVal = true;
                }
                else if((initial_x == destination_x + j) and (initial_y == destination_y + i)){
                    retVal = true;
                }
            }
        }
    }
        //bishop movement
    else if(initial_location.get_name() == 'B'){
        //checks and see if
        for(int i = 1; i < 9; i++){
            //this code goes in a diagonal by always adding x and y by i or subtracting x and y by i
            //checks both diagonals max distance being 8
            //this code will be re used for the queen might mo  ve to helper function
            if((initial_x == destination_x + i) and (initial_y == destination_y + i)){
                retVal = true;
            }
            else if((initial_x == destination_x -i) and (initial_y == destination_y - i)){
                retVal = true;
            }
            else if((initial_x == destination_x + i) and (initial_y == destination_y - i)){
                retVal = true;
            }
            else if((initial_x == destination_x -i) and (initial_y == destination_y + i)){
                retVal = true;
            }
        }
    }
    else if(initial_location.get_name() == 'R'){
        for(int i = 1; i < 9; i++){
            if((initial_x == destination_x + i) and (initial_y == destination_y)){
                retVal = true;
            }
            else if((initial_x == destination_x) and (initial_y == destination_y + i)){
                retVal = true;
            }
            else if((initial_x == destination_x - i) and (initial_y == destination_y)){
                retVal = true;
            }
            else if((initial_x == destination_x) and (initial_y == destination_y - i)){
                retVal = true;
            }

        }
    }
        //the queen is just a copy of the bishop and rook combined
    else if(initial_location.get_name() == 'Q'){
        for(int i = 1; i < 9; i++){
            //this is the rook behavior
            if((initial_x == destination_x + i) and (initial_y == destination_y)){
                retVal = true;
            }
            else if((initial_x == destination_x) and (initial_y == destination_y + i)){
                retVal = true;
            }
            else if((initial_x == destination_x - i) and (initial_y == destination_y)){
                retVal = true;
            }
            else if((initial_x == destination_x) and (initial_y == destination_y - i)){
                retVal = true;
            }
                //this is the bishop behavior
            else if((initial_x == destination_x + i) and (initial_y == destination_y + i)){
                retVal = true;
            }
            else if((initial_x == destination_x -i) and (initial_y == destination_y - i)){
                retVal = true;
            }
            else if((initial_x == destination_x + i) and (initial_y == destination_y - i)){
                retVal = true;
            }
            else if((initial_x == destination_x -i) and (initial_y == destination_y + i)){
                retVal = true;
            }
        }
    }
        //this piece can move one up down left right or any of the 4 diagonals
        //x+1,y     x-1,y    x,y-1   x,y+1  x+1,y+1   x-1,y-1   x-1,y+1     x+1,y-1
    else if(initial_location.get_name() == 'K'){

        if((initial_x == destination_x + 1) and (initial_y == destination_y)){
            retVal = true;
        }
        else if((initial_x == destination_x - 1) and (initial_y == destination_y)){
            retVal = true;
        }
        else if((initial_x == destination_x) and (initial_y == destination_y - 1)){
            retVal = true;
        }
        else if((initial_x == destination_x) and (initial_y == destination_y + 1)){
            retVal = true;
        }
        else if((initial_x == destination_x + 1) and (initial_y == destination_y + 1)){
            retVal = true;
        }
        else if((initial_x == destination_x - 1) and (initial_y == destination_y - 1)){
            retVal = true;
        }
        else if((initial_x == destination_x + 1) and (initial_y == destination_y - 1)){
            retVal = true;
        }
        else if((initial_x == destination_x - 1) and (initial_y == destination_y + 1)){
            retVal = true;
        }
    }
    //rejected by if statement
    //or its an empty space and retVal was initialized to false so just return retVal

    //if(!retVal){
        //cout << "Invalid Move" << endl;
    //}
    //else{
        //cout << "Valid Move" << endl;
    //}
    return retVal;
}
bool Board::check_for_checks() {
    //so this function is going to be called at the beginning of a turn to look and see if there are any checks
    //in the given position. We first need to find out whos turn it is, then we must find where their king is
    //and then we must find if any of the pieces have a valid move to the king

    //returns true if in check returns false otherwise

    //attempted implementing this without scanning through all the pieces but kept getting bugs
    //we must scan through all of the pieces and make sure that none of them have a valid move on the king

    //1. We must find out which king is in danger
    //2. For every piece in piece_array if that piece is equal to the opposite color see if it has a valid move
    //3. if any of the pieces have a check return true;

    //set king equal to the current players king
    Piece king;
    if(current_turn){
        king = white_king;
    }
    else{
        king = black_king;
    }
    //this is to prepare for our for loop we will be checking to see if the opposite player can make moves
    //and with how our valid_move function is implemented we must temporarily switch to the other players move
    swap_turn();
    //hard coded 64 could change
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(piece_array[i][j].get_color() != king.get_color()){
                //so these pieces are threats to the king must check for every valid move
                if(valid_move(piece_array[i][j],king)){
                    //this piece can attack the king
                    //swap back turns and return false;
                    cout << "In check" << endl;
                    swap_turn();
                    in_check = true;
                    return true;
                }
            }
        }
    }
    //no pieces can attack the king
    swap_turn();
    in_check = false;
    return false;

}
