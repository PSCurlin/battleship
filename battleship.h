#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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

int parseArgs(int argc, char **argv,int* board_size,int *max_shots){
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
	exit();
      }
       if(strcmp("-i",argv[1])==0)
	 {
	   instructions();
	 }
       return -1;
  }
  }	
}

board * randomFleetArrangement (board * blank_board);

void printUsage() {
  printf("Usage: Number of shots: \n Input a number between 12 and 63.\n");
}

