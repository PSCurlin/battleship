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

struct _board{
  int size;
  int *data;
  int cells_with_ships;
  int carrier;
  int battleship;
  int cruiser;
  int submarine;
};

void printUsage();
void help();
void instructions();
void restart();

int parseArgs(int argc, char **argv,int* board_size,int *max_shots);
static void arrangeCarrier(board*b);
static void arrangeBattleship(board *b);
static void arrangeCruiser(board *b);
static void arrangeSubmarine(board *b);

//User input
static int getInput()
{
  printf(GRN "\n>>> "RSTCOL);
  return fgets(input,  sizeof(input),stdin) !=NULL;
}

//Parser
static int parseArgs()
{
  char *cmd = strtok(input, " \n");
  
  if (cmd != NULL)
    {
      if (strcmp(cmd, "-h") == 0) {
	help();
      }
       if (strcmp(cmd, "-i") == 0) {
	  instructions();
	}
      else if (strcmp(cmd, "-x") == 0) {
      	  printf(BOLD"\nBYE!\n"RSTCOL);
	  exit(0);
        }
      // else if - put the function to see if the numbers are between the values that we need
      
      else {
	usage1();
      }
    }
   return 1;
}

//Prints the main screen of the game
void mainscrn(){
  printf(RED "\n~~~~~~~~~~~~~~~~~~~~~~\n"RSTCOL);
  printf("WELCOME TO BATTLESHIP!\n");
  printf(RED "~~~~~~~~~~~~~~~~~~~~~~\n"RSTCOL);
  printf("\nType in the number of shots that you wish to have (-h for list of commands):\n");

}


void printUsage() {
  printf("Usage: Number of shots: \n Input a number between 12 and 63.\n");

//Declares the usage for inputting the number of shots
void usage1() {
  printf(YEL BOLD "Usage "RSTCOL YEL ": input an integer between 12 and 63 for the number of shots"RSTCOL);
}

//Lists the instructions of the game
void instructions() {
  printf(RED"\n~~~~~~~~~~~~~~~~~~~~~\n"RSTCOL);
  printf("HOW TO PLAY BATTLESHIP\n");
  printf(RED "~~~~~~~~~~~~~~~~~~~~~~\n"RSTCOL);
  
  printf("\nThis is a single-player version of the game.\n");
  printf("You must figure out the location of the computer's fleet\n");
  printf("\nShips will only  be arranged horizontally or vertically.\n");
  printf("The ships will not overlap each other and are fully \nwithin the board.\n");
  
  printf("\nWhen the ships are arranged, you will fire shots at the \n");
  printf("computer's board by announcing the cell number you wish to hit.\n");
  
  printf("\nIf you hit the computer's ship it will announce "RED"HIT"RSTCOL " else it will \ndeclare a "BLU"MISS.\n "RSTCOL);
  
  printf("\nOnce an entire ship is sunk the computer will declare"BOLD" YOU SUNK MY"YEL " [ship type]"RSTCOL "!\n");
  
  printf("\nIf you sink all of the ships under the given number of available shots,\n");
  printf("you win the game!\n");
}

//Lists the user commands
void help() {
  printf(RED "\n~~~~~~~~~~~~~~~~"RSTCOL);
  printf("\nLIST OF COMMANDS");
  printf(RED"\n~~~~~~~~~~~~~~~~\n"RSTCOL);
  printf(YEL BOLD" -i " RSTCOL "   instructions on the game\n");
  printf(YEL BOLD" -h " RSTCOL "   list of commands\n");
  printf(YEL BOLD" -x " RSTCOL "   exits the game\n");
  printf(YEL BOLD" -r " RSTCOL "   restarts the game\n");
}

//Creates a delay in seconds
void delay(int seconds) {
  int ms = 1000 * seconds;
  clock_t strt_tm = clock();
  while (clock() < strt_tm +ms);
}

