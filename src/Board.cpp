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
    checkmate = false;
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

//function that switches the pieces on the chess board - main part of the functionality
bool Board::swap_pieces(int x1, int y1, int x2, int y2) {

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
        //cout << "You can't move a space" << endl;
        return false;
    }

    //the first thing we have to make sure is that piece 1 can move to piece 2 as a valid move
    bool validMove = valid_move(first_piece,second_piece);
    //here we can add a call to a helper function to make sure the pieces aren't jumping over each other
    if(validMove){
        validMove = check_for_pieces_inbetween(first_piece,second_piece);
        cout << validMove << endl;
    }
    /*
     * Have to implement something here to deal with the fact that pawns capture in different directions
     * Also have to implement something to see if this move makes you go from being in check to not being in check
     * creating a new board copying everything over making the move and then checking for checks seems too costly
     * issue is that if the second piece is a piece we clear it out and then swap with the cleared piece
     * can create a temporary piece equal to the piece that we cleared out and undo swapping if still in check
     */

    //we store this temporary piece in case the baord is still in check after the move therefore making it an invalid move
    Piece temporary_piece = Piece(second_piece.get_x_location(),second_piece.get_y_location(),second_piece.get_color(),second_piece.get_name());


    //this king is stored in case a king is moved and then needs to be put back
    Piece temp_king = Piece(-1,-1,'e','0');
    if(first_piece.get_name() == 'K' or second_piece.get_name() == 'K'){
        if(first_piece.get_color() == 'w' or second_piece.get_color() == 'b'){
            temp_king = black_king;
            black_king = second_piece;
        }
        else{
            temp_king = white_king;
            white_king = second_piece;
        }
    }
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

            if(temp_king.get_name() == 'K'){
                if(temp_king.get_color() == 'b'){
                    black_king = temp_king;
                }
                else{
                    white_king = temp_king;
                }
            }

            first_piece.set_color(second_piece.get_color());
            first_piece.set_name(second_piece.get_name());
            //first piece is set back time to set back the second piece
            //important here to make sure we set second_pieces values to temps values
            second_piece.set_color(temporary_piece.get_color());
            second_piece.set_name(temporary_piece.get_name());

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
            Piece isItaCapture;
            isItaCapture = get_piece(destination_x,destination_y);

            if(isItaCapture.get_color() == 'b') {
                moveForwardOne = (initial_x == destination_x + 1) and (initial_y == destination_y - 1);
                moveForwardTwo = (initial_x == destination_x + 1) and (initial_y == destination_y + 1);
            }
            else if(initial_location.get_pawn_rule()){
                moveForwardTwo = (initial_x == destination_x + 2) and (initial_y == destination_y);
            }
            if (moveForwardOne or moveForwardTwo) {
                return true;
            }
        }
        else{
            bool moveForwardOne = (initial_x == destination_x - 1) and (initial_y == destination_y);
            bool moveForwardTwo = false;
            Piece isItaCapture;
            isItaCapture = get_piece(destination_x,destination_y);

            if(isItaCapture.get_color() == 'w') {
                moveForwardOne = (initial_x == destination_x + 1) and (initial_y == destination_y - 1);
                moveForwardTwo = (initial_x == destination_x + 1) and (initial_y == destination_y + 1);
            }

            else if (initial_location.get_pawn_rule()) {
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
                if(valid_move(piece_array[i][j],king)) {
                    if (check_for_pieces_inbetween(piece_array[i][j], king)) {
                        //this piece can attack the king
                        //swap back turns and return false;
                        cout << "In check" << endl;

                        in_check = true;

                        swap_turn();
                        return true;
                    }
                }
            }
        }
    }
    //no pieces can attack the king
    swap_turn();
    in_check = false;
    return false;

}
bool Board::check_for_checkmate() {
    /*
     * So in this function we return true if in checkmate and false if not in checkmate
     * we must loop through all of the current players moves to see if they have any possible moves to get out of checkmate
     * we will look at current_turns pieces at all of their available moves and then check for checks after making that move
     *
     * So the most common way to get out of check is to move the king
     * we have the king stored in memory so it is easy and fast to check his moves first
     * 1. Find the king in check
     * 2. See if moving the king can get you out of check
     * 3. Loop through the piece_array to get a piece of the same color of the king
     * 4. loop through every square on the board to get a final_destination
     * 5. try swapping the piece with the final_destination
     * 5.a if true restore piece_array and return false - there is no checkmate
     * 5.b if false continue looking
     */
    //we must temporarily swap turns in order to check if the other player can take the current players pieces


    Piece king;
    if(current_turn){
        king = white_king;
    }
    else{
        king = black_king;
    }
    //our only issue is that with our functions we want to actually make the move and then see if the checks happen
    //in_check = true so calls to swap pieces will fail if they don't get out of check
    //therefore we just have to try and move each piece to every possible location and then the swap would tell us
    //if it gets us out of check or not -> but then if it does get us out of check it will automatically move for
    //the player; would be nice if we could just move our in_check case to valid_move but with how our functions
    //currently work we need to actually swap the pieces before checking for check.
    //probably easiest to just store the piece_array and then set it back to that at the end
    Piece temp_piece_array[8][8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            temp_piece_array[i][j] = piece_array[i][j];
        }
    }
    //now we can call swap_pieces and if it returns true we know it's not in check mate
    //kings movement

    //so our code has checked to see if the king can move now we are in a situation where the king can't move
    //the next most frequent way to get out of check is to capture the piece that put you in check
    //you would have to go through every piece and see if it can capture that piece
    //it doesn't make any sense to run through every piece twice so we just run through every piece and see if any of the valid
    //moves will work for us

    //we know that the king has the color of the player whos pieces we need to check
    char cur_color = king.get_color();


    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(piece_array[i][j].get_color() == cur_color){
                //we now have a piece that can possibly be moved to get out of check
                //we first must determine all of its valid moves
                //one implementation with poor runtime would be to loop over every square see if its a valid move
                //and if its a valid move attempt to swap 8*8*8*8 iterations so it would run over 4000 times
                //might be realistic because move of the iterations will just end instantly and swapping has no loops
                //temporary solution -> will look to improve eventually
                for(int x = 0; x < 8; x++){
                    for(int y = 0; y < 8; y++) {
                        //Piece at i,j is the piece that can possible move
                        //Piece at x,y is the possible location that piece at i,j can move to

                        bool valid_move_or_not = swap_pieces(i,j,x,y);
                        if(valid_move_or_not){
                            cout << "valid move with a valid piece" << endl;
                            //this is a valid move that doesn't neccesarily mean we are out of check
                            //swap back to the correct turn
                            cout << i << " " << j << " " << x << " " << y << " " <<endl;
                            Piece test_i = get_piece(i,j);
                            Piece test_d = get_piece(x,y);
                            cout << test_i.get_color() << " " << test_d.get_color() << endl;
                            cout << white_king.get_x_location() << " " << white_king.get_y_location() << endl;
                            swap_turn();
                            if(!check_for_checks()){
                                for(int a = 0; i < 8; i++){
                                    for(int b = 0; j < 8; j++){
                                        piece_array[a][b] = temp_piece_array[a][b];
                                    }
                                }
                                cout << "move possible-not king" << endl;
                                return false;
                            }
                        }
                    }
                }
            }
            //if it's not of the right color we don't do anything with the piece
        }
    }
    cout << "checkmate" << endl;
    checkmate = true;
    swap_turn();
    return true;
}

