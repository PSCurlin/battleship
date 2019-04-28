#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

/*
Prints the usage if the user inputs something invalid.
 */
void printUsage();

/*
Generates the main screen of the game.
 */
void mainScreen();

/*
Creates a delay if needed in seconds
*/
void delay(int seconds);

/*
This function parses the command−line input arguments in argv and stores the user−provided
board size (if provided)at the memory location pointed to by board size and the
maximum number of shots allowed at the memory location pointed to by max shots. 
Returns 0 for successful parsing and −1 if there is an error in user input .
 */
int parseArgs(int argc, char ** argv, int*size, int*maxshots);

//Functions used to generate the board

//Defines the board type
typedef struct _board board;

/*
This function creates the board that the ships will be arranged on by 
taking in the size of the board based on the user input. The values of
each part of the board are 0 by default.
 */
board *  createBoard(int size);

/*
This function deletes the board in order to conserve memory in the stack.
 */
void deleteBoard();

/*
This function prints the board for the user, with each unhit spot represented by a '.' .
An 'O' is printed for missed shots and an 'X' is printed for hits.
*/
void printBoard(board*b);

/*
The tracker board tracks what elements on the board have been hit or unhit. This function
fetches the value of a specific part of the board and returns it (either a 0,1,or -1 based
on if the spot has been hit or not).
 */
int getTracker(board*b, int i, int j);

/*
This function sets the certain points of the board to either 0, 1, or -1 based on if the 
spot is hit, missed, or unhit.
 */
void setTracker(board * b, int row, int col, double val);

/* This function is only used internally to verify that the ships are being generated correctly
   and randomly.*/
void revealBoard(board *b);

/*
This function fetches the values from the board that contains the fleet arrangement.
 */
int get(board*b, int row, int col);

/*
This function sets the value of the spot on the board that contains the fleet arrangement.
 */
void set(board*b, int row, int col, double val);

/*
This function randomly arranges the carrier on the board and ensures that it doesn't overlap with 
any other fleets.
 */
void arrangeCarrier(board*b);

/*
This function randomly arranges the battleship on the board and ensures that it doesn't overlap with 
any other fleets.
 */
void arrangeBattleship(board *b);

/*
This function randomly arranges the cruiser on the board and ensures that it doesn't overlap with 
any other fleets.
 */
void arrangeCruiser(board *b);

/*
This function randomly arranges the submarine on the board and ensures that it doesn't overlap with 
any other fleets.
 */
void arrangeSubmarine(board *b);

/*
This function generates the random fleet arrangement on blank board and returns a pointer to the new board.
*/
void randomFleetArrangement (board * b);

/*
This function reads the users input guess for the target cell and prints out errors if the input is
malformed.
 */
void readTargets(board*b, int * row, int * col);

/*
This function takes the users input and prints if it is a hit or miss, all while counting down from the
maximum shots and printing out a new changed board each time. The function then declares whether the user
has won or lost the game based on the max shots either running out or the user sinking all the fleets.
 */
void play(board *b, int maxshots);

#endif

