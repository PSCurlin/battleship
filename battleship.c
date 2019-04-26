#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "battleship.h"

//Associates the word for each color with its approprate ASCII color equivalent
#define RED   "\x1B[31m"
#define GRN   "\x1B[92m"
#define BLU   "\x1B[94m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define YEL   "\x1B[93m"
#define BOLD  "\x1B[1m"
#define RSTCOL "\x1B[0m"

struct _board{
  int size;
  int *data;
  int unhit;
  int *tracker;
  int cells_with_ships;
  int carrier;
  int battleship;
  int cruiser;
  int submarine;
};

//Prints a usage if a user enters an invalid input a usage message appears
void printUsage(){
  printf(YEL BOLD "Error!"RSTCOL" Invalid input. You must input in the following format:\n");
  printf(YEL"Size of board:"RSTCOL" integer between 5 and 20\n");
  printf(YEL"Max Shots:"RSTCOL" Integer between 12 and n^2 - 1 (where n is the size of the board)\n");
}

 board * createBoard(int size) {
   int i; board * b;
   if(size <= 0) return NULL;
   b = (board *) malloc(sizeof(board));
   if(!b) return NULL;
   b->size = size;
   b->data = (int*) malloc(size*size*sizeof(int));
   b->tracker = (int*)malloc(size*size*sizeof(int));
   if(!b->data) {
     free(b);
     return NULL;
   }
   if(!b->tracker) {
     free(b);
     return NULL;
   }
   for(i = 0; i < size*size; i++){
     b->data[i] = 0;
     b->tracker[i] = 0;
   }
   return b;
 }

int getTracker(board*b, int i, int j) {
   return b->tracker[(j-1) * b->size + i];
}
 
int get(board *b, int row, int col){
  return b->data[(col-1)*b->size+row];
}
void set(board * b, int row, int col, double val) {
  b->data[(col-1) * b->size + row] = val;
}

void printBoard(board*b) {
  int i, j = 0;
  for(i = 1; i<=b->size; i++)
    {
      printf("\n");
      for(j=1;j<=b->size;j++){
      if(getTracker(b, i, j) == 0){
	printf(".  ");
      }
      else if(getTracker(b,i,j)==1){
	printf("O  ");
      }
      else if(getTracker(b,i,j)==-1){
	printf("X  ");
      }
      }
    }
  printf("\n\n");
}

void revealBoard(board*b){
  int i, j;
  for(i = 1; i <= b->size; i++){
    printf("\n");
    for(j=1;j<=b->size;j++){
      printf("%d ", get(b,i,j));
    }
  }
  printf("\n\n");
}

// Parses the arguments put into the input by the user
// argc is the argument counter, argv the argument vector
// size the size of the board and maxshots the maximum number of shots (both of which are stored for setting up the game)
int parseArgs(int argc, char ** argv,int *size, int *maxshots)
{
   //Checks if there are too few inputs or too many, prints the usage if this is the case
  if (argc < 2 || argc > 3){
	printUsage();
	return -1;
      }
  // Case for when there are two arguments
  else if (argc == 2){
    // Checks if the input is malformed, or if the maxshots is out of bounds from the range of number of shots defined by the size of the board
    // If it is, it prints the usage
    if(sscanf(argv[1],"%d",maxshots) != 1 || *maxshots<12||*maxshots>((*size)*(*size))-1){
      printUsage();
      return -1;
    }
  }
  // Case for when there are three arguments
  else if(argc == 3){
    // Checks if the input is malformed, or if the maxshots is out of bounds from the range of number of shots defined by the size of the board
    // If it is, it prints the usage
    if ( sscanf(argv[2],"%d",maxshots) != 1 || *maxshots<12||*maxshots>((*size)*(*size)-1)){
      printUsage();
      return -1;
    }
    // Checks if the input is malformed, or if the szie is out of bounds from the predefined board size range (5 to 20)
    // If it is, it prints the usage
    if(sscanf(argv[1],"%d",size) != 1 || *size<5 || *size > 20) {
	    printUsage();
	    return -1;
      }
  }
  //Returns 0 when successfull
  return 0;
}



 void deleteBoard(board*b)
 {
   if(b) {
     free(b->data);
     free(b->tracker);
     free(b);
   }
 }

void arrangeCarrier(board *b){
   
  int dir,randrow,randcol;

  while(1){

  dir = rand() % 4;  //random direction 0 = upwards, 1 = downards, 2 = rightward, 3 = leftward

  if(dir == 0){ 
    //generate a random cell, excluding the first three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 4 + 1) + 4;   //from 4 to n
    randcol = rand() % (b->size - 1 + 1) + 1;   //from 1 to n

    //ensure that the ship does not overlap with other ships, if it does then continue to the top of the while loop again
    if (get(b,randrow,randcol) !=0 ||  get(b,randrow-1,randcol) !=0 || get(b,randrow-2,randcol) !=0 || get(b,randrow-3,randcol) !=0 ) continue;

    //finally set the cells to 4 (since we are arranging a carrier.)
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
    randcol = rand() % (b->size - 4 + 1) + 4;   //from 4 to n

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

void arrangeBattleship(board *b){
   int dir,randrow,randcol;

  while(1){

  dir = rand() % 4;  //random direction 0 = upwards, 1 = downards, 2 = rightward, 3 = leftward

  if(dir == 0){ 
    //generate a random cell, excluding the first three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 3 + 1) + 3;   //from 3 to n
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
    randcol = rand() % (b->size - 3 + 1) + 3;   //from 3 to n

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

void arrangeCruiser(board *b){
   int dir,randrow,randcol;

  while(1){

  dir = rand() % 4;  //random direction 0 = upwards, 1 = downards, 2 = rightward, 3 = leftward

  if(dir == 0){ 
    //generate a random cell, excluding the first three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 3 + 1) + 3;   //from 3 to n
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
    randcol = rand() % (b->size - 3 + 1) + 3;   //from 3 to n

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

void arrangeSubmarine(board *b){
   int dir,randrow,randcol;

  while(1){

  dir = rand() % 4;  //random direction 0 = upwards, 1 = downards, 2 = rightward, 3 = leftward

  if(dir == 0){ 
    //generate a random cell, excluding the first three random rows, otherwise the ship may go out of the board!
    randrow = rand() % (b->size - 2 + 1) + 2;   //from 2 to n
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
    randcol = rand() % (b->size - 2 + 1) + 2;   //from 2 to n

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
 board * randomFleetArrangement (board * b){

  arrangeCarrier(b);
  arrangeBattleship(b);
  arrangeCruiser(b);
  arrangeSubmarine(b);

  b->unhit = 12;
  b->carrier = 4;
  b->battleship = 3;
  b->cruiser = 3;
  b->submarine = 2;

  return b;
}


int readTargets(board * b, int * targetRow, int * targetCol){
  char cell[3];
  int row;
  char col;
  int ret;
  int size = b->size;

  while(1){
    fgets(cell,3,stdin);

    if(sscanf("%d",&targetRow) != 1) {
      printf(YEL BOLD "Error! You must input the number of rows followed by the letter column.); 
    }
  }

}

