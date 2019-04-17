#ifndef BATTLESHIP_H_
#define BATTLESHIP_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

//Commands
void printUsage();

//Time
void delay(int seconds);

//Colors
#define RED   "\x1B[31m"
#define GRN   "\x1B[92m"
#define BLU   "\x1B[94m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define YEL   "\x1B[93m"
#define BOLD  "\x1B[1m"
#define RSTCOL "\x1B[0m"

int parseArgs(int argc, char ** argv, int*size, int*maxshots);

//Board creation
typedef struct _board board;
board *  createBoard(int size);
void deleteBoard();
void printBoard(board*b);
int getTracker(board*b, int i, int j);
void revealBoard(board *b);
int get(board*b, int row, int col);
void set(board*b, int row, int col, double val);
void arrangeCarrier(board*b);
void arrangeBattleship(board *b);
void arrangeCruiser(board *b);
void arrangeSubmarine(board *b);

#endif

