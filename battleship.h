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
static void arrangeCarrier(board*b);
static void arrangeBattleship(board *b);
static void arrangeCruiser(board *b);
static void arrangeSubmarine(board *b);


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
}

