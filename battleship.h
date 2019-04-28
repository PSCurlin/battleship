#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

//Prints the usage if the user inputs something invalid
void printUsage();
//Main screen of the game
int mainscrn();
//Creates a delay if needed in seconds
void delay(int seconds);
// Parses the arguments inputted by the user
int parseArgs(int argc, char ** argv, int*size, int*maxshots);
//Functions used to generate the board
typedef struct _board board;
board *  createBoard(int size);
//Deletes the board
void deleteBoard();
//Prints the board
void printBoard(board*b);
//Tracks if the cell has been previously hit
int getTracker(board*b, int i, int j);
//Reveals the board
void revealBoard(board *b);
//Gets element from the board
int get(board*b, int row, int col);
//Sets element from the board
void set(board*b, int row, int col, double val);
//Aranges the carrier
void arrangeCarrier(board*b);
//Aranges the battleships
void arrangeBattleship(board *b);
//Aranges the cruisers
void arrangeCruiser(board *b);
//Aranges the submarines
void arrangeSubmarine(board *b);
//Reads the inputted target by the user
int readTargets(board*b, int * row, int * col);
//Declares that you lost and quits the game
int lose();
//Declares that you won and quits the game
int win();
//Counts the number of hits until the max number of shots

#endif

