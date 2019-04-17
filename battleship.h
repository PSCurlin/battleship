#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

//Includes the required libraries for the c file
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

//Prints the usage if the user inputs something invalid
void printUsage();

//Creates a delay if needed in seconds
void delay(int seconds);

// Parses the arguments inputted by the user
int parseArgs(int argc, char ** argv, int*size, int*maxshots);

//Functions used to generate the board
typedef struct _board board;
board *  createBoard(int size);
void deleteBoard();
void printBoard(board*b);
int getTracker(board*b, int i, int j);
void revealBoard(board *b);
int get(board*b, int row, int col);
void set(board*b, int row, int col, double val);
//Aranges the carrier
void arrangeCarrier(board*b);
//Aranges the battleships
void arrangeBattleship(board *b);
//Aranges the cruisers
void arrangeCruiser(board *b);
//Aranges the submarines
void arrangeSubmarine(board *b);

#endif

