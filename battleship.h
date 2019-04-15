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

<<<<<<< HEAD
void printUsage();
void help();
void instructions();
void restart();
int parseArgs(int argc, char **argv,int* board_size,int *max_shots);
static void arrangeCarrier(board*b);
static void arrangeBattleship(board *b);
static void arrangeCruiser(board *b);
static void arrangeSubmarine(board *b);

=======
//User input
static int getInput()
{
  printf(GRN "\n>>> "RSTCOL);
  return fgets(input,  sizeof(input),stdin) !=NULL;
}
>>>>>>> e272e66581fa254312b3bd2a0a66f5f85c95afd8

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

<<<<<<< HEAD
static void arrangeCarrier(board *b){
   
  int dir,randrow,randcol;

  while(1){

  dir = rand() % 4;  //random direction 0 = upwards, 1 = downards, 2 = rightward, 3 = leftward

  if(dir == 0){ 
    //generate a random cell, excluding the first three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 4 + 1) + 1;   //from 4 to n
    randcol = rand() % (b->size - 1 + 1) + 1;   //from 1 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0 || get(b,randrow-2,randcol) !=0 || get(b,randrow-3,randcol) !=0 ) continue;

    //finally set the cells to 1 (since we are arranging a carrier.)
    set(b,randrow,randcol,1);
    set(b,randrow-1,randcol,1);
    set(b,randrow-2,randcol,1);
    set(b,randrow-3,randcol,1);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
    
  }
  else if(dir == 1){  //downward
    //generate a random cell, excluding the last three random rows, otherwise the ship may go out of the board!
    randrow = rand() % ((b->size - 3) - 1 + 1) + 1;   //from 1 to n - 3
    randcol = rand() % (b->size - 1 + 1) + 1;   //from 1 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow+1,randcol) !=0 || get(b,randrow+2,randcol) !=0 || get(b,randrow+3,randcol) !=0 ) continue;

    //finally set the cells to 1 (since we are arranging a carrier.)
    set(b,randrow,randcol,1);
    set(b,randrow+1,randcol,1);
    set(b,randrow+2,randcol,1);
    set(b,randrow+3,randcol,1);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
  }
   else if(dir == 2){  //rightward
    //generate a random cell, excluding the last three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 1 + 1) + 1;   //from 1 to n
    randcol = rand() % (b->size - 4 + 1) + 1;   //from 4 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol-1) !=0 || get(b,randrow,randcol-2) !=0 || get(b,randrow,randcol-3) !=0 ) continue;

    //finally set the cells to 1 (since we are arranging a carrier.)
    set(b,randrow,randcol,1);
    set(b,randrow,randcol-1,1);
    set(b,randrow,randcol-2,1);
    set(b,randrow,randcol-3,1);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
  }
   else if(dir == 3){  //leftward
    //generate a random cell, excluding the last three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 1 + 1) + 1;   //from 1 to n
    randcol = rand() % ((b->size-3) - 1 + 1) + 1;   //from 1 to n - 3

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol+1) !=0 || get(b,randrow,randcol+2) !=0 || get(b,randrow,randcol+3) !=0 ) continue;

    //finally set the cells to 1 (since we are arranging a carrier.)
    set(b,randrow,randcol,1);
    set(b,randrow,randcol+1,1);
    set(b,randrow,randcol+2,1);
    set(b,randrow,randcol+3,1);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
  }
  
  }
}

static void arrangeBattleship(board *b){
   int dir,randrow,randcol;

  while(1){

  dir = rand() % 4;  //random direction 0 = upwards, 1 = downards, 2 = rightward, 3 = leftward

  if(dir == 0){ 
    //generate a random cell, excluding the first three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 3 + 1) + 1;   //from 3 to n
    randcol = rand() % (b->size - 1 + 1) + 1;   //from 1 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0 || get(b,randrow-2,randcol) !=0) continue;

    //finally set the cells to 2 (since we are arranging a battleship.)
    set(b,randrow,randcol,2);
    set(b,randrow-1,randcol,2);
    set(b,randrow-2,randcol,2);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
    
  }
  else if(dir == 1){  //downward
    //generate a random cell, excluding the last three random rows, otherwise the ship may go out of the board!
    randrow = rand() % ((b->size - 2) - 1 + 1) + 1;   //from 1 to n - 2
    randcol = rand() % (b->size - 1 + 1) + 1;   //from 1 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow+1,randcol) !=0 || get(b,randrow+2,randcol) !=0) continue;

    //finally set the cells to 2 (since we are arranging a battleship.)
    set(b,randrow,randcol,2);
    set(b,randrow+1,randcol,2);
    set(b,randrow+2,randcol,2);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
  }
   else if(dir == 2){  //rightward
    //generate a random cell, excluding the last three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 1 + 1) + 1;   //from 1 to n
    randcol = rand() % (b->size - 3 + 1) + 1;   //from 3 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol-1) !=0 || get(b,randrow,randcol-2) !=0) continue;

    //finally set the cells to 2 (since we are arranging a battleship.)
    set(b,randrow,randcol,2);
    set(b,randrow,randcol-1,2);
    set(b,randrow,randcol-2,2);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
  }
   else if(dir == 3){  //leftward
    //generate a random cell, excluding the last three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 1 + 1) + 1;   //from 1 to n
    randcol = rand() % ((b->size-2) - 1 + 1) + 1;   //from 1 to n - 2

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol+1) !=0 || get(b,randrow,randcol+2) !=0) continue;

    //finally set the cells to 2 (since we are arranging a battleship.)
    set(b,randrow,randcol,2);
    set(b,randrow,randcol+1,2);
    set(b,randrow,randcol+2,2);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
  }
  
  }
}

