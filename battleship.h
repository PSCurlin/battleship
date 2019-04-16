#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

//Main screen functions
void mainscrn();
void usage1();

//Commands
void instructions();
void help();

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


static char input[100];
static int getInput();
static int parseArgs();

void printUsage();
void help();
void instructions();
void restart();

typedef struct _board;
int parseArgs(int argc, char **argv,int* board_size,int *max_shots);
static void arrangeCarrier(board*b);
static void arrangeBattleship(board *b);
static void arrangeCruiser(board *b);
static void arrangeSubmarine(board *b);


