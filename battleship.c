#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>


//for the time being this is all in the .c rather than the .h

struct _board{
  int size;
  int *data;
  int cells_with_ships;
  int carrier;
  int battleship;
  int cruiser;
  int submarine;
};

void usage1();
void help();
void instructions();
void delay(int seconds);

static char input[100];

static int getInput()
{
  printf("\n>>> ");
  return fgets(input,  sizeof(input),stdin) !=NULL;
}

static int parseArgs()
{
  char *cmd = strtok(input, " \n");
  
  if (cmd != NULL)
    {
      if (strcmp(cmd, "-h") == 0) {
	help();
      }
      else if (strcmp(cmd, "-i") == 0) {
	  instructions();
	}
      else if (strcmp(cmd, "-x") == 0) {
	   exit(0);
        }
      // else if - put the function to see if the numbers are between the values that we need
      
      else {
	usage1();
      }
    }
   return 1;
}

int main()
{
  printf("\n~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("WELCOME TO BATTLESHIP!\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~\n");
  
  printf("\nType in the number of shots that you wish to have (-h for list of commands):\n");
  while (getInput() && parseArgs());
  printf("\nBye!\n");
  delay (1);
  return 0;
}
	  
	       
//void restart();
//int parseArgs(int argc, char **argv,int* board_size,int *max_shots);

/*int main(int argc, char **argv){
  if (argc  > 3)
    {
      printf("I did not understand your input. Please type again\n");
      printUsage();
      return -1;
    }
  if(argc > 1){
    if(strcmp("-h",argv[1])==0)
      {
	help();
	return -1;
      }
       if(strcmp("-x",argv[1])==0)
      {
	exit(0);
      }
       if(strcmp("-i",argv[1])==0)
	 {
	   instructions();
	 }
  }
       return -1;
}	

//board * randomFleetArrangement (board * blank_board);

void printUsage() {
  printf("Usage: Number of shots: \n Input a number between 12 and 63.\n");
}
*/
	  
void instructions() {
  printf("\n~~~~~~~~~~~~~~~~~~~~~\n");
  printf("HOW TO PLAY BATTLESHIP\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~\n");
  
  printf("\nThis is a single-player version of the game.\n");
  printf("You must figure out the location of the computer's fleet\n");
  printf("\nShips will only  be arranged horizontally or vertically.\n");
  printf("The ships will not overlap each other and are fully \nwithin the board.\n");
  
  printf("\nWhen the ships are arranged, you will fire shots at the \n");
  printf("computer's board by announcing the cell number you wish to hit.\n");
  
  printf("\nIf you hit the computer's ship it will announce HIT else\nit will declare a MISS.\n ");
  
  printf("\nOnce an entire ship is sunk the computer will declare YOU SUNK MY (ship type)!\n");
  
  printf("\nIf you sink all of the ships under the given number of available shots,\n");
  printf("you win the game!\n");
}
  
void help() {
  printf("\n~~~~~~~~~~~~~~~~");
  printf("\nLIST OF COMMANDS");
  printf("\n~~~~~~~~~~~~~~~~");
  printf(" -i    instructions on the game\n");
  printf(" -h    list of commands\n");
  printf(" -x    exits the game\n");
  printf(" -r    restarts the game\n");
}

void usage1() {
  printf("Usage: input an integer between A and B for the number of shots"); // need to add the values
}

void delay(int seconds) {
  int ms = 1000 * seconds;
  clock_t strt_tm = clock();
  while (clock() < strt_tm +ms);
}