static void arrangeCruiser(board *b){
   int dir,randrow,randcol;

  while(1){

  dir = rand() % 4;  //random direction 0 = upwards, 1 = downards, 2 = rightward, 3 = leftward

  if(dir == 0){ 
    //generate a random cell, excluding the first three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 3 + 1) + 1;   //from 3 to n
    randcol = rand() % (b->size - 1 + 1) + 1;   //from 1 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0 || get(b,randrow-2,randcol) !=0) continue;

    //finally set the cells to 3 (since we are arranging a cruiser.)
    set(b,randrow,randcol,3);
    set(b,randrow-1,randcol,3);
    set(b,randrow-2,randcol,3);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
    
  }
  else if(dir == 1){  //downward
    //generate a random cell, excluding the last three random rows, otherwise the ship may go out of the board!
    randrow = rand() % ((b->size - 2) - 1 + 1) + 1;   //from 1 to n - 2
    randcol = rand() % (b->size - 1 + 1) + 1;   //from 1 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow+1,randcol) !=0 || get(b,randrow+2,randcol) !=0) continue;

    //finally set the cells to 3 (since we are arranging a cruiser.)
    set(b,randrow,randcol,3);
    set(b,randrow+1,randcol,3);
    set(b,randrow+2,randcol,3);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
  }
   else if(dir == 2){  //rightward
    //generate a random cell, excluding the last three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 1 + 1) + 1;   //from 1 to n
    randcol = rand() % (b->size - 3 + 1) + 1;   //from 3 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol-1) !=0 || get(b,randrow,randcol-2) !=0) continue;

    //finally set the cells to 3 (since we are arranging a cruiser.)
    set(b,randrow,randcol,3);
    set(b,randrow,randcol-1,3);
    set(b,randrow,randcol-2,3);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
  }
   else if(dir == 3){  //leftward
    //generate a random cell, excluding the last three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 1 + 1) + 1;   //from 1 to n
    randcol = rand() % ((b->size-2) - 1 + 1) + 1;   //from 1 to n - 2

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol+1) !=0 || get(b,randrow,randcol+2) !=0) continue;

    //finally set the cells to 3 (since we are arranging a cruiser.)
    set(b,randrow,randcol,3);
    set(b,randrow,randcol+1,3);
    set(b,randrow,randcol+2,3);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
  }
  
  }
}

static void arrangeSubmarine(board *b){
   int dir,randrow,randcol;

  while(1){

  dir = rand() % 4;  //random direction 0 = upwards, 1 = downards, 2 = rightward, 3 = leftward

  if(dir == 0){ 
    //generate a random cell, excluding the first three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 2 + 1) + 1;   //from 2 to n
    randcol = rand() % (b->size - 1 + 1) + 1;   //from 1 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0) continue;

    //finally set the cells to 4 (since we are arranging a submarine.)
    set(b,randrow,randcol,4);
    set(b,randrow-1,randcol,4);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!    
  }
  else if(dir == 1){  //downward
    //generate a random cell, excluding the last three random rows, otherwise the ship may go out of the board!
    randrow = rand() % ((b->size - 1) - 1 + 1) + 1;   //from 1 to n - 1
    randcol = rand() % (b->size - 1 + 1) + 1;   //from 1 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow+1,randcol) !=0) continue;

    //finally set the cells to 4 (since we are arranging a submarine.)
    set(b,randrow,randcol,4);
    set(b,randrow+1,randcol,4);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
  }
   else if(dir == 2){  //rightward
    //generate a random cell, excluding the last three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 1 + 1) + 1;   //from 1 to n
    randcol = rand() % (b->size - 2 + 1) + 1;   //from 2 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol-1) !=0) continue;

    //finally set the cells to 4 (since we are arranging a submarine.)
    set(b,randrow,randcol,4);
    set(b,randrow,randcol-1,4);;
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
  }
   else if(dir == 3){  //leftward
    //generate a random cell, excluding the last three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 1 + 1) + 1;   //from 1 to n
    randcol = rand() % ((b->size-1) - 1 + 1) + 1;   //from 1 to n - 1

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow,randcol+1) !=0) continue;

    //finally set the cells to 4 (since we are arranging a submarine.)
    set(b,randrow,randcol,4);
    set(b,randrow,randcol+1,4);
    break;  //very important, otherwise you get stuck in an infinite loop!!!!!
  }
  
  }
}

board * randomFleetArrangement (board * blank_board){

  arrangeCarrier(blank_board);
  arrangeBattleship(blank_board);
  arrangeCruiser(blank_board);
  arrangeSubmarine(blank_board);
  
}
void printUsage() {
  printf("Usage: Number of shots: \n Input a number between 12 and 63.\n");
=======
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
>>>>>>> e272e66581fa254312b3bd2a0a66f5f85c95afd8
}

