#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

//Prints the usage if the user inputs something invalid
void printUsage();
//Main screen of the game
void mainScreen();
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
//Gets the value of the cell
int getTracker(board*b, int i, int j);
//Sets the value of a cell
void setTracker(board * b, int row, int col, double val);
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
void randomFleetArrangement (board * b);
void readTargets(board*b, int * row, int * col);
//Main function that counts if your shots and declares your win or loss
void play(board *b, int maxshots);

#endif