bool Board::check_for_pieces_inbetween(Piece moving_piece,Piece destination) {
    //this function will return true if the game should continue or false if the move is invalid
    if (moving_piece.get_name() == 'N' or moving_piece.get_name() == 'K') {
        //knights are the only piece that is allowed to move over other pieces
        //kings can't move enough squares to attempt to jump over a piece
        return true;
    }
    //we added this variable because all of our function calls will update the turn and cause errors

    //so what we want to do is get the x values for both and the y values from both and loop between them
    int initial_x = moving_piece.get_x_location();
    int initial_y = moving_piece.get_y_location();
    int destination_x = destination.get_x_location();
    int destination_y = destination.get_y_location();

    cout << initial_x << " " << initial_y << " " << destination_x << " " << destination_y << endl;
    //so we have no way of knowing how the pieces are located relative to each other
    //temporary solution is to have if statements making sure we are looping from low to high

    //first we take care of moves in the only y direction
    if (initial_x == destination_x) {
        //we only need to move in y direction
        if (initial_y < destination_y) {
            for (initial_y++; initial_y < destination_y; initial_y = initial_y + 1) {
                //can use initial or destination x because they are ==
                Piece test_piece = get_piece(initial_x, initial_y);
                if (test_piece.get_name() != '0') {
                    cout << "Piece in between" << endl;
                    return false;
                }
            }
        } else {
            for (destination_y++; destination_y < initial_y; destination_y = destination_y + 1) {
                Piece test_piece = get_piece(initial_x, destination_y);
                if (test_piece.get_name() != '0') {
                    cout << "Piece in between" << endl;
                    return false;
                }
            }
        }
    }

        //then we take care of moves only in the x direction
    else if (initial_y == destination_y) {
        //we only need to move in y direction
        if (initial_x < destination_x) {
            //note this ++ is so we start at the piece after our current piece
            for (initial_x++; initial_x < destination_x; initial_x = initial_x + 1) {
                //can use initial or destination y because they are ==
                Piece test_piece = get_piece(initial_x, initial_y);
                if (test_piece.get_name() != '0') {
                    cout << "Piece in between" << endl;
                    return false;
                }
            }
        } else {

            for (destination_x++; destination_x < initial_x; destination_x = destination_x + 1) {
                //can use initial or destination y because they are ==
                Piece test_piece = get_piece(destination_x, initial_y);
                cout << destination_x << " " << initial_y << endl;
                if (test_piece.get_name() != '0') {
                    cout << "Piece in between" << endl;
                    return false;
                }
            }
        }
    }
    else{
        //before this loop we knew knights and king moves can not jump over a piece
        //So now we have king, knight, rook, pawn fully implemented
        //all we have left is the bishop and queen diagonal moves

        //this loop probably can be altered to cover all cases but currently can not because if the x or y values
        //of the 2 pieces are the same it wont run the loops
        //this loop runs between the initial piece to the destination piece incrementing and decrementing when neccesary
        //this will start at the piece right after inital and stop when we get to our destination piece
        if(initial_x > destination_x){
            initial_x = initial_x - 1;
        }
        else{
            initial_x = initial_x + 1;
        }

        if(initial_y > destination_y){
            initial_y = initial_y - 1;
        }
        else{
            initial_y = initial_y + 1;
        }
        while(initial_x != destination_x){
            //have to increase or decrease x depending on which direction we have to go
            //we do this here because we have to increment it up or down one before we go into the next loop


            Piece test_piece = get_piece(initial_x,initial_y);
            cout << test_piece.get_color() << " " << initial_x << " " << initial_y <<endl;
            if (test_piece.get_name() != '0') {
                cout << "Piece in between" << endl;
                return false;
            }
            //update loop values
            if(initial_x > destination_x){
                initial_x = initial_x - 1;
            }
            else{
                initial_x = initial_x + 1;
            }

            if(initial_y > destination_y){
                initial_y = initial_y - 1;
            }
            else{
                initial_y = initial_y + 1;
            }

        }

    }

    //no pieces in between you're good
    return true;
}